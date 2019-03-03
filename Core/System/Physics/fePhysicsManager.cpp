#include "fePhysicsManager.h"

#include "feDebugDrawer.h"

#include "../feScene.h"
#include "Core\Object\feObject.h"
#include "Core\Component\Physics\feCollider.h"

#include "Math\Vector3d.h"
#include "Tools\feEvent.h"
#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace System
	{
		namespace Physics
		{
			void feTickCallback(btDynamicsWorld* world, btScalar timeStep)
			{
				int manifoldNb = world->getDispatcher()->getNumManifolds();

				for (int i = 0; i < manifoldNb; i++)
				{
					btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
					const btCollisionObject* objA = contactManifold->getBody0();
					const btCollisionObject* objB = contactManifold->getBody1();

					FrogEngine::Component::Physics::feCollider* colliderA = (Component::Physics::feCollider*)objA->getUserPointer();
					FrogEngine::Component::Physics::feCollider* colliderB = (Component::Physics::feCollider*)objB->getUserPointer();		

					colliderA->GetCollisionEvent().Invoke(colliderB);
					colliderB->GetCollisionEvent().Invoke(colliderA);
				}
			}

			fePhysicsManager::~fePhysicsManager()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "fePhysicManager is deleting. . .");

				if (_dynamicsWorld)
				{
					delete _dynamicsWorld;
					_dynamicsWorld = nullptr;
				}
				
				if (_collisionConfig)
				{
					delete _collisionConfig;
					_collisionConfig = nullptr;
				}
				if (_dispatcher)
				{
					delete _dispatcher;
					_dispatcher = nullptr;
				}
				if (_broadphaseInterface)
				{
					delete _broadphaseInterface;
					_broadphaseInterface = nullptr;
				}
				if (_constraintSolver)
				{
					delete _constraintSolver;
					_constraintSolver = nullptr;
				}
				if (_debugDrawer)
				{
					delete _debugDrawer;
					_debugDrawer = nullptr;
				}

				_collisionShapes.clear();

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "fePhysicManager deleted !");
			}

			fePhysicsManager* fePhysicsManager::Create()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "fePhysicManager is creating. . .");

				fePhysicsManager* PhyMgr = new fePhysicsManager();

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "fePhysicManager created !");
				return PhyMgr;
			}

			void fePhysicsManager::Init()
			{
				_collisionConfig = new btDefaultCollisionConfiguration();
				_dispatcher = new	btCollisionDispatcher(_collisionConfig);
				_broadphaseInterface = new btDbvtBroadphase();
				_constraintSolver = new btSequentialImpulseConstraintSolver();

				_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _broadphaseInterface, _constraintSolver, _collisionConfig);
				_dynamicsWorld->setInternalTickCallback(feTickCallback);
				_dynamicsWorld->setGravity(GRAVITY_VECTOR);

				_debugDrawer = new feDebugDrawer();
				_dynamicsWorld->setDebugDrawer(_debugDrawer);
				_debugDrawer->setDebugMode(_debugDrawer->DBG_DrawAabb);
			}

			void fePhysicsManager::Simulate(float deltaTime)
			{
				_dynamicsWorld->stepSimulation(deltaTime, SIMULATION_TICK);
			}

			void fePhysicsManager::DrawPhysicsGizmo()
			{
				_dynamicsWorld->debugDrawWorld();
				_debugDrawer->Draw();
			}

			void fePhysicsManager::ManageCollider(FrogEngine::Component::Physics::feCollider* collider)
			{
				if (!collider)
					return;
				if (IsManaged(collider))
					return;

				_collisionShapes.push_back(collider);
				_dynamicsWorld->addRigidBody(collider->_rigidBody);
			}

			void fePhysicsManager::UnManageCollider(FrogEngine::Component::Physics::feCollider* collider)
			{
				if (!collider)
					return;

				std::vector<Component::Physics::feCollider*>::iterator it = _collisionShapes.begin();
				std::vector<Component::Physics::feCollider*>::iterator end = _collisionShapes.end();

				for (; it != end; it++)
				{
					if ((*it) == collider)
					{
						_dynamicsWorld->removeRigidBody(collider->_rigidBody);
						_collisionShapes.erase(it);
					}
				}
			}

			void fePhysicsManager::ManageScene(feScene* scn)
			{
				if (!scn)
					return;

				ClearAllManagedCollider();

				std::vector<Object::feObject*> phyObj = scn->GetPhysicsObjects();

				std::vector<Object::feObject*>::iterator it = phyObj.begin();
				std::vector<Object::feObject*>::iterator end = phyObj.end();

				for (; it != end; it++)
				{
					Component::Physics::feCollider* comp = (*it)->GetComponent<Component::Physics::feCollider>();

					if (comp)
					{
						ManageCollider(comp);
					}
				}
			}

			bool fePhysicsManager::IsManaged(FrogEngine::Component::Physics::feCollider* collider)
			{
				if (!collider)
					return false;

				std::vector<Component::Physics::feCollider*>::iterator it = _collisionShapes.begin();
				std::vector<Component::Physics::feCollider*>::iterator end = _collisionShapes.end();

				for (; it != end; it++)
				{
					if ((*it) == collider)
						return true;
				}
				return false;
			}

			void fePhysicsManager::ClearAllManagedCollider()
			{
				std::vector<Component::Physics::feCollider*>::const_iterator it = _collisionShapes.begin();
				std::vector<Component::Physics::feCollider*>::const_iterator end = _collisionShapes.end();

				for (; it != end; it++)
					_dynamicsWorld->removeRigidBody((*it)->_rigidBody);
				
				_collisionShapes.clear();
			}

			//Private
			fePhysicsManager::fePhysicsManager()
			{
				_collisionConfig = nullptr;
				_dispatcher = nullptr;
				_broadphaseInterface = nullptr;
				_constraintSolver = nullptr;
				_dynamicsWorld = nullptr;
			}

		} //namespace Physics
	} //namespace System
} //namespace FrogEngine
