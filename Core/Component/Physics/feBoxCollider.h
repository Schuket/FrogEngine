#pragma once

#ifdef CORE_EXPORTS
#define PHYSICS_BOX_COLLIDER __declspec(dllexport) 
#else
#define PHYSICS_BOX_COLLIDER __declspec(dllimport) 
#endif

#include "feCollider.h"
#include "Math\Vector3d.h"

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
			class feBoxCollider : public feCollider
			{
			public:
				//Functions
				PHYSICS_BOX_COLLIDER feBoxCollider(Math::Vector3d scale = Math::Vector3d(1.f, 1.f, 1.f), float mass = 1.f);
				PHYSICS_BOX_COLLIDER feBoxCollider(feBoxCollider const& copy);

				PHYSICS_BOX_COLLIDER feBoxCollider* Clone();
			};

		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine