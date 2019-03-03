#include "feAmbiantLight.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Light
		{
			feAmbiantLight::feAmbiantLight(float ambiant)
			:feLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feAmbiantLight is creating. . .");
				_typeID = typeid(feAmbiantLight).hash_code();
				_type = ComponentType::Light;
				_mat.SetAmbiant(ambiant);
				_idLight = AMBIANT;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feAmbiantLight created !");
			}

			feAmbiantLight::feAmbiantLight(Math::Vector4d color, float ambiant)
			:feLight(color)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feAmbiantLight is creating. . .");
				_typeID = typeid(feAmbiantLight).hash_code();
				_type = ComponentType::Light;
				_mat.SetAmbiant(ambiant);
				_idLight = AMBIANT;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feAmbiantLight created !");
			}

			feAmbiantLight::~feAmbiantLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feAmbiantLight is deleting. . .");
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feAmbiantLight deleted !");
			}

			shaderLight feAmbiantLight::CreateShaderStruct()
			{
				shaderLight light;

				light.color = _mat.GetColor();
				light.ambiant = _mat.GetAmbiant();
				light.ID = _idLight;

				return light;
			}

		} // namespace Light
	} //namespace Object
} //namespace FrogEngine