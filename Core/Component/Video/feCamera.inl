#include "feCamera.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Video
		{
			template <class Archive>
			void feCamera::Save(Archive & ar) const
			{
				std::string type = "feCamera";

				ar(CEREAL_NVP(type));
				ar(CEREAL_NVP(_width));
				ar(CEREAL_NVP(_height));
				ar(CEREAL_NVP(_near));
				ar(CEREAL_NVP(_far));
				ar(CEREAL_NVP(_fov));
			}
		}
	}
}