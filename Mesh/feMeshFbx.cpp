#include "feMeshFbx.h"

#include "Material\feMaterial.h"
#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace Mesh
	{
		feMeshFbx::feMeshFbx(std::string const& name, feVertices vData, feMaterial* mtl)
			:feMesh()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshFbx is creating. . .");
			_vData = vData;
			_material = mtl;
			_name = name;

			Init();
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshFbx created !");
		}

		feMeshFbx::~feMeshFbx()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshFbx is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshFbx deleted !");
		}

		feMeshFbx::feMeshFbx(feMeshFbx const& copy)
			:feMesh(copy)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshFbx is copying. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshFbx copied !");
		}

		feMeshFbx* feMeshFbx::Clone()
		{
			return new feMeshFbx(*this);
		}

		void feMeshFbx::Draw()
		{
			if (_material)
				_material->UpdateBufferObject();

			feRenderer::Draw(_vData.GetVerticesNb(), TypeDraw::DRAW_INDEXED, TypePolygon::TRIANGLES);
		}

		void feMeshFbx::Init()
		{
			_buffer.Create(_vData);
		}
	}
}