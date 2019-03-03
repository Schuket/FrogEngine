#ifdef CORE_EXPORTS
#define RAY_WRAPPER __declspec(dllexport)
#else
#define RAY_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <vector>

#include "Math\Vector3d.h"

namespace Math
{
	struct Vector2d;
} //namespace Math

namespace FrogEngine
{
	namespace Object
	{
		class feObject;
	} // namespace Object

	namespace Component
	{
		namespace Video
		{
			class feCamera;
		} // namespace Video
	} // namespace System

	namespace Physics
	{
		class feRay
		{
		public:
			//Ctor
			/* Create a ray 
			* mousePos : the mouse's position, the destination
			* cam : the camera component, the the beginning
			*/
			RAY_WRAPPER feRay(Math::Vector2d mousePos, Component::Video::feCamera* cam);

			//Functions
			/* Check if an specific object touched the ray
			* obj : the object for the check
			*/
			RAY_WRAPPER bool IsHiting(Object::feObject* obj);

			// Reinitialize the ray
			RAY_WRAPPER void Reset();

			// Return the first object hits by the ray
			RAY_WRAPPER Object::feObject* GetFirstObjectHit();
			// Return all objects hit by the ray
			RAY_WRAPPER std::vector<Object::feObject*> GetAllObjectHit();

			// Return the ray's direction
			RAY_WRAPPER Math::Vector3d GetDirection();
			// Return the ray's origin
			RAY_WRAPPER Math::Vector3d GetOrigin();

		private:
			//Functions
			void CreateRayFromMousePos(Math::Vector2d mousePos, Component::Video::feCamera* cam);

			int CheckCollisionNb(Math::Vector3d center, float radius); //may change to bounding boxes		
			float calcCollisionDistance(Math::Vector3d center, float radius);
			bool CheckIfNearest(float dist);

			//Variables
			std::vector<Object::feObject*> _objectHit;

			Math::Vector3d _dir;
			Math::Vector3d _origin;

			float _nearestHitDist = -1.f;
			float _delta;
		};
	
	} //namespace Physics
} //namespace FrogEngine