#pragma once

#include "config.h"
#include "Error\RHIError.h"

using namespace FrogEngine;

#if defined _OPEN_GL_
#include "RHIOpenGL.h"
#elif defined _DIRECT_3D_
#include "RHID3D.h"
#else
#pragma	message("ERROR -> You need to choose a Graphic API : OPENGL / DIRECT3D / VULKAN")	
#endif