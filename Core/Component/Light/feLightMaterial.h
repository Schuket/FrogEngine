#ifdef CORE_EXPORTS
#define LIGHTMATERIAL_WRAPPER __declspec(dllexport)
#else
#define LIGHTMATERIAL_WRAPPER __declspec(dllimport)
#endif

#pragma once

#define INITIAL_INTENSITY 20.0f
#define INITIAL_AMBIANT 0.01f

#include "Math\Vector4d.h"

namespace FrogEngine 
{
	namespace Material 	
	{
		class feLightMaterial
		{
		public:
			// Ctor / Dtor
			feLightMaterial();
			feLightMaterial(Math::Vector4d Color);
			~feLightMaterial();

			// Functions
			#pragma region Getter/Setter

			// Return the color
			LIGHTMATERIAL_WRAPPER Math::Vector4d GetColor() const;
			// Return the intensity
			LIGHTMATERIAL_WRAPPER float GetIntensity() const;
			// Return the ambiant
			LIGHTMATERIAL_WRAPPER float GetAmbiant() const;
	
			/* Set the color
			* color : the new color
			*/
			LIGHTMATERIAL_WRAPPER void SetColor(Math::Vector4d color);
			/* Set the intensity
			* value : the new intensity
			*/
			LIGHTMATERIAL_WRAPPER void SetIntensity(float value);
			/* Set the ambiant
			* value : the new ambiant
			*/
			LIGHTMATERIAL_WRAPPER void SetAmbiant(float value);
			
			#pragma endregion
		
		private:
			// Variables
			Math::Vector4d _color;
			float _intensity = INITIAL_INTENSITY;
			float _ambiant = INITIAL_AMBIANT;
		};
	} // namespace Light
} //namespace FrogEngine