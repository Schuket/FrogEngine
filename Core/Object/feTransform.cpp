#include "feTransform.h"

#include "feObject.h"
#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace Object 
	{
		feTransform::feTransform()
			:feTransform(nullptr)
		{
		}
	
		feTransform::feTransform(feTransform const& copy)
		{
			_owner = copy._owner;

			_rotation = copy._rotation;
			_localRotation = copy._localRotation;

			_translation = copy._translation;
			_localTranslation = copy._localTranslation;

			_scale = copy._scale;
			_localScale = copy._localScale;

			_local = copy._local;
			_world = copy._world;
		}
		
		feTransform::feTransform(Object::feObject* Owner)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feTransform is creating. . .");
			_owner = Owner;
			_translation = Math::Vector3d(0.0f, 0.0f, 0.0f);
			_rotation = Math::Quaternion();
			_scale = Math::Vector3d(1.0f, 1.0f, 1.0f);
	
			_localTranslation = Math::Vector3d(0.0f, 0.0f, 0.0f);
			_localRotation = Math::Quaternion();
			_localScale = Math::Vector3d(1.0f, 1.0f, 1.0f);
	
			_world = Math::Matrix4();
			_local = Math::Matrix4();

			CheckToUpdate();
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feTransform created !");
		}

		feTransform::feTransform(Math::Vector3d Translation, Math::Quaternion Rotation, Math::Vector3d Scale, Object::feObject* Owner)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feTransform is creating. . .");
			_owner = Owner;
			_translation = Math::Vector3d(0.0f, 0.0f, 0.0f);
			_rotation = Math::Quaternion();
			_scale = Math::Vector3d(1.0f, 1.0f, 1.0f);
	
			_localTranslation = Translation;
			_localRotation = Rotation;
			_localScale = Scale;

			_world = Math::Matrix4();
			_local = Math::Matrix4();

			CheckToUpdate();
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feTransform created !");
		}
	
		feTransform::~feTransform()
		{
			_owner = nullptr;
		}
	
		void feTransform::Translate(Math::Vector3d Translation)
		{
			_localTranslation += Translation;
			CheckToUpdate();
		}
	
		void feTransform::RotateDeg(float Deg, float Xaxis, float Yaxis, float Zaxis)
		{
			Math::Quaternion quat = Math::Quaternion::QuatFromAxisDeg(Deg, Xaxis, Yaxis, Zaxis);
			_localRotation = _localRotation * quat;
			
			CheckToUpdate();
		}
	
		void feTransform::RotateDeg(float Deg, Math::Vector3d vec)
		{
			Math::Quaternion quat = Math::Quaternion::QuatFromAxisDeg(Deg, vec.X(), vec.Y(), vec.Z());
			_localRotation = _localRotation * quat;

			CheckToUpdate();
		}

		void feTransform::RotateRad(float Rad, float Xaxis, float Yaxis, float Zaxis)
		{
			Math::Quaternion quat = Math::Quaternion::QuatFromAxisRad(Rad, Xaxis, Yaxis, Zaxis);
			_localRotation = _localRotation * quat;
		
			CheckToUpdate();
		}
	
		void feTransform::Scale(Math::Vector3d Scale)
		{
			_localScale = Scale;
			CheckToUpdate();
		}
	
#pragma region Getter/Setter

		void feTransform::SetTranslation(Math::Vector3d NewTranslation) 
		{ 
			_localTranslation = NewTranslation; 
			CheckToUpdate(); 
		}

		void feTransform::SetRotation(Math::Quaternion NewQuaternion) 
		{ 
			_localRotation = NewQuaternion;  
			CheckToUpdate(); 
		}

		void feTransform::SetScale(Math::Vector3d NewScale) 
		{ 
			_localScale = NewScale; 
			CheckToUpdate(); 
		}

		void feTransform::SetTranslationAndRotation(Math::Vector3d NewTranslation,
													Math::Quaternion NewQuaternion)
		{
			_localTranslation = NewTranslation;
			_localRotation = NewQuaternion;
			CheckToUpdate();
		}

		Math::Quaternion& feTransform::GetRotation() 
		{ 
			return _rotation; 
		}

		Math::Vector3d& feTransform::GetTranslation() 
		{ 
			return _translation; 
		}

		Math::Vector3d& feTransform::GetScale() 
		{ 
			return _scale; 
		}

		Math::Quaternion feTransform::GetLocalRotation() const 
		{ 
			return _localRotation; 
		}

		Math::Vector3d feTransform::GetLocalTranslation() const 
		{ 
			return _localTranslation; 
		}

		Math::Vector3d feTransform::GetLocalScale() const 
		{ 
			return _localScale; 
		}

		Math::Matrix4 feTransform::GetWorldMatrix() const 
		{ 
			return _world; 
		}

		Math::Matrix4 feTransform::GetLocalMatrix() const
		{
			return _local;
		}

		Object::feObject* feTransform::GetOwner() const 
		{ 
			return _owner; 
		}

		void feTransform::SetOwner(Object::feObject* newOwner) 
		{ 
			if (!newOwner)
				Logging::Logger::Instance().Log(Logging::Priority::WARNING, "feTransform::SetOwner -> setting a nullptr owner");

			_owner = newOwner; 
		}

		Math::Vector3d feTransform::GetUp()
		{
			return Math::Quaternion::QuatToMat4(_rotation).GetUp();
		}

		Math::Vector3d feTransform::GetForward()
		{
			return Math::Quaternion::QuatToMat4(_rotation).GetForward();
		}

		Math::Vector3d feTransform::GetRight()
		{
			return Math::Quaternion::QuatToMat4(_rotation).GetRight();
		}

#pragma endregion

		void feTransform::UpdateLocalMatrix()
		{
			_local = Math::Matrix4::CreateMat4Translation(_localTranslation) * Math::Quaternion::QuatToMat4(_localRotation) * Math::Matrix4::CreateMat4Scale(_localScale);
		}
	
		void feTransform::UpdateWorldMatrix(feTransform* const parentTransform)
		{
			UpdateLocalMatrix();
	
			if (parentTransform)
			{
				_world = parentTransform->GetWorldMatrix() * _local;
				_translation = _world.RecoverTranslation();//parentTransform->GetTranslation().Cross(_localTranslation);
				_scale = _world.RecoverScale();// parentTransform->GetScale().Cross(_localScale);
				_rotation = _world.RecoverRotation();// parentTransform->GetRotation() * _localRotation;
			}
			else
			{
				_world = _local;
				_translation = _localTranslation;
				_rotation = _localRotation;
				_scale = _localScale;
			}
		}
		
		void feTransform::CheckToUpdate()
		{
			if (_owner != nullptr)
				_owner->UpdateWorldPos();
		}
	} //namespace Object
} //namespace FrogEngine