#pragma once

#include "config.h"

#ifdef _SFML_
#include "SFML\SFMLWindow.h"
#include "SFML\SFMLEvent.h"
using namespace FrogEngine::SFML;
#elif defined _SDL_
#include "SDL\SDLWindow.h"
#include "SDL\SDLEvent.h"
using namespace FrogEngine::SDL;
#else
#pragma	message("ERROR -> You need to choose a library to handle Window and his Event")	
#endif
