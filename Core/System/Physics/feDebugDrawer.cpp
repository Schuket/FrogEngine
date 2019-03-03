#include "feDebugDrawer.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace System
	{
		namespace Physics
		{
			//Functions
			feDebugDrawer::feDebugDrawer()
			{
				_gizmoShader.Create("line");
			}

			feDebugDrawer::~feDebugDrawer()
			{
				_gizmoLines.clear();
			}

			void feDebugDrawer::setDebugMode(int debugMode)
			{
				_debugMode = (DebugDrawModes)debugMode;
			}

			int	feDebugDrawer::getDebugMode() const
			{
				return _debugMode;
			}

			void feDebugDrawer::Draw()
			{
				feVertices data;

				std::vector<Line>::iterator begin = _gizmoLines.begin();
				std::vector<Line>::iterator end = _gizmoLines.end();

				for (; begin != end; ++begin)
				{
					Line line = (*begin);
					data.SetPositions(Math::Vector3d(line._from.X(), line._from.Y(), line._from.Z()));
					data.SetPositions(Math::Vector3d(line._to.X(), line._to.Y(), line._to.Z()));
				}

				_buffer.Create(data);
				_buffer.Bind();
				_gizmoShader.Bind();

				feRenderer::Draw(data.GetVerticesNb(), TypeDraw::DRAW, TypePolygon::LINES);

				_gizmoShader.Unbind();
				_gizmoLines.clear();
			}


			///private
			//only here to be Override
			void feDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
			{
				Math::Vector3d fromVec(from.getX(), from.getY(), from.getZ());
				Math::Vector3d toVec(to.getX(), to.getY(), to.getZ());
				Math::Vector3d colorVec(color.getX(), color.getY(), color.getZ());

				_gizmoLines.push_back(Line(fromVec, toVec, colorVec));
			}

			void feDebugDrawer::reportErrorWarning(const char* warningString)
			{
				Logging::Logger::Instance().Log(Logging::CRITICAL, "Bullet Error Warning", warningString);
			}

		} //namespace Physics
	} //namespace System
} //namespace FrogEngine