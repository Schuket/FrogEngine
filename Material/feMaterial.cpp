#include "feMaterial.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	feMaterial::feMaterial()
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial is creating. . .");
		_ns = 50.f; 
		_ni = 0.f; 
		_d = 0.f; 
		_tr = 0.f; 

		_tf = Vector3d(0.f, 0.f, 0.f); 
		_ka = Vector3d(1.f, 1.f, 1.f); 
		_kd = Vector3d(1.f, 1.f, 1.f); 
		_ks = Vector3d(1.f, 1.f, 1.f);
		_ke = Vector3d(0.f, 0.f, 0.f); 

		_illum = 0; 

		_mapKd = ""; 
		_name = "Unnamed Material";

		_texture.SetSamplerName("Sampler");
		_texture.SetIdx(0);

		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial created !");
	}

	feMaterial::feMaterial(feMaterial const& copy)
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial[" + copy._name + "] is copying. . .");
		_texture = copy._texture;

		_ns = copy._ns;
		_ni = copy._ni;
		_d = copy._d;
		_tr = copy._tr;

		_tf = copy._tf;
		_ka = copy._ka;
		_kd = copy._kd;
		_ks = copy._ks;
		_ke = copy._ke;

		_illum = copy._illum; 

		_mapKd = copy._mapKd;
		_pathDirectory = copy._pathDirectory;
		_name = copy._name;

		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial[" + copy._name + "] copied !");
	}

	feMaterial::~feMaterial()
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial[" + _name + "] is deleting. . .");
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial[" + _name + "] deleted !");
	}

	void feMaterial::UpdateBufferObject()
	{
		shaderMtl mtlStruct = GetShaderStruct();

		_bObject.Update(&mtlStruct, sizeof(mtlStruct), 3);
	}

	shaderMtl feMaterial::GetShaderStruct()
	{
		shaderMtl material;

		material.transmissFilter = Math::Vector4d(_tf, 1.f);
		material.ambiant = Math::Vector4d(_ka, 1.f);
		material.diffuse = Math::Vector4d(_kd, 1.f);
		material.specular = Math::Vector4d(_ks, 1.f);
		material.emissive = Math::Vector4d(_ke, 1.f);

		material.shiningness = _ns;
		material.refractionAngle = _ni;
		material.alphaCoeff = _d;
		material.alphaInverse = _tr;

		material.illum = _illum;

		return material;
	}

	void feMaterial::BindTexture(uint32_t const& prgID)
	{
		_texture.Bind(prgID);
	}

	void feMaterial::UnbindTexture()
	{
		_texture.Unbind();
	}
}