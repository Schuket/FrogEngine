#include "feCollider.h"

#include "feMotionState.h"

#include "Core\Object\feObject.h"
#include "Core\Object\feTransform.h"
#include "Core\System\Physics\fePhysicsManager.h"
#include "Core\Physics\feBoundingSphere.h"

#include "Logger/Logger.h"
#include "Math/Vector3d.h"
#include "Math/Matrix4.h"
#include "Math/Tools.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Physics
		{
			feCollider::feCollider(feCollider const& copy)
				:feComponent(copy)
			{
				_isDynamic = copy._isDynamic;
				_mass = copy._mass;
				_localInertia = copy._localInertia;

				_collisionEvent = copy._collisionEvent;
				_updateOwner = copy._updateOwner;
			}

			feCollider::~feCollider()
			{
				if (_rigidBody)
				{
					delete _rigidBody;
					_rigidBody = nullptr;
				}
				if (_collisionShape)
				{
					delete _collisionShape;
					_collisionShape = nullptr;
				}

				if (_motionState)
				{
					delete _motionState;
					_motionState = nullptr;
				}
			}

			void feCollider::ResetForces()
			{
				if (!_rigidBody)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::ResetForces -> Set your Collider component to an Object before doing anything to it");
					return;
				}

				_rigidBody->clearForces();
			}

			void feCollider::SetTranslationFreezeRatio(float trsX, float trsY, float trsZ)
			{
				if (!_rigidBody)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::SetTranslationFreezeRatio -> Set your Collider component to an Object before doing anything to it");
					return;
				}

				trsX = Math::Tools::ReverseRatio(Math::Tools::ToRatio(trsX));
				trsY = Math::Tools::ReverseRatio(Math::Tools::ToRatio(trsY));
				trsZ = Math::Tools::ReverseRatio(Math::Tools::ToRatio(trsZ));

				_rigidBody->setLinearFactor(btVector3(trsX, trsY, trsZ));
			}

			void feCollider::SetRotationFreezeRatio(float rotX, float rotY, float rotZ)
			{
				if (!_rigidBody)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::SetRotationFreezeRatio -> Set your Collider component to an Object before doing anything to it");
					return;
				}

				rotX = Math::Tools::ReverseRatio(Math::Tools::ToRatio(rotX));
				rotY = Math::Tools::ReverseRatio(Math::Tools::ToRatio(rotY));
				rotZ = Math::Tools::ReverseRatio(Math::Tools::ToRatio(rotZ));

				_rigidBody->setAngularFactor(btVector3(rotX, rotY, rotZ));
			}

			void feCollider::EnableKinematic(bool state)
			{
				if (!_rigidBody)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::EnableKinematic -> Set your Collider component to an Object before doing anything to it");
					return;
				}

				if (state)
				{
					_rigidBody->setCollisionFlags(_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
					_rigidBody->setActivationState(DISABLE_DEACTIVATION);
					return;
				}

				_rigidBody->setCollisionFlags(_rigidBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
				_rigidBody->setActivationState(WANTS_DEACTIVATION);
				
			}

			bool feCollider::IsKinematic()
			{
				if (!_rigidBody)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::IsKinematic -> Set your Collider component to an Object before doing anything to it");
					return false;
				}

				if (_rigidBody->getCollisionFlags() == btCollisionObject::CF_KINEMATIC_OBJECT)
					return true;

				return false;
			}

			void feCollider::SetColliderTransform(Math::Matrix4 transform)
			{
				if (!_rigidBody)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::SetColliderTransform -> Set your Collider component to an Object before doing anything to it");
					return;
				}

				btTransform newtrs;
				newtrs.setFromOpenGLMatrix(transform.DataArray());
				_rigidBody->setCenterOfMassTransform(newtrs);
			}

			//private 

			void feCollider::Create(float mass)
			{
				if (!_collisionShape)
				{
					Logging::Logger::Instance().Log(Logging::CRITICAL, "feCollider::Create -> _collisionShape not created ...");
					return;
				}

				_typeID = typeid(feCollider).hash_code();
				_type = ComponentType::Collider;

				_mass = mass;
				_isDynamic = (_mass != 0.f);

				_localInertia = btVector3(0, 0, 0);
				if (_isDynamic)
					_collisionShape->calculateLocalInertia(_mass, _localInertia);
			}

			void feCollider::Init(Object::feObject* node)
			{
				if (node == nullptr)
					return;

				_motionState = new feMotionState(node, &node->GetCollider()->GetTransform(), this);
				//_motionState = new btDefaultMotionState(_transform);
				btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(_mass, _motionState, _collisionShape, _localInertia);
				_rigidBody = new btRigidBody(rigidBodyInfo);
				_rigidBody->setUserPointer(this);

				node->GetEventOnTransformChange().Bind<feMotionState, &feMotionState::UpdateBulletColliderTransform>((feMotionState*)_motionState);
			}

		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine