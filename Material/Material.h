#pragma once

#include "config.h"

#include "feMaterial.h"
#include "feMaterialFbx.h"

#if defined _FE_
	#include "FE/FELoaderMaterial.h"
	using namespace FrogEngine::FE;
#else
	#pragma	message("ERROR -> You need to choose a Loader Material Library : FE")	
#endif