#ifdef CORE_EXPORTS
#define COMPONENT_WRAPPER __declspec(dllexport)
#else
#define COMPONENT_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <cstring>
#include "../System/feSerializeManager.h"

namespace FrogEngine {
	namespace Object {
		class feObject;
		} // namespace Object
	
	namespace Component	{
		namespace Video {
			class feCamera;
			} // namespace Video
		
		enum class ComponentType
		{
			None = 0,
			EditorCamera,
			Camera,
			Mesh,
			Light,
			Collider
		};

		class COMPONENT_WRAPPER feComponent
		{
		public:
			feComponent() = default;
			feComponent(feComponent const& copy);
			virtual ~feComponent();

			/* Init the component when he is attaching with an object
			* node : the object who has the component
			*/
			virtual void Init(Object::feObject* node) {};

			virtual feComponent* Clone() = 0;

#pragma region Getter/Setter
			// Return the Hash Code ID 
			std::size_t GetTypeID() const;
			// Return the type of component
			ComponentType GetType() const;
			// Return the owner of this component
			Object::feObject* GetOwner() const;

			/* Set the owner of this component
			* newOwner : the new owner
			*/
			void SetOwner(Object::feObject* const& owner);
#pragma endregion
			// Save the component in XML file with Cereal lib
			template <class Archive>
			void Save(Archive & ar) const;

		protected:
			std::size_t _typeID;
			ComponentType _type;
			Object::feObject* _owner;
		};

	} //namespace Component
} //namespace FrogEngine

#include "feComponent.inl"