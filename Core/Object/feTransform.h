#ifdef CORE_EXPORTS
#define TRANSFORM_WRAPPER __declspec(dllexport)
#else
#define TRANSFORM_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "Math\Matrix4.h"
#include "Math\Vector3d.h"
#include "Math\Quaternion.h"

namespace FrogEngine
{
	namespace Object
	{
		class feObject;

		class feTransform
		{
		public:
			// Ctor / Dtor
			feTransform();
			feTransform(feTransform const& copy);
			feTransform(Object::feObject* Owner);
			feTransform(Math::Vector3d Translation, Math::Quaternion Rotation, Math::Vector3d Scale, Object::feObject* Owner = nullptr);
			~feTransform();

			// Functions
			/* Translate the object
			* translation : the translation vector 
			*/
			TRANSFORM_WRAPPER void Translate(Math::Vector3d Translation);
			/* Rotate the object with an angle in degree
			* Deg : the angle in degree to rotate
			* Xaxis, Yaxis, Zaxis : Choose the axe of rotation
			*/
			TRANSFORM_WRAPPER void RotateDeg(float Deg, float Xaxis, float Yaxis, float Zaxis);
			/* Rotate the object with an angle in degree
			* Deg : the angle in degree to rotate
			* vec : Choose the axe of rotation with a Vector3d
			*/
			TRANSFORM_WRAPPER void RotateDeg(float Deg, Math::Vector3d vec);
			/* Rotate the object with an angle in radian
			* Rad : the angle in radian to rotate
			* Xaxis, Yaxis, Zaxis : Choose the axe of rotation
			*/
			TRANSFORM_WRAPPER void RotateRad(float Rad, float Xaxis, float Yaxis, float Zaxis);
			/* Scale the object
			* Scale : the new scale (replace the old scale)
			*/
			TRANSFORM_WRAPPER void Scale(Math::Vector3d Scale);

#pragma region Getter/Setter
			/* Set translation vector of this object
			* NewTranslation : the new translation (replace the old translation)
			*/
			TRANSFORM_WRAPPER void SetTranslation(Math::Vector3d NewTranslation);
			/* Set rotation quaternion of this object
			* NewQuaternion : the new quaternion (replace the old rotation)
			*/
			TRANSFORM_WRAPPER void SetRotation(Math::Quaternion NewQuaternion);
			/* Set Scale vector of this object
			* NewScale : the new scale (replace the old scale)
			*/
			TRANSFORM_WRAPPER void SetScale(Math::Vector3d NewScale);
			/* Set translation vector and the rotaion quaternion of this object
			* NewTranslation : the new translation (replace the old translation)
			* NewQuaternion : the new quaternion (replace the old rotation)
			*/
			TRANSFORM_WRAPPER void SetTranslationAndRotation(Math::Vector3d NewTranslation,
			
			Math::Quaternion NewQuaternion);
			// Get the global rotation
			TRANSFORM_WRAPPER Math::Quaternion& GetRotation();
			// Get the global translation
			TRANSFORM_WRAPPER Math::Vector3d& GetTranslation();
			// Get the global scale
			TRANSFORM_WRAPPER Math::Vector3d& GetScale();

			// Get the local rotation
			TRANSFORM_WRAPPER Math::Quaternion GetLocalRotation() const;
			// Get the local translation
			TRANSFORM_WRAPPER Math::Vector3d GetLocalTranslation() const;
			// Get the local scale
			TRANSFORM_WRAPPER Math::Vector3d GetLocalScale() const;

			// Get the world matrix
			TRANSFORM_WRAPPER Math::Matrix4 GetWorldMatrix() const;
			// Get the local matrix 
			TRANSFORM_WRAPPER Math::Matrix4 GetLocalMatrix() const;

			// Return the owner of this transform (feObject)
			TRANSFORM_WRAPPER Object::feObject* GetOwner() const;
			/* Set the owner of this transform
			* newOwner : the new owner
			*/
			TRANSFORM_WRAPPER void SetOwner(Object::feObject* newOwner);

			// Get the up vector
			TRANSFORM_WRAPPER Math::Vector3d GetUp();
			// Get the forward vector
			TRANSFORM_WRAPPER Math::Vector3d GetForward();
			// Get the right vector
			TRANSFORM_WRAPPER Math::Vector3d GetRight();

#pragma endregion

			void UpdateWorldMatrix(feTransform* const parent = nullptr);

			void UpdateLocalMatrix();

			//Variables
			const Math::Vector3d _up = Math::Vector3d(0.f, 1.f, 0.f);
			const Math::Vector3d _right = Math::Vector3d(1.f, 0.f, 0.f);
			const Math::Vector3d _forward = Math::Vector3d(0.f, 0.f, -1.f);

		private:
			// Functions
			void CheckToUpdate();

			// Variables
			Object::feObject* _owner;

			Math::Quaternion _rotation;
			Math::Quaternion _localRotation;

			Math::Vector3d _translation;
			Math::Vector3d _localTranslation;

			Math::Vector3d _scale;
			Math::Vector3d _localScale;

			Math::Matrix4 _local;
			Math::Matrix4 _world;

		};

	} //namespace Object
} //namespace FrogEngine