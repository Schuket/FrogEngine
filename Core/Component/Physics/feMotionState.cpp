#include "feMotionState.h"

#include "Core/Component/Physics/feCollider.h"
#include "Core\Object\feTransform.h"
#include "Core\Object\feObject.h"

#include "Math\Quaternion.h"
#include "Math\Vector3d.h"
#include "Math\Matrix4.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Physics
		{
			feMotionState::feMotionState(Object::feObject* feObj, Object::feTransform* colliderTransform, feCollider* owner)
			: _obj(feObj), _offset(colliderTransform), _owner(owner)
			{
			}

			feMotionState::feMotionState(feMotionState& copy)
			{
				_obj = copy._obj;
				_owner = copy._owner;

				_offset->SetTranslation(copy._offset->GetLocalTranslation());
				_offset->SetScale(copy._offset->GetLocalScale());
				_offset->SetRotation(copy._offset->GetLocalRotation());
				_offset->SetOwner(copy._offset->GetOwner());
			}


			void feMotionState::UpdateBulletColliderTransform(Object::feTransform trs)
			{
				_owner->SetColliderTransform((trs.GetWorldMatrix() * _offset->GetLocalMatrix()));
				_owner->EnableKinematic(true);
				_owner->EnableKinematic(false);
			}


			//private:
			void feMotionState::getWorldTransform(btTransform& worldTrans) const
			{
				if (!_obj || !_offset)
					return;

				worldTrans.setFromOpenGLMatrix((_obj->GetTransform().GetWorldMatrix() * _offset->GetLocalMatrix()).DataArray());
			}

			void feMotionState::setWorldTransform(const btTransform& worldTrans)
			{
				if (!_obj || !_offset)
					return;

				btVector3 pos = worldTrans.getOrigin();
				btQuaternion rot = worldTrans.getRotation();

				Math::Vector3d rotated = _offset->GetLocalMatrix().Inverse().RecoverTranslation();
				rotated.Rotate(Math::Quaternion(rot.x(), rot.y(), rot.z(), rot.w()));

				Math::Quaternion newRot = Math::Quaternion(rot.x(), rot.y(), rot.z(), rot.w());
				Math::Vector3d newTrans = Math::Vector3d(pos.x(), pos.y(), pos.z()) + Math::Vector3d(rotated.X(), rotated.Y(), rotated.Z());

				_owner->SetUpdateOwner(true);
				_obj->GetTransform().SetTranslationAndRotation(newTrans, newRot);
			}
		}
	}
}