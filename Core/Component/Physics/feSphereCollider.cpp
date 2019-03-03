#include "feSphereCollider.h"

#include "Math/Vector3d.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Physics
		{

			feSphereCollider::feSphereCollider(float radius, float mass)
			{
				_collisionShape = new btSphereShape(radius);
				Create(mass);
			}

			feSphereCollider::feSphereCollider(feSphereCollider const& copy)
				:feCollider(copy)
			{
				_collisionShape = new btSphereShape(*((btSphereShape*)copy._collisionShape));
			}

			feSphereCollider* feSphereCollider::Clone()
			{
				return new feSphereCollider(*this);
			}
		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine