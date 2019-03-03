#pragma once

#include "config.h"

#if defined _SFML_
	#include "SFML/SFMLTime.h"
	using namespace FrogEngine::SFML;
#else
	#pragma	message("ERROR -> You need to choose a Graphic API : OPENGL / DIRECT3D / VULKAN")	
#endif