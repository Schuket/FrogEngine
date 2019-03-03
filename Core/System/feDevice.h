#ifdef CORE_EXPORTS
#define CORE_WRAPPER __declspec(dllexport)
#else
#define CORE_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "WindowEvent\WindowEvent.h"
#include "Time/Time.h"

namespace FrogEngine
{
	namespace System 
	{
		namespace Video
		{
			class feDriver;
		} // namespace Video

		namespace Physics
		{
			class fePhysicsManager;
		} // namespace Physics
		
		class feSceneManager;
		class feInputManager;

		class feDevice
		{
		public:
			// Ctor / Dtor
			feDevice(feDevice const&) = delete;
			feDevice(feDevice&&) = delete;
			CORE_WRAPPER ~feDevice();

			//Create Device
			CORE_WRAPPER static feDevice* Create();

			// Functions
			#pragma region Getter/Setter
				/*Init all managers
				* HWND : Handle ID to create a window 
				*/
				CORE_WRAPPER void SetDefaultParameters(HWND id = nullptr);
				/*Set _hasOnSimulation value
				* b : true -> in simulation, false -> out simulation
				*/
				CORE_WRAPPER void SetHasOnSimulation(bool const& b);
				//Getter feSceneManager
				CORE_WRAPPER feSceneManager* GetScnMgr() const;
				feInputManager* GetInputMgr() const;
				Time* GetTime() const;
				//Getter Window
				CORE_WRAPPER Window* GetWindow() const;
			#pragma endregion

			// Launch the simulation
			CORE_WRAPPER void StartSimulation();
			// Stop the simulation
			CORE_WRAPPER void StopSimulation();

			// Launch th renderer loop 
			CORE_WRAPPER void Run();
			CORE_WRAPPER void RunInit();
			CORE_WRAPPER void Shutdown();
		private:
			// Ctor
			feDevice();

			// Variables
			Video::feDriver* _driver;
			feSceneManager* _scnMgr;
			feInputManager* _inputMgr;
			Physics::fePhysicsManager* _physicsMgr;

			Window* _window;
			Time* _time;

			bool _hasOnSimulation = true;
		};

	} // namespace System
} //namespace FrogEngine