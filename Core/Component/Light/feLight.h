#ifdef CORE_EXPORTS
#define LIGHT_WRAPPER __declspec(dllexport)
#else
#define LIGHT_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "Math\Vector4d.h"
#include "feLightMaterial.h"

#include "../feComponent.h"

#define INITIAL_COLOR Math::Vector4d(1.f, 1.f, 1.f, 1.f)

namespace FrogEngine 
{
	namespace System
	{
		class feLightManager;
	}

	namespace Component
	{
		namespace Light 
		{
			enum LIGHT_ID
			{
				POSITION = 1,
				DIRECTION,
				SPOT,
				AMBIANT
			};

			struct shaderLight
			{
				Math::Vector4d position;
				Math::Vector4d direction;
				Math::Vector4d color;
				float intensity;
				float ambiant;
				float fov;
				int ID;
			};

			class feLight : public feComponent
			{
			public:
				// Ctor / Dtor
				feLight(Math::Vector4d color = INITIAL_COLOR);
				feLight(feLight const& copy);
				~feLight();

				virtual void Init(Object::feObject* node) {};
				virtual feLight* Clone();

				// Functions
				#pragma region Getter/Setter

				// Return the material light
				LIGHT_WRAPPER Material::feLightMaterial& GetMaterial();
				/* Set the material light
				* mat : the new material light
				*/
				LIGHT_WRAPPER void SetMaterial(Material::feLightMaterial mat);
				#pragma endregion

				virtual shaderLight CreateShaderStruct();

				template <class Archive>
				void Save(Archive & ar) const;

			protected:

				// Variables
				Material::feLightMaterial _mat;
				LIGHT_ID _idLight = POSITION;
			};

		} // namespace Light
	} //namespace Object
} //namespace FrogEngine

#include "feLight.inl"