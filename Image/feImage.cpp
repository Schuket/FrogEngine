#include "feImage.h"

#include "Math/Vector2d.h"
#include "Logger/Logger.h"

namespace FrogEngine
{
	feImage::feImage()
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage is creating. . .");
		_x = 0;
		_y = 0;

		_pixels = nullptr;

		_name = "Unnamed Image";

		_typeTex = TypeTexture::NONE;
		_type = TypeTexture::NONE;
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage created !");
	}

	feImage::feImage(Math::Vector2d size, const uint8_t* pixels, std::string name)
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] is creating. . .");
		_x = (int)size.X();
		_y = (int)size.Y();

		_pixels = pixels;

		_name = name;

		_typeTex = TypeTexture::NONE;
		_type = TypeTexture::NONE;
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] created !");
	}

	feImage::feImage(Math::Vector2d size, const uint8_t* pixels, std::string name, TypeTexture typeTex, TypeTexture type)
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] is creating. . .");
		_x = (int)size.X();
		_y = (int)size.Y();

		_pixels = pixels;

		_name = name;

		_typeTex = typeTex;
		_type = type;
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + name + "] created !");
	}

	feImage::~feImage()
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + _name + "] is deleting. . .");
		_pixels = nullptr;
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feImage[" + _name + "] deleted !");
	}
} // namespace FrogEngine