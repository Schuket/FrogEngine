#include "D3DShader.h"

#include "../Error/RHIError.h"


namespace FrogEngine
{
	namespace D3D
	{

		feShader::feShader(std::string name, int& error)
		{
			error = Create(name);
		}


		int feShader::Create(std::string name)
		{
			_name = name;

			return Error::RHI_SUCCESS;
		}

		int feShader::Bind() { return Error::RHI_SUCCESS; }
		int feShader::Unbind() { return Error::RHI_SUCCESS; }
		int feShader::BindTransform(Math::Matrix4 worldPos) { return Error::RHI_SUCCESS; }

	} //namespace D3D
} //namespace FrogEngine