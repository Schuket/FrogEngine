#include "feCapsuleCollider.h"

#include "Math/Vector3d.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Physics
		{
			feCapsuleCollider::feCapsuleCollider(float radius, float height, float mass)
			{
				_collisionShape = new btCapsuleShape(radius, height);
				Create(mass);
			}

			feCapsuleCollider::feCapsuleCollider(feCapsuleCollider const& copy)
				:feCollider(copy)
			{
				_collisionShape = new btCapsuleShape(*((btCapsuleShape*)copy._collisionShape));
			}

			feCapsuleCollider* feCapsuleCollider::Clone()
			{
				return new feCapsuleCollider(*this);
			}
		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine