#include "feLight.h"

#include "feLightMaterial.h"

#include "Core/Physics/feBoundingSphere.h"
#include "Core/Object/feObject.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Light
		{
			feLight::feLight(feLight const& copy)
				:feComponent(copy)
			{
				_typeID = typeid(feLight).hash_code();
				_type = ComponentType::Light;
				_mat = copy._mat;
				_idLight = copy._idLight;
			}

			feLight::feLight(Math::Vector4d color)
			: feComponent()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLight is creating. . .");
				_typeID = typeid(feLight).hash_code();
				_type = ComponentType::Light;
				_idLight = POSITION;
				_mat = Material::feLightMaterial(color);
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLight created !");
			}

			feLight::~feLight()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLight is deleting. . .");
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLight is deleted !");
			}

			feLight* feLight::Clone()
			{
				return new feLight(*this);
			}

#pragma region Getter/Setter

			Material::feLightMaterial& feLight::GetMaterial() 
			{ 
				return _mat; 
			}

			void feLight::SetMaterial(Material::feLightMaterial mat) 
			{ 
				_mat = mat; 
			}

#pragma endregion

			shaderLight feLight::CreateShaderStruct()
			{
				shaderLight light;

				light.position = Math::Vector4d(_owner->GetTransform().GetTranslation(), 1.f);
				light.color = _mat.GetColor();
				light.intensity = _mat.GetIntensity();
				light.ambiant = _mat.GetAmbiant();
				light.ID = _idLight;

				return light;
			}
		} // namespace Light
	} //namespace Object
} //namespace FrogEngine
