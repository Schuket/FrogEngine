#ifdef CORE_EXPORTS
#define OBJECT_WRAPPER __declspec(dllexport)
#else
#define OBJECT_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <vector> 

#include "feTransform.h"
#include "../Component/Light/feLight.h"
#include "../Component/Video/feEditorCamera.h"

#include "Tools/feEvent.h"
#include "../System/feSerializeManager.h"

namespace FrogEngine 
{
	namespace Physics
	{
		class feRay;
		class feBoundingSphere;
	} // namespace Physics
	namespace System 
	{
		class feInputManager;
		class feSceneManager;
	} // namespace System

	namespace Object 
	{	
		class feTransform;

		class feObject
		{
		public:
			// Ctor / Dtor
			feObject();
			feObject(std::string const& name, feObject* parent = nullptr);
			~feObject();

			// Functions
			void UpdateWorldPos();
			void DrawCollider();

			void BindShaderCollider();
			void UnbindShaderCollider();

			feObject* Clone();

			#pragma region Getter/Setter
			// Return the object's name
			OBJECT_WRAPPER std::string GetName() const;
			// Return the object's parent
			OBJECT_WRAPPER feObject* GetParent() const;
			// Return the object's transform
			OBJECT_WRAPPER feTransform& GetTransform();
			// Return all children of this object
			OBJECT_WRAPPER std::vector<feObject*> GetChildren() const;
			// Return the collider by default
			OBJECT_WRAPPER Physics::feBoundingSphere* GetCollider() const;
			feEvent<void(feTransform)>& GetEventOnTransformChange();

			// Return the object's index 
			OBJECT_WRAPPER unsigned int GetID() const;
			/* Set the object's name
			* value : the new name 
			*/
			OBJECT_WRAPPER void SetName(std::string value);
			/* Set the object's parent
			* parent : the new parent
			*/
			OBJECT_WRAPPER void SetParent(feObject* const parent);
	
			#pragma endregion

			void SetID(unsigned int const& id);
			/* Add a child 
			* child : the new child
			*/
			OBJECT_WRAPPER void AddChild(feObject* const& child);
			void Draw(feShader* shader, unsigned int idxMesh);
			/* Remove a child
			* child : the child to remove
			*/
			OBJECT_WRAPPER void RemoveChild(feObject* const& child);
			
			// Return all object's components
			OBJECT_WRAPPER std::map<std::size_t, Component::feComponent*> GetComponent() const;
			
			template<typename T>
			T* GetComponent();
			
			template <class Archive>
			void Save(Archive & ar) const;

			template <class Archive>
			void Load(Archive & ar);

			/* Add a component in this object
			* component : the new component
			*/
			OBJECT_WRAPPER void AddComponent(Component::feComponent* const& component);
			void RemoveComponent(Component::feComponent* const& component);

			bool CheckRayCollision(Physics::feRay* ray);
			bool CheckRayCollisionWithObjectAndChildren(Physics::feRay* ray);

			void HookKeyboardInputController(System::feInputManager* classPtr);
			void UnHookKeyboardInputController(System::feInputManager* classPtr);


		protected:
			feObject(feObject const& copy);

			//Functions
			void MoveRight(float deltaTime);
			void MoveLeft(float deltaTime);
			void MoveForward(float deltaTime);
			void MoveBackward(float deltaTime);
			void MoveUp(float deltaTime);
			void MoveDown(float deltaTime);

			//Event
 			feEvent<void(feTransform)> _onTransformChange;

			// Variables
			std::string _name;
			feTransform _transform;

			feObject* _parent;
			std::vector<feObject*> _children;
			std::map<std::size_t, Component::feComponent*> _components;
			Physics::feBoundingSphere* _collider;

			unsigned int _id = 0;
		};
	} // namespace Object 
} //namespace FrogEngine

#include "feObject.inl"
