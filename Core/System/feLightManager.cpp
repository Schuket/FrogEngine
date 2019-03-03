
#include "feLightManager.h"

#include "../Component/Light/feSpotLight.h"
#include "../Component/Light/feAmbiantLight.h"

#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace System 
	{
		feLightManager::feLightManager()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightManager is creating. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightManager created !");
		}

		feLightManager::~feLightManager()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightManager is deleting. . .");

			_lights.clear();

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feLightManager deleted !");
		}

		multipleLightShader feLightManager::CreateShaderStruct()
		{
			multipleLightShader Struct;

			int size = (int)_lights.size();
			Struct.lightNb = size < MAX_LIGHT ? size : (int)MAX_LIGHT;

			int nbLight = Struct.lightNb;
			for (int idx = 0; idx < nbLight; ++idx)
				Struct.lights[idx] = (_lights[idx]->CreateShaderStruct());

			return Struct;
		}

		std::vector<Component::Light::feLight*>& feLightManager::GetLights()
		{
			return _lights;
		}

		void feLightManager::UpdateBufferObject()
		{
			multipleLightShader Struct = CreateShaderStruct();

			_bObject.Update(&Struct, sizeof(Struct), 2);
		}

	} //namespace System
} //namespace FrogEngine