#pragma once

#include <map>

#include "RHI/RHI.h"

namespace FrogEngine 
{
	namespace Component
	{
		namespace Video
		{
			class feCamera;
		} // namespace Video
	} // namespace Component

	namespace System 
	{	
		class feSceneManager;

		namespace Video 
		{
			class feDriver
			{
			public:
				// Ctor / Dtor
				feDriver(feDriver const&) = delete;
				feDriver(feDriver&&) = delete;
				~feDriver();
		
				static feDriver* Create();

				// Functions
				#pragma region Getter/Setter
					feShader* GetProgramByName(std::string const& name);
		
					void SetDefaultParameters();
					void SetSceneManager(feSceneManager* const& feScnMgr);
				#pragma endregion
		
				void Shutdown();
				void Draw(feSceneManager* feScnMgr, Component::Video::feCamera* cam);
		
				feShader* LoadShader(std::string const& name);
		
			private:
				// Ctor
				feDriver();
		
				// Variables
				feSceneManager* _scnMgr;
				std::map<std::string, feShader*> _shaders;
			};
		} //namespace Video
	} //namespace System
} //namespace FrogEngine