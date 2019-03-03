#include "feMaterialFbx.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	feMaterialFbx::feMaterialFbx()
		:feMaterial()
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterialFbx is creating. . .");

		_hasDiffuse = 0;
		_hasSpecular = 0;
		_hasNormal = 0;

		_texDiffuse = feTexture();
		_texDiffuse.SetIdx(0);
		_texDiffuse.SetSamplerName("u_DiffuseTexture");

		_texSpecular = feTexture();
		_texSpecular.SetIdx(1);
		_texSpecular.SetSamplerName("u_SpecularTexture");

		_texNormal = feTexture();
		_texNormal.SetIdx(2);
		_texNormal.SetSamplerName("u_NormalTexture");

		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterialFbx created !");
	}

	feMaterialFbx::feMaterialFbx(feMaterialFbx const& copy)
		:feMaterial(copy)
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterialFbx is copying. . .");

		_hasDiffuse = copy._hasDiffuse;
		_hasSpecular = copy._hasSpecular;
		_hasNormal = copy._hasNormal;

		_texDiffuse = copy._texDiffuse;
		_texSpecular = copy._texSpecular;
		_texNormal = copy._texNormal;

		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterialFbx copied !");
	}

	feMaterialFbx::~feMaterialFbx()
	{
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterialFbx is deleting. . .");
		Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterialFbx deleted !");
	}

	void feMaterialFbx::BindTexture(uint32_t const& prgID)
	{
		if (_hasDiffuse)
			_texDiffuse.Bind(prgID);

		if (_hasSpecular)
			_texSpecular.Bind(prgID);

		if (_hasNormal)
			_texNormal.Bind(prgID);
	}

	void feMaterialFbx::UnbindTexture()
	{
		if (_hasDiffuse)
			_texDiffuse.Unbind();

		if (_hasSpecular)
			_texSpecular.Unbind();

		if (_hasNormal)
			_texNormal.Unbind();
	}
}