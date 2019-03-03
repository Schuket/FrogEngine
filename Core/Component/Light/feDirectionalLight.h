#ifdef CORE_EXPORTS
#define DIRECTIONALLIGHT_WRAPPER __declspec(dllexport)
#else
#define DIRECTIONALLIGHT_WRAPPER __declspec(dllimport)
#endif

#pragma once

#define INITIAL_DIR Math::Vector3d(0.f, 0.f, -1.f)

#include "feLight.h"

#include "Math\Vector3d.h"
#include "Math\Vector4d.h"

namespace FrogEngine 
{
	namespace Component
	{
		namespace Light 
		{
			class feDirectionalLight : public feLight
			{
			public:
				// Ctor / Dtor
				/* Create a feDirectionalLight
				* direction : the direction of this light
				*/
				DIRECTIONALLIGHT_WRAPPER feDirectionalLight(Math::Vector3d direction);
				/* Create a feDirectionalLight
				* color : the color of this light
				* direction : the direction of this light
				*/
				DIRECTIONALLIGHT_WRAPPER feDirectionalLight(Math::Vector4d color = INITIAL_COLOR, Math::Vector3d direction = INITIAL_DIR);
				~feDirectionalLight();

				virtual void Init(Object::feObject* node) {};

				virtual feDirectionalLight* Clone();

				// Functions
				#pragma region Getter/Setter
				// Return the direction
				DIRECTIONALLIGHT_WRAPPER Math::Vector3d GetDirection();
				/* Set the direction
				* dir : the new direction
				*/
				DIRECTIONALLIGHT_WRAPPER void SetDirection(Math::Vector3d dir);
				
				#pragma endregion

				virtual shaderLight CreateShaderStruct() override;

				template <class Archive>
				void Save(Archive & ar) const;
			protected:
				feDirectionalLight(feDirectionalLight const& copy);
				// Variables
				Math::Vector3d _dir = INITIAL_DIR;
			};

			
		} //namespace Light
	} //namespace Object
} //namespace FrogEngine

#include "feDirectionalLight.inl"