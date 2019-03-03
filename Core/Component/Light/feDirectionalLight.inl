#include "feDirectionalLight.h"

#include "feSpotLight.h"
#include "Logger\Logger.h"
#include "Math\Vector3d.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Light
		{
			template <class Archive>
			void feDirectionalLight::Save(Archive & ar) const
			{
				//std::vector<float> dir = { _dir.X(), _dir.Y(), _dir.Z() };
				//
				//if (LIGHT_ID::SPOT == _idLight)
				//	_owner->GetComponent<Light::feSpotLight>()->Save(ar);
				//else
				//{
				//	std::string type = "feDirectionalLight";
				//	ar(CEREAL_NVP(type));
				//}
				//ar(CEREAL_NVP(dir));
			}
		}
	}
}