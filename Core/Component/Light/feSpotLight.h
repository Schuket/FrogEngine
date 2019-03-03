#ifdef CORE_EXPORTS
#define SPOTLIGHT_WRAPPER __declspec(dllexport)
#else
#define SPOTLIGHT_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "feDirectionalLight.h"

#define INITIAL_FOV 12.f

namespace FrogEngine 
{
	namespace Component 
	{
		namespace Light 
		{
			class feSpotLight : public feDirectionalLight
			{
			public:
				// Ctor / Dtor
				/* Create feSpotLight
				* fov : the field of view of this light
				*/
				SPOTLIGHT_WRAPPER feSpotLight(float fov);
				/* Create feSpotLight
				* direction : the direction of this spot
				* fov : the field of view of this light
				*/
				SPOTLIGHT_WRAPPER feSpotLight(Math::Vector3d direction, float fov);
				/* Create feSpotLight
				* color : the color of this light
				* direction : the direction of this spot
				* fov : the field of view of this light
				*/
				SPOTLIGHT_WRAPPER feSpotLight(Math::Vector4d color = INITIAL_COLOR, Math::Vector3d dir = INITIAL_DIR, float fov = INITIAL_FOV);
				~feSpotLight();
				
				void Init(Object::feObject* node) {};

				feSpotLight* Clone();

				// Functions
				#pragma region Getter/Setter

				// Return the fov
				SPOTLIGHT_WRAPPER float GetFov();
				/* Set the fov 
				* angle : the new angle of the fov
				*/
				SPOTLIGHT_WRAPPER void SetFov(float angle);
				
				#pragma endregion

				virtual shaderLight CreateShaderStruct() final;

				template <class Archive>
				void Save(Archive & ar) const
				{
					std::string type = "feSpotLight";

					ar(CEREAL_NVP(type));
					ar(CEREAL_NVP(_fov));
				}

			protected:
				feSpotLight(feSpotLight const& copy);
				// Variables
				float _fov;
			};
		} // namespace Light
	} //namespace Object
} //namespace FrogEngine