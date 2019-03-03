#include "feObject.h"

#include "../System/feSceneManager.h"
#include "../System/feInputManager.h"

#include "../Physics/feRay.h"
#include "../Physics/feBoundingSphere.h"

#include "../Component/Physics/feCollider.h"
#include "../Component/Mesh/feModel.h"

#include "Mesh/Mesh.h"
#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace Object 
	{
		feObject::feObject()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feObject is creating. . .");
			_collider = new Physics::feBoundingSphere(1.f, Math::Vector3d(0.f, 0.f, 0.f));
			_parent = nullptr;
			_name = "Unamed Object";
			_transform.SetOwner(this);

			UpdateWorldPos();

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feObject created !");
		}

		feObject::feObject(feObject const& copy)
		{
			_name = copy._name;
			_transform.SetTranslation(copy._transform.GetLocalTranslation());
			_transform.SetScale(copy._transform.GetLocalScale());
			_transform.SetRotation(copy._transform.GetLocalRotation());
			_transform.SetOwner(this);
			_collider = copy._collider->Clone();
			_id = copy._id;

			size_t size = copy._children.size();
			for (size_t idx = 0; idx < size; ++idx)
				copy._children[idx]->Clone()->SetParent(this);

			std::map<std::size_t, Component::feComponent*> components = copy._components;
			std::map<std::size_t, Component::feComponent*>::iterator it = components.begin();
			std::map<std::size_t, Component::feComponent*>::iterator end = components.end();
			for (; it != end; it++)
			{
				AddComponent(it->second->Clone());
			}

			UpdateWorldPos();
		}

		feObject::feObject(std::string const& name, feObject* parent)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feObject is creating. . .");
			_collider = new Physics::feBoundingSphere(1.f, Math::Vector3d(0.f, 0.f, 0.f));
			_parent = parent;
			_name = name;
			_transform.SetOwner(this);

			UpdateWorldPos();

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feObject created !");
		}

		feObject::~feObject()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feObject is deleting. . .");
			size_t size = _children.size();
			for (unsigned int idx = 0; idx < size; ++idx)
				delete _children[idx];
			_children.clear();

			std::map<std::size_t, Component::feComponent*>::iterator it = _components.begin();
			for (; it != _components.end(); ++it)
			{
				delete it->second;
				it->second = nullptr;
			}
			_components.erase(_components.begin(), _components.end());

			delete _collider;

			_collider = nullptr;
			_parent = nullptr;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feObject deleted !");
		}

		void feObject::UpdateWorldPos()
		{
			if (_parent)
				_transform.UpdateWorldMatrix(&_parent->GetTransform());
			else
				_transform.UpdateWorldMatrix(nullptr);

			if (_collider && _name != "Editor Camera" && _name != "root")
				_collider->GetTransform().UpdateWorldMatrix(&_transform);

			Component::Physics::feCollider* collider = GetComponent<Component::Physics::feCollider>();
			if (collider)
			{
				if (!collider->IsUpdatingOwner())
				{
					_onTransformChange.Invoke(_transform);
				}
				collider->SetUpdateOwner(false);
			}

			std::vector<feObject*>::iterator first = _children.begin();
			std::vector<feObject*>::iterator last = _children.end();

			for (; first != last; ++first)
				(*first)->UpdateWorldPos();
		}

		void feObject::DrawCollider()
		{
			if (_collider && _name != "Editor Camera" && _name != "root")
				_collider->Draw();

			std::vector<feObject*>::iterator first = _children.begin();
			std::vector<feObject*>::iterator last = _children.end();

			for (; first != last; ++first)
				(*first)->DrawCollider();
		}

		void feObject::BindShaderCollider()
		{
			if (_collider)
			{
				_collider->BindShader();
				_collider->BindBuffer();
			}
		}

		void feObject::UnbindShaderCollider()
		{
			if (_collider)
			{
				_collider->UnbindShader();
				_collider->UnbindBuffer();
			}
		}

		feObject* feObject::Clone()
		{
			return new feObject(*this);
		}

#pragma region Getter/Setter

		std::string feObject::GetName() const 
		{ 
			return _name; 
		}

		feObject* feObject::GetParent() const 
		{ 
			return _parent; 
		}

		feTransform& feObject::GetTransform() 
		{ 
			return _transform; 
		}

		std::vector<feObject*> feObject::GetChildren() const 
		{ 
			return _children; 
		}
		
		Physics::feBoundingSphere* feObject::GetCollider() const
		{
			return _collider;
		}

		feEvent<void(feTransform)>& feObject::GetEventOnTransformChange()
		{
			return _onTransformChange; 
		}

		unsigned int feObject::GetID() const
		{
			return _id;
		}

		void feObject::SetID(unsigned int const& id)
		{
			_id = id;
		}

		void feObject::SetName(std::string value) 
		{ 
			_name = value; 
		}

		void feObject::SetParent(feObject* const parent)
		{
			if (parent == nullptr)
				Logging::Logger::Instance().Log(Logging::Priority::WARNING, "feObject::SetParent() -> Setting parent with NULLPTR value.");

			_parent = parent;
			_parent->AddChild(this);
		}

#pragma endregion

		void feObject::Draw(feShader* shader, unsigned int idxMesh)
		{
			GetComponent<Component::Mesh::feModel>()->GetMeshes()[shader][idxMesh]->Draw();
		}

		void feObject::AddChild(feObject* const& child) 
		{ 
			_children.push_back(child); 
		}

		void feObject::AddComponent(Component::feComponent* const& component)
		{
			_components.emplace(component->GetTypeID(), component);
			component->SetOwner(this);
			component->Init(this);
		}
		
		void feObject::RemoveComponent(Component::feComponent* const& component)
		{
			if (!component)
				return;

			std::map<std::size_t, Component::feComponent*>::iterator it = _components.begin();
			for (; it != _components.end(); ++it)
			{
				if (it->second == component)
					_components.erase(it);
			}
		}

		void feObject::RemoveChild(feObject* const& child)
		{
			if (!child)
				return;
			std::vector<feObject*>::iterator it = _children.begin();
			for (; it != _children.end(); ++it)
			{
				if (*it == child)
					_children.erase(it);
			}
		}

		std::map<std::size_t, Component::feComponent*> feObject::GetComponent() const
		{
			return _components;
		}

		bool feObject::CheckRayCollision(Physics::feRay* ray)
		{
			return ray->IsHiting(this);
		}

		bool feObject::CheckRayCollisionWithObjectAndChildren(Physics::feRay* ray)
		{
			bool result = false;
			result = CheckRayCollision(ray);

			std::vector<feObject*>::iterator first = _children.begin();
			std::vector<feObject*>::iterator last = _children.end();

			for (; first != last; ++first)
			{
				if ((*first)->CheckRayCollisionWithObjectAndChildren(ray))
					result = true;
			}
			return result;
		}

		void feObject::HookKeyboardInputController(System::feInputManager* inputMgr)
		{
			if (!inputMgr)
				return;

			inputMgr->_keyIsPressed_I.Bind<feObject, &feObject::MoveForward>(this);
			inputMgr->_keyIsPressed_K.Bind<feObject, &feObject::MoveBackward>(this);
			inputMgr->_keyIsPressed_L.Bind<feObject, &feObject::MoveRight>(this);
			inputMgr->_keyIsPressed_J.Bind<feObject, &feObject::MoveLeft>(this);
			inputMgr->_keyIsPressed_U.Bind<feObject, &feObject::MoveUp>(this);
			inputMgr->_keyIsPressed_O.Bind<feObject, &feObject::MoveDown>(this);
		}

		void feObject::UnHookKeyboardInputController(System::feInputManager* inputMgr)
		{
			if (!inputMgr)
				return;

			inputMgr->_keyIsPressed_I.Unbind<feObject, &feObject::MoveForward>();
			inputMgr->_keyIsPressed_K.Unbind<feObject, &feObject::MoveBackward>();
			inputMgr->_keyIsPressed_L.Unbind<feObject, &feObject::MoveRight>();
			inputMgr->_keyIsPressed_J.Unbind<feObject, &feObject::MoveLeft>();
			inputMgr->_keyIsPressed_U.Unbind<feObject, &feObject::MoveUp>();
			inputMgr->_keyIsPressed_O.Unbind<feObject, &feObject::MoveDown>();
		}

		//private

		void feObject::MoveRight(float deltaTime)
		{
			_transform.Translate(_transform.GetRight() * deltaTime * 10.f);
		}

		void feObject::MoveLeft(float deltaTime)
		{
			_transform.Translate(_transform.GetRight() * (-deltaTime * 10.f));
		}

		void feObject::MoveForward(float deltaTime)
		{
			_transform.Translate(_transform.GetForward() * (deltaTime * 10.f));
		}

		void feObject::MoveBackward(float deltaTime)
		{
			_transform.Translate(_transform.GetForward() * (-deltaTime * 10.f));
		}

		void feObject::MoveUp(float deltaTime)
		{
			_transform.Translate(_transform.GetUp() * (deltaTime * 10.f));
		}

		void feObject::MoveDown(float deltaTime)
		{
			_transform.Translate(_transform.GetUp() * (-deltaTime * 10.f));
		}
	} //namespace Object
} //namespace FrogEngine 