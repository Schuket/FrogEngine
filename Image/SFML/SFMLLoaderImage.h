#ifdef IMAGE_EXPORTS
#define IMAGE_WRAPPER __declspec(dllexport)
#else
#define IMAGE_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "../AbstractImage.h"

namespace sf
{
	class Image;
} // namespace sf

namespace FrogEngine
{
	namespace SFML
	{
		struct LoaderImage : AbstractImage
		{
			IMAGE_WRAPPER static feImage LoadImg(std::string name);
			IMAGE_WRAPPER static void FreeCache();
		private:
			static sf::Image _cache;
		};
	} // namespace SFML
} // namespace FrogEngine