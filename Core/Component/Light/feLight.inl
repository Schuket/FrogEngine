#include "feLight.h"

#include "feDirectionalLight.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Light
		{
			template <class Archive>
			void feLight::Save(Archive & ar) const
			{
				std::string type = "feLight";
				
				switch (_idLight)
				{
				case LIGHT_ID::AMBIANT:
					type = "feAmbiantLight";
					ar(CEREAL_NVP(type));
					break;
				case LIGHT_ID::POSITION:
					ar(CEREAL_NVP(type));
					break;
				case LIGHT_ID::DIRECTION:
					_owner->GetComponent<Light::feDirectionalLight>()->Save(ar);
					break;
				case LIGHT_ID::SPOT:
					_owner->GetComponent<Light::feDirectionalLight>()->Save(ar);
					break;
				}
				
				std::vector<float> color = _mat.GetColor().DataVector();
				float intensity = _mat.GetIntensity();
				float ambiant = _mat.GetAmbiant();
				
				ar(CEREAL_NVP(color));
				ar(CEREAL_NVP(intensity));
				ar(CEREAL_NVP(ambiant));
			}
		}
	}
}