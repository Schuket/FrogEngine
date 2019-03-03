#ifdef CORE_EXPORTS
#define SCENE_WRAPPER __declspec(dllexport)
#else
#define SCENE_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <map>
#include <vector>

namespace FrogEngine 
{	
	namespace Object 
	{
		class feObject;
	} // namespace Object

	namespace Physics
	{
		class feRay;
	} // namespace Physics

	namespace Component
	{
		namespace Video
		{
			class feCamera;
		} // namespace Video
	} // namespace Component

	namespace System 
	{
		class feResourceManager;

		class feScene
		{
		public:
			// Ctor / Dtor
			feScene(feResourceManager* resMgr);
			~feScene();

			// Functions
				feScene* Clone();

			#pragma region Getter/Setter
				// Return the Main Camera
				SCENE_WRAPPER Object::feObject* GetMainCamera() const;
				// Return the original world (root)
				SCENE_WRAPPER Object::feObject* GetRoot() const;
				Object::feObject* GetSelectedObject() const;
				std::map<unsigned int, std::vector<Object::feObject*>> GetDrawableObjects();
				std::vector<Object::feObject*> GetPhysicsObjects();

				void SetSkybox(Object::feObject* const& cubeMap);
				void SetSelectedObject(Object::feObject* const&  obj);
				void SetMainCamera(Object::feObject* const&  obj);
			#pragma endregion

			void Draw(Component::Video::feCamera* const& cam);
			void AddDrawableObject(Object::feObject* objToSet);
			void RemoveObject(Object::feObject* objToDel);

			void AddPhysicObject(Object::feObject* objToSet);

			unsigned int IncreaseIDCount();

			void CheckComponents(Object::feObject* node);
		
		private:
			feScene(feScene const& copy);

			void SearchAndDeleteObject(Object::feObject* node, Object::feObject* objToDel);
			void UpdateIDCount(Object::feObject* objToSet);

			// Variables
			feResourceManager* _resMgr;
			Object::feObject* _cubeMap;
			Object::feObject* _root;
			Object::feObject* _selectedObject;
			Object::feObject* _mainCamera;


			std::map<unsigned int, std::vector<Object::feObject*>> _drawableObjects;
			std::vector<Object::feObject*> _physicsObjects;
			unsigned int _idCount = 0;
		};
	} //namesapce System
} //namesapce FrogEngine