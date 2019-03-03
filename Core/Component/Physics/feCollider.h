#pragma once

#ifdef CORE_EXPORTS
#define PHYSICS_ACOLLIDER __declspec(dllexport) 
#else
#define PHYSICS_ACOLLIDER __declspec(dllimport) 
#endif

#include "btBulletDynamicsCommon.h"

#include "Core/Component/feComponent.h"

#include "Tools/feEvent.h"

namespace Math
{
	struct Vector3d;
	struct Matrix4;
}

namespace FrogEngine
{
	namespace System
	{
		namespace Physics
		{
			class fePhysicsManager;
		}
	}

	namespace Object
	{
		class feTransform;
	}

	namespace Component
	{
		namespace Physics
		{

			class feCollider abstract: public feComponent
			{
			public:
				PHYSICS_ACOLLIDER feCollider() = default;
				PHYSICS_ACOLLIDER virtual ~feCollider();

				PHYSICS_ACOLLIDER feEvent<void(feCollider*)>& GetCollisionEvent() { return _collisionEvent; }

				virtual feCollider* Clone() = 0;
				//Clear all forces apply to this collider (ex : gravity, ...)
				PHYSICS_ACOLLIDER void ResetForces();
				//Freeze translation in axis with ratio from 0 to 1
				PHYSICS_ACOLLIDER void SetTranslationFreezeRatio(float trsX, float trsY, float trsZ);
				//Freeze rotation in axis with ratio from 0 to 1
				PHYSICS_ACOLLIDER void SetRotationFreezeRatio(float rotX, float rotY, float rotZ);

				PHYSICS_ACOLLIDER void EnableKinematic(bool state);

				PHYSICS_ACOLLIDER bool IsKinematic();
				PHYSICS_ACOLLIDER bool IsDynamic()  { return _isDynamic; }

				PHYSICS_ACOLLIDER void SetColliderTransform(Math::Matrix4 transform);

				bool IsUpdatingOwner()		{ return _updateOwner; };
				void SetUpdateOwner(bool b) { _updateOwner = b; };

			protected:
				feCollider(feCollider const& copy);
				friend System::Physics::fePhysicsManager;

				//Functions
				void Create(float mass);
				virtual void Init(Object::feObject* node);

				//Event
				feEvent<void(feCollider*)> _collisionEvent;

				//Variables
				bool _updateOwner = false;

				float _mass;
				bool _isDynamic;	

				//Bullet Variable
				btCollisionShape* _collisionShape;
				btRigidBody* _rigidBody;
				btMotionState* _motionState;

				btVector3 _localInertia;
			};

		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine
