#pragma once

#include "config.h"

#include "feImage.h"

#if defined _SFML_
	#include "SFML/SFMLLoaderImage.h"
	using namespace FrogEngine::SFML;
#else
	#pragma	message("ERROR -> You need to choose a Loader Image Library : SFML")	
#endif