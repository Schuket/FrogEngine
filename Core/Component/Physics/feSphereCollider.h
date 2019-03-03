#pragma once

#ifdef CORE_EXPORTS
#define PHYSICS_SPHERE_COLLIDER __declspec(dllexport) 
#else
#define PHYSICS_SPHERE_COLLIDER __declspec(dllimport) 
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
			class feSphereCollider : public feCollider
			{
			public:
				//Functions
				PHYSICS_SPHERE_COLLIDER feSphereCollider(float radius = 1.f, float mass = 1.f);
				PHYSICS_SPHERE_COLLIDER feSphereCollider(feSphereCollider const& copy);
				PHYSICS_SPHERE_COLLIDER feSphereCollider* Clone();
			};

		} //namespace Physics
	} //namespace Component
} //namespace FrogEngine