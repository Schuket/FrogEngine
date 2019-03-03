#include "SFMLLoaderImage.h"

#include <SFML\Graphics.hpp>

#include "../feImage.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace SFML
	{
		sf::Image LoaderImage::_cache = sf::Image::Image();

		feImage LoaderImage::LoadImg(std::string name)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] is loading. . .");
			if (!_cache.loadFromFile(name))
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] didn't load !");

			Math::Vector2d size((float)_cache.getSize().x, (float)_cache.getSize().y);

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] loaded !");
			return feImage(size, _cache.getPixelsPtr(), name);
		}

		void LoaderImage::FreeCache()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "LoaderImage::Cache freed !");
			_cache = sf::Image::Image();
		}
	} // namespace SFML
} // namespace FrogEngine