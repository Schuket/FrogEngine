#pragma once

#pragma once

#ifdef CORE_EXPORTS
#define PHYSICS_CAPSULE_COLLIDER __declspec(dllexport) 
#else
#define PHYSICS_CAPSULE_COLLIDER __declspec(dllimport) 
#endif

#include "feCollider.h"

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
			class feCapsuleCollider : public feCollider
			{
			public:
				//Functions
				PHYSICS_CAPSULE_COLLIDER feCapsuleCollider(float radius = 1.f, float height = 2.f, float mass = 1.f);
				PHYSICS_CAPSULE_COLLIDER feCapsuleCollider(feCapsuleCollider const& copy);
				PHYSICS_CAPSULE_COLLIDER feCapsuleCollider* Clone();
			};

		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine