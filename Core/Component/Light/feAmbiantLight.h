#pragma once

#include "feLight.h"

namespace FrogEngine {
	namespace Component {
		namespace Light {

			class feAmbiantLight : public feLight
			{
			public:
				// Ctor / Dtor
				feAmbiantLight(float ambiant);
				feAmbiantLight(Math::Vector4d color = INITIAL_COLOR, float ambiant = INITIAL_AMBIANT);
				~feAmbiantLight();

				void Init(Object::feObject* node) {};

				// Functions
				virtual shaderLight CreateShaderStruct();
			};
		} // namespace Light
	} //namespace Object
} //namespace FrogEngine