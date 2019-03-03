#include "feSpotLight.h"

#include "../../Object/feObject.h"

#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace Component
	{
		namespace Light 
		{
			feSpotLight::feSpotLight(float fov)
			:feDirectionalLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight is creating. . .");
				_typeID = typeid(feSpotLight).hash_code();
				_type = ComponentType::Light;
				_fov = fov;
				_idLight = SPOT;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight created !");
			}

			feSpotLight::feSpotLight(feSpotLight const& copy)
				:feDirectionalLight(copy)
			{
				_type = ComponentType::Light;
				_fov = copy._fov;
				_typeID = typeid(feSpotLight).hash_code();
			}

			feSpotLight::feSpotLight(Math::Vector3d dir, float fov)
			:feDirectionalLight(dir)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight is creating. . .");
				_fov = fov;
				_typeID = typeid(feSpotLight).hash_code();
				_type = ComponentType::Light;
				_idLight = SPOT;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight created !");
			}

			feSpotLight::feSpotLight(Math::Vector4d color, Math::Vector3d dir,	float fov)
			:feDirectionalLight(color, dir)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight is creating. . .");
				_fov = fov;
				_typeID = typeid(feSpotLight).hash_code();
				_type = ComponentType::Light;
				_idLight = SPOT;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight created !");
			}

			feSpotLight::~feSpotLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight is deleting. . .");
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSpotLight deleted !");
			}

			feSpotLight* feSpotLight::Clone()
			{
				return new feSpotLight(*this);
			}

#pragma region Getter/Setter

			float feSpotLight::GetFov() 
			{ 
				return _fov; 
			}

			void feSpotLight::SetFov(float angle) 
			{ 
				_fov = angle; 
			}

#pragma endregion

			shaderLight feSpotLight::CreateShaderStruct()
			{
				shaderLight light;

				light.position = Math::Vector4d(_owner->GetTransform().GetTranslation(), 1.f);
				light.direction = Math::Vector4d(_dir.X(), _dir.Y(), _dir.Z(), 0.f);
				light.color = _mat.GetColor();
				light.intensity = _mat.GetIntensity();
				light.ambiant = _mat.GetAmbiant();
				light.fov = _fov;
				light.ID = _idLight;

				return light;
			}
		} // namespace Light
	} //namespace Object
} //namespace FrogEngine