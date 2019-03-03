#ifdef CORE_EXPORTS
#define SCENEMANAGER_WRAPPER __declspec(dllexport)
#else
#define SCENEMANAGER_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <vector>

#include "../Component/Light/feLight.h"

namespace FrogEngine 
{
	namespace Object
	{
		class feObject;
	} // namespace Object

	namespace Component
	{
		class feComponent;

		namespace Video
		{
			class feEditorCamera;
			class feCamera;
		} // namespace Video
	} // namespace Component

	namespace System 
	{
		class feScene;
		class feResourceManager;
		class feInputManager;
		class feLightManager;

		namespace Physics
		{
			class fePhysicsManager;
		}

		namespace Video 
		{
			class feDriver;
		} // namespace Video

		class feSceneManager
		{
		public:
			// Ctor / Dtor
			feSceneManager(feSceneManager const&) = delete;
			feSceneManager(feSceneManager&&) = delete;
			~feSceneManager();

			static feSceneManager* Create();

			// Functions
			#pragma region Getter/Setter

				feLightManager* GetLightManager() const;
				// Return the Editor Camera
				SCENEMANAGER_WRAPPER Object::feObject* GetEditorCamera() const;
				// Return the Resource Manager
				SCENEMANAGER_WRAPPER System::feResourceManager* GetRessourceLoader() const;
				int GetSceneIndex() const;

				std::vector<feScene*>& GetScenes();
				// Return the current scene
				SCENEMANAGER_WRAPPER feScene* GetCurrentScene();

				void SetDefaultParameters(unsigned int const& width, unsigned int const& height, Video::feDriver* const& drv);
				void SetObjectInScene(Object::feObject* objToSet, Object::feObject* const& parent);
				void SetInputManager(feInputManager* const& inputMgr);
				void SetPhysicsManager(Physics::fePhysicsManager* phyMgr) { _phyMgr = phyMgr; }
			#pragma endregion

			feScene* AddScene();
			feScene* AddSimulatorScene();
			void RemoveSimulatorScene();
			/* Create an object in the current scene 
			* parent : Fairly explicite ? No ? Just for you, parent is the parent object. If the parent == nullptr, the object will be root's child.
			*/
			SCENEMANAGER_WRAPPER Object::feObject* CreateObject(Object::feObject* parent = nullptr);
			/* Add a component to an object 
			* node : the object who must receive the component
			* comp : the component
			*/
			SCENEMANAGER_WRAPPER void AddComponent(Object::feObject* node, Component::feComponent* comp);
			// Save the current scene in a XML file
			SCENEMANAGER_WRAPPER void SaveCurrentScene();

			void Draw(Component::Video::feCamera* cam);
			void Shutdown();

			void HookMouseInputController(feInputManager* classPtr);

		private:
			// Ctor
			feSceneManager();

			//Functions
			void LeftMouseClick(float pX, float pY);
			
			// Variables
			std::vector<feScene*> _scenes;
			unsigned int _idxActiveScene;
			unsigned int _idxEditorScene;

			feLightManager* _lightMgr;
			Video::feDriver* _drv;
			Object::feObject* _editorCam;
			feResourceManager* _resMgr;
			feInputManager* _inputMgr;
			Physics::fePhysicsManager* _phyMgr;
		};
	} //namespace System
} //namespace FrogEngine