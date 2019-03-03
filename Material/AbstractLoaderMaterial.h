#pragma once

#include <string>

namespace FrogEngine
{
	class feMaterial;

	struct AbstractLoaderMaterial
	{
		virtual FrogEngine::feMaterial* Load(std::string const& name, std::string const& fileName, std::string const& pathDirectory) = 0;
	};
} // namespace FrogEngine