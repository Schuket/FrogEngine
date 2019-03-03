#pragma once

#include <vector>

namespace FrogEngine
{
	enum TypeTexture;
}

namespace FrogEngine
{
	class AbstractTexture
	{
	public:
		// Functions
		virtual int Load(std::string name, FrogEngine::TypeTexture type, FrogEngine::TypeTexture typeTex) = 0;
		virtual int LoadSkybox(std::vector<std::string> names, FrogEngine::TypeTexture type) = 0;
		virtual int Bind(uint32_t const& prgID) = 0;
		virtual int Unbind() = 0;
	};
} // namespace FrogEngine