#include "feBoxCollider.h"

#include "Math/Vector3d.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Physics
		{

			feBoxCollider::feBoxCollider(Math::Vector3d scale, float mass)
			{
				_collisionShape = new btBoxShape(btVector3(scale.X(), scale.Y(), scale.Z()));
				Create(mass);
			}

			feBoxCollider::feBoxCollider(feBoxCollider const& copy)
				:feCollider(copy)
			{
				_collisionShape = new btBoxShape(*((btBoxShape*)copy._collisionShape));
			}

			feBoxCollider* feBoxCollider::Clone()
			{
				return new feBoxCollider(*this);
			}
		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine