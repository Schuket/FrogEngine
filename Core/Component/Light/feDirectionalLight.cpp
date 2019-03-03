#include "feDirectionalLight.h"

#include "Logger\Logger.h"
#include "Math\Vector3d.h"

namespace FrogEngine 
{
	namespace Component
	{
		namespace Light 
		{
			feDirectionalLight::feDirectionalLight(Math::Vector3d dir)
			:feLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDirectionalLight is creating. . .");
				_dir = dir;
				_typeID = typeid(feDirectionalLight).hash_code();
				_type = ComponentType::Light;
				_idLight = DIRECTION;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDirectionalLight created !");
			}

			feDirectionalLight::feDirectionalLight(feDirectionalLight const& copy)
				:feLight(copy)
			{
				_typeID = typeid(feDirectionalLight).hash_code();
				_type = ComponentType::Light;
				_dir = copy._dir;
			}

			feDirectionalLight::feDirectionalLight(Math::Vector4d color, Math::Vector3d dir)
			:feLight(color)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDirectionalLight is creating. . .");
				_dir = dir;
				_typeID = typeid(feDirectionalLight).hash_code();
				_type = ComponentType::Light;
				_idLight = DIRECTION;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDirectionalLight created !");
			}

			feDirectionalLight::~feDirectionalLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDirectionalLight is deleting. . .");
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDirectionalLight deleted !");
			}

			feDirectionalLight* feDirectionalLight::Clone()
			{
				return new feDirectionalLight(*this);
			}

#pragma region Getter/Setter

			Math::Vector3d feDirectionalLight::GetDirection() 
			{ 
				return _dir; 
			}

			void feDirectionalLight::SetDirection(Math::Vector3d dir) 
			{ 
				_dir = dir; 
			}

#pragma endregion

			shaderLight feDirectionalLight::CreateShaderStruct()
			{
				shaderLight light;

				light.direction = Math::Vector4d(_dir.X(), _dir.Y(), _dir.Z(), 0.f);
				light.color = _mat.GetColor();
				light.intensity = _mat.GetIntensity();
				light.ambiant = _mat.GetAmbiant();
				light.ID = _idLight;

				return light;
			}
		} // namespace Light
	} //namespace Object
} //namespace FrogEngine