#pragma once

#ifdef RHI_EXPORTS
#define D3D_SHADER_RHI __declspec(dllexport)
#else
#define D3D_SHADER_RHI __declspec(dllimport)
#endif


#include <string>
#include "AbstractShader.h"

namespace FrogEngine
{
	namespace D3D
	{
		class feShader : public AbstractShader
		{
		public:
			// Ctor
			D3D_SHADER_RHI feShader() = default;
			D3D_SHADER_RHI feShader(std::string name, int& error);

			// Functions
			D3D_SHADER_RHI virtual int Create(std::string name);

			D3D_SHADER_RHI virtual int Bind();
			D3D_SHADER_RHI virtual int Unbind();
			D3D_SHADER_RHI virtual int BindTransform(Math::Matrix4 worldPos);
		};

	} //namespace D3D
} //namespace FrogEngine
