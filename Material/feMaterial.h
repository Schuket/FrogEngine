#ifdef MATERIAL_EXPORTS
#define MATERIAL_WRAPPER __declspec(dllexport)
#else
#define MATERIAL_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "Math/Vector3d.h"
#include "Math/Vector4d.h"
#include "RHI/RHI.h"

using namespace Math;

namespace FrogEngine
{
	struct shaderMtl
	{
		Vector4d transmissFilter;
		Vector4d ambiant;
		Vector4d diffuse;
		Vector4d specular;
		Vector4d emissive;

		float shiningness;
		float refractionAngle;
		float alphaCoeff;
		float alphaInverse;

		int illum;
	};

	class feMaterial
	{
	public:
		// Ctor / Dtor
		MATERIAL_WRAPPER feMaterial();
		MATERIAL_WRAPPER feMaterial(feMaterial const& copy);
		MATERIAL_WRAPPER ~feMaterial();

		// Functions
		MATERIAL_WRAPPER void UpdateBufferObject();
		MATERIAL_WRAPPER shaderMtl GetShaderStruct();
		MATERIAL_WRAPPER virtual void BindTexture(uint32_t const& prgID);
		MATERIAL_WRAPPER virtual void UnbindTexture();

		// Variables
		float _ns; // specularExponent -> shiningness
		float _ni; // index refraction
		float _d;  // transparent
		float _tr; // transparent reverse

		Vector3d _tf; // transmission filter
		Vector3d _ka; // constante ambient
		Vector3d _kd; // constante diffuse
		Vector3d _ks; // constante specular
		Vector3d _ke; // constante emissive

		int _illum; // illum

		std::string _mapKd; // map_kd
		std::string _pathDirectory;
		std::string _name;

		feTexture _texture;
		feBufferObject _bObject;
	};
} // namespace FrogEngine