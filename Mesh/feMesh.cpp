#include "feMesh.h"

#include "Material/Material.h"
#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace Mesh
	{
		feMesh::feMesh()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh is creating. . .");
			_name = "NoName";
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh created !");
		}

		feMesh::~feMesh()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh is deleting. . .");
		
			delete _material;

			_material = nullptr;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh deleted !");
		}

		feMesh::feMesh(feMesh const& copy)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh is copying. . .");
			_buffer = copy._buffer;
			_vData = copy._vData;
			_shader = copy._shader;
			_name = copy._name;

			if (_material)
				_material = new feMaterial(*copy._material);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh copied !");
		}

#pragma region Getters/Setters
		feMaterial* feMesh::GetMtl()
		{ 
			return _material; 
		}

		feBuffer& feMesh::GetBuffer()
		{ 
			return _buffer; 
		}

		void feMesh::SetShader(feShader* shader) 
		{ 
			_shader = shader; 
		}

		feShader* feMesh::GetShader()
		{ 
			return _shader; 
		}

		void feMesh::SetName(std::string const& name)
		{
			_name = name;
		}
#pragma endregion

	} // namespace Mesh
} // namespace Data