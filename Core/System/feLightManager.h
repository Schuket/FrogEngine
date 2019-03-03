#pragma once

#define MAX_LIGHT 10

#include <array>

#include "RHI/RHI.h"

#include "../Component/Light/feLight.h"

namespace FrogEngine 
{
	namespace System 
	{
		struct multipleLightShader
		{
			std::array<Component::Light::shaderLight, MAX_LIGHT> lights;
			int lightNb;
		};
	
		class feLightManager
		{
		public:
			// Ctor / Dtor
			feLightManager();
			~feLightManager();
	
			feLightManager(feLightManager const&) = delete;
			feLightManager(feLightManager&&) = delete;
			feLightManager& operator=(feLightManager const&) =  delete;
			feLightManager& operator=(feLightManager&&) = delete;
			
			// Functions
			std::vector<Component::Light::feLight*>& GetLights();

			void UpdateBufferObject();

		private:
			// Functions
			multipleLightShader CreateShaderStruct();
	
			// Variables
			feBufferObject _bObject;
			std::vector<Component::Light::feLight*> _lights;
		};
	} //namespace System
} //namespace FrogEngine