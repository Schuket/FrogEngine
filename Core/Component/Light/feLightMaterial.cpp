#include "feLightMaterial.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace Material
	{
		feLightMaterial::feLightMaterial()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightMaterial is creating. . .");
			_color = Math::Vector4d(1.f, 1.f, 1.f, 1.f);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightMaterial created !");
		}

		feLightMaterial::feLightMaterial(Math::Vector4d color)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightMaterial is creating. . .");
			_color = color;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightMaterial created !");
		}

		feLightMaterial::~feLightMaterial()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightMaterial is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightMaterial deleted !");
		}

#pragma region Getter/Setter

		Math::Vector4d feLightMaterial::GetColor() const
		{ 
			return _color; 
		}

		float feLightMaterial::GetIntensity() const 
		{ 
			return _intensity; 
		}

		float feLightMaterial::GetAmbiant() const 
		{ 
			return _ambiant; 
		}

		void feLightMaterial::SetColor(Math::Vector4d color) 
		{ 
			_color = color; 
		}

		void feLightMaterial::SetIntensity(float value) 
		{ 
			_intensity = value; 
		}

		void feLightMaterial::SetAmbiant(float value)
		{
			if (_ambiant > 1.f)
				_ambiant = 1.f;

			else if (_ambiant < 0.f)
				_ambiant = 0.f;

			else
				_ambiant = value; 
		}

#pragma endregion
	} //namespace Light
} //namespace FrogEngine