#ifdef RHI_EXPORTS
#define D3D_TEXTURE_RHI __declspec(dllexport)
#else
#define D3D_TEXTURE_RHI __declspec(dllimport)
#endif

#pragma once

#include "AbstractTexture.h"

namespace FrogEngine
{
	namespace D3D
	{
		class feTexture : public AbstractTexture
		{
		public:
			// Ctor / Dtor
			D3D_TEXTURE_RHI feTexture() { }
			D3D_TEXTURE_RHI ~feTexture() { }

			// Functions
			D3D_TEXTURE_RHI int Load(std::string name, FrogEngine::TypeTexture type, FrogEngine::TypeTexture typeTex) { return 0; }
			D3D_TEXTURE_RHI int LoadSkybox(std::vector<std::string> names, FrogEngine::TypeTexture type) { return 0; }
			D3D_TEXTURE_RHI int Bind(uint32_t const& prgID) { return 0; }
			D3D_TEXTURE_RHI int Unbind() { return 0; };
		};
	} // namespace D3D
} //namespace FrogEngine