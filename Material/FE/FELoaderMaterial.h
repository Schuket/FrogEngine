#ifdef MATERIAL_EXPORTS
#define MATERIAL_WRAPPER __declspec(dllexport)
#else
#define MATERIAL_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "../AbstractLoaderMaterial.h"

namespace FrogEngine
{
	namespace FE
	{
		struct LoaderMaterial : public AbstractLoaderMaterial
		{
			MATERIAL_WRAPPER static FrogEngine::feMaterial* Load(std::string const& name, std::string const& fileName, std::string const& pathDirectory);

		private:
			static void LoadPng(std::string const& pathDirectory, FrogEngine::feMaterial* mtl);
			static std::string RecoverNameTex(std::string line);
			static std::string FindFile(std::string const& directory, std::string const& name);
		};
	} // namespace FE
} // namespace FrogEngine