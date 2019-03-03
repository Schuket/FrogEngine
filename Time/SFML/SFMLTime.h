#ifdef TIME_EXPORTS
#define SFMLTime_API __declspec(dllexport) 
#else
#define SFMLTime_API __declspec(dllimport) 
#endif

#pragma once

#include <SFML/System/Clock.hpp>

#include "../AbstractTime.h"

namespace FrogEngine
{
	namespace SFML
	{
		class Time : AbstractTime
		{
		public:
			// Ctor / Dtor
			SFMLTime_API Time();
			SFMLTime_API ~Time();

			// Functions
			SFMLTime_API float DeltaTime();
			SFMLTime_API void RestartDeltaTime();
			SFMLTime_API void RestartTime();
			SFMLTime_API void Scale(float scale);
			SFMLTime_API void ResetScale();

		private:
			// Variables
			sf::Clock _curClock;
			sf::Clock _deltaClock;
		};
	} // namespace SFML
} // namespace FrogEngine