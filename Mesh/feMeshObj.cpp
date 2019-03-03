#include "feMeshObj.h"

#include "Material/Material.h"
#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace Mesh
	{
		feMeshObj::feMeshObj(std::string const& name, feVertices vData, feMaterial* mtl)
			:feMesh()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshObj is creating. . .");
			_vData = vData;
			_material = mtl;
			_name = name;

			Init();
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshObj created !");
		}

		feMeshObj::~feMeshObj()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshObj is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshObj deleted !");
		}

		feMeshObj::feMeshObj(feMeshObj const& copy)
			:feMesh(copy)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshObj is copying. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshObj copied !");
		}

		feMeshObj* feMeshObj::Clone()
		{
			return new feMeshObj(*this);
		}

		void feMeshObj::Draw()
		{
			if (_material)
				_material->UpdateBufferObject();

			//glPatchParameteri(GL_PATCH_VERTICES, _vertices.size());
			feRenderer::Draw(_vData.GetVerticesNb(), TypeDraw::DRAW_INDEXED, TypePolygon::TRIANGLES);
		}

		void feMeshObj::Init()
		{
			_buffer.Create(_vData);
		}
	} // namespace Mesh
} // namespace Data