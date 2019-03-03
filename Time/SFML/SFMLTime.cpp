#include "SFMLTime.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace SFML
	{
		Time::Time()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Time is creating. . .");
			_curClock.restart();
			_deltaClock.restart();
			ResetScale();
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Time created !");
		}

		Time::~Time()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Time is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Time deleted !");
		}

		float Time::DeltaTime()
		{
			sf::Time curTime;

			curTime = _deltaClock.restart();

			return curTime.asSeconds() * _scale;
		}

		void Time::RestartDeltaTime()
		{
			_deltaClock.restart();
		}

		void Time::RestartTime()
		{
			_curClock.restart();
		}

		void Time::Scale(float scale)
		{
			_scale = scale;
		}

		void Time::ResetScale()
		{
			_scale = 1.f;
		}

	} // namespace SFML
} // namespace FrogEngine