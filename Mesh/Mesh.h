#pragma once

#include "config.h"

#include "feMeshObj.h"
#include "feMeshSkybox.h"
#include "feMeshFbx.h"

#if defined _FE_
	#include "FE\FELoaderMesh.h"
	using namespace FrogEngine::FE;
#else
	#pragma	message("ERROR -> You need to choose a Loader Mesh Library : FE")	
#endif