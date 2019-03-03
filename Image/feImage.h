#ifdef IMAGE_EXPORTS
#define IMAGE_WRAPPER __declspec(dllexport)
#else
#define IMAGE_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <string>
#include "../Math/Vector2d.h"

namespace FrogEngine
{
	enum TypeTexture
	{
		NONE = 0,
		TEXTURE_2D,
		TEXTURE_CUBE_MAP,
		TEXTURE_CUBE_MAP_POSITIVE_X,
		TEXTURE_CUBE_MAP_NEGATIVE_X,
		TEXTURE_CUBE_MAP_POSITIVE_Y,
		TEXTURE_CUBE_MAP_NEGATIVE_Y,
		TEXTURE_CUBE_MAP_POSITIVE_Z,
		TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	class feImage
	{
	public:
		IMAGE_WRAPPER feImage();
		IMAGE_WRAPPER feImage(Math::Vector2d size, const uint8_t* pixels, std::string name);
		IMAGE_WRAPPER feImage(Math::Vector2d size, const uint8_t* pixels, std::string name, TypeTexture typeTex, TypeTexture type);
		IMAGE_WRAPPER ~feImage();

		unsigned int _x, _y;
		const uint8_t* _pixels;
		std::string _name;
		TypeTexture _typeTex;
		TypeTexture _type;
	};
} // namespace FrogEngine