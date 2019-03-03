#include "feRay.h"

#include "feBoundingSphere.h"
#include "Core/Object/feObject.h"
#include "Core/Component/Video/feCamera.h"

#include "Math\Vector2d.h"
#include "Math\Matrix4.h"

#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace Physics
	{
		feRay::feRay(Math::Vector2d mousePos, Component::Video::feCamera* cam)
		{
			CreateRayFromMousePos(mousePos, cam);
		}

		bool feRay::IsHiting(Object::feObject* obj)
		{
			Math::Vector3d objPos = obj->GetCollider()->GetTransform().GetTranslation();
			float sphereRadius = obj->GetCollider()->GetRadius();

			int collisionNb = CheckCollisionNb(objPos, sphereRadius);
			if (collisionNb == 0)
				return false;

			float dist = calcCollisionDistance(objPos, sphereRadius);
			if (dist < 0.f)
				return false;

			if (CheckIfNearest(dist))
			{
				_nearestHitDist = dist;
				_objectHit.insert(_objectHit.begin(), obj);
			}
			else
				_objectHit.push_back(obj);

			return true;
		}

		void feRay::Reset()
		{
			_nearestHitDist = -1.f;
			_objectHit.clear();
		}

		Object::feObject* feRay::GetFirstObjectHit()
		{
			if (_objectHit.empty())
				return nullptr;

			return _objectHit[0];
		}

		std::vector<Object::feObject*> feRay::GetAllObjectHit()
		{
			return _objectHit;
		}

		Math::Vector3d feRay::GetDirection()
		{
			return _dir;
		}

		Math::Vector3d feRay::GetOrigin()
		{
			return _origin;
		}

		//private

		void feRay::CreateRayFromMousePos(Math::Vector2d mousePos, Component::Video::feCamera* cam)
		{
			if (cam == nullptr)
			{
				Logging::Logger::Instance().Log(Logging::CRITICAL, "feRay::CreateRayFromMousePos -> no camera to do RayPicking, aborting ...");
				return;
			}

			//Normalizing Positions -> going into ratios
			float x = (2.0f * mousePos.X()) / (float)cam->GetWidth() - 1.0f;
			float y = 1.0f - (2.0f * mousePos.Y()) / (float)cam->GetHeight();
			Math::Vector2d normalizedRay = Math::Vector2d(x, y);

			//casting ray forward -> z = -1
			Math::Vector4d forwardRay = Math::Vector4d(normalizedRay, -1.f, 0.f);

			//Going into EyeSpace, Where cam is the origin 
			Math::Vector4d camRay = cam->GetProjectionMatrix().Inverse() * forwardRay;
			Math::Vector4d fwdCamRay = Math::Vector4d(camRay.X(), camRay.Y(), -1.f, 0.f);

			//Goind into WorldSpace
			Math::Vector4d worldRay = cam->GetViewMatrix()/*.Inverse()*/ * fwdCamRay;

			_dir = Math::Vector3d(worldRay.X(), worldRay.Y(), worldRay.Z()).GetNormalize();
			_origin = cam->GetOwner()->GetTransform().GetTranslation();
		}


		int feRay::CheckCollisionNb(Math::Vector3d center, float radius)
		{
			Math::Vector3d centerToOrigin(_origin - center);		
			_delta = powf(_dir.Dot(centerToOrigin), 2.f) - centerToOrigin.Dot(centerToOrigin) + powf(radius, 2.f);

			if (_delta < 0.f)
				return 0;

			else if (_delta == 0.f)
				return 1;
			
			else
				return 2;	
		}

		float feRay::calcCollisionDistance(Math::Vector3d center, float radius)
		{

			if (_delta == 0.f)
			{
				float dist = -(_dir.Dot(_origin - center));

				//if negative, ray hit with element behind -> no hit
				if (dist < 0.f)
					return -1.f;

				else
					return dist;
			}
			else if (_delta > 0.f)
			{
				float dist = -(_dir.Dot(_origin - center));
				float dist1 = dist + sqrt(_delta);
				float dist2 = dist - sqrt(_delta);

				//if negative, ray hit with element behind -> no hit
				if (dist1 < 0.f && dist2 < 0.f)
					return -1.f;

				//return the shortest positive distance
				else if (dist1 < 0.f)
					return dist2;
				else if (dist2 < 0.f)
					return dist1;
				else
					return dist1 < dist2 ? dist1 : dist2;
			}
			else
				return -1.f;
		}

		bool feRay::CheckIfNearest(float dist)
		{
			if (_nearestHitDist < 0.f || dist < _nearestHitDist)
				return true;
			else
				return false;
		}

	} //namespace Physics
} //namespace FrogEngine