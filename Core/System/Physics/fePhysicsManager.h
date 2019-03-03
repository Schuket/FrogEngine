#pragma once

#include <vector>

#include "btBulletDynamicsCommon.h"
	
#define GRAVITY_VECTOR btVector3(0.f, -9.8f, 0.f)
#define SIMULATION_TICK 100

namespace Math
{
	struct Vector3d;
}

namespace FrogEngine
{
	namespace Component
	{
		namespace Physics
		{
			class feCollider;
		} //namespace Physics
	} //namespace Component

	namespace System
	{
		class feScene;

		namespace Physics
		{
			//Called Each Tick that the physic will be Simulated
			void feTickCallback(btDynamicsWorld *world, btScalar timeStep);

			class feDebugDrawer;

			class fePhysicsManager
			{
			public:
				//Functions
				~fePhysicsManager();

				static fePhysicsManager* Create();

				void Init();
				void Simulate(float deltaTime);
				void DrawPhysicsGizmo();
				
				void ManageCollider(FrogEngine::Component::Physics::feCollider* collider);
				void UnManageCollider(FrogEngine::Component::Physics::feCollider* collider);

				void ManageScene(feScene* scn);
				
				bool IsManaged(FrogEngine::Component::Physics::feCollider* collider);

				void ClearAllManagedCollider();

			private:
				//Functions
				fePhysicsManager();

				//Variables
				btDefaultCollisionConfiguration* _collisionConfig;
				btCollisionDispatcher* _dispatcher;
				btBroadphaseInterface* _broadphaseInterface;
				btSequentialImpulseConstraintSolver* _constraintSolver;
				btDiscreteDynamicsWorld* _dynamicsWorld;

				std::vector<Component::Physics::feCollider*> _collisionShapes;

				feDebugDrawer* _debugDrawer;
			};

		} //namespace Physics
	} //namespace System
} //namespace FrogEngine