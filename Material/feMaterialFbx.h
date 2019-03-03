#ifdef MATERIAL_EXPORTS
#define MATERIALFBX_WRAPPER __declspec(dllexport)
#else
#define MATERIALFBX_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "Math\Vector3d.h"
#include "RHI/RHI.h"
#include "feMaterial.h"

using namespace Math;

namespace FrogEngine
{ 
	class feMaterialFbx : public feMaterial
	{
	public:
		MATERIALFBX_WRAPPER feMaterialFbx();
		MATERIALFBX_WRAPPER feMaterialFbx(feMaterialFbx const& copy);
		MATERIALFBX_WRAPPER ~feMaterialFbx();

		MATERIALFBX_WRAPPER void BindTexture(uint32_t const& prgID);
		MATERIALFBX_WRAPPER void UnbindTexture();

		int _hasDiffuse;
		int _hasSpecular;
		int _hasNormal;

		feTexture _texDiffuse;
		feTexture _texSpecular;
		feTexture _texNormal;
	};
}