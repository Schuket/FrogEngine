#include "feScene.h"

#include "feResourceManager.h"

#include "../Object/feObject.h"
#include "../Component/Mesh/feModel.h"
#include "../Component/Video/feCamera.h"
#include "../Component/Physics/feCollider.h"
#include "../Physics/feBoundingSphere.h"
#include "../Physics/feRay.h"

#include "Mesh\Mesh.h"
#include "Material\feMaterial.h"

#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace System 
	{
		feScene::feScene(feResourceManager* resMgr)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feScene is creating. . .");

			_resMgr = resMgr;
			_cubeMap = nullptr;
			_root = new Object::feObject();
			_root->SetName("root");
			_selectedObject = nullptr;
			_mainCamera = nullptr;

			_idCount = 0;

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feScene created !");
		}

		feScene::feScene(feScene const& copy)
		{
			_resMgr = copy._resMgr;
			_cubeMap = copy._cubeMap->Clone();
			_root = copy._root->Clone();
			_selectedObject = nullptr;
			_mainCamera = nullptr;

			_idCount = copy._idCount;

			CheckComponents(_root);
		}

		feScene::~feScene()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feScene is deleting. . .");

			std::map<unsigned int, std::vector<Object::feObject*>>::iterator it = _drawableObjects.begin();
			for (; it != _drawableObjects.end(); it++)
			{
				for (int idx = 0; idx < it->second.size(); idx++)
				{
					it->second[idx] = nullptr;
				}
				it->second.clear();
			}
			_drawableObjects.erase(_drawableObjects.begin(), _drawableObjects.end());

			delete _cubeMap;
			delete _root;

			_resMgr = nullptr;
			_cubeMap = nullptr;
			_root = nullptr;
			_selectedObject = nullptr;
			_mainCamera = nullptr;

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feScene deleted !");
		}

		feScene* feScene::Clone()
		{
			return new feScene(*this);
		}

#pragma region Getter/Setter

		Object::feObject* feScene::GetMainCamera() const
		{
			return _mainCamera;
		}

		Object::feObject* feScene::GetRoot() const
		{
			return _root;
		}

		Object::feObject* feScene::GetSelectedObject() const
		{
			return _selectedObject;
		}

		std::map<unsigned int, std::vector<Object::feObject*>> feScene::GetDrawableObjects()
		{
			return _drawableObjects;
		}

		std::vector<Object::feObject*> feScene::GetPhysicsObjects()
		{
			return _physicsObjects;
		}

		void feScene::SetSkybox(Object::feObject* const& cubeMap)
		{
			_cubeMap = cubeMap;
		}

		void feScene::SetSelectedObject(Object::feObject* const& obj)
		{
			_selectedObject = obj;
		}

		void feScene::SetMainCamera(Object::feObject* const& obj)
		{
			_mainCamera = obj;
		}

#pragma endregion

		void feScene::Draw(Component::Video::feCamera* const& cam)
		{
			if (!cam)
				return;

			std::map<unsigned int, std::vector<Object::feObject*>> canDraw;

			std::map<unsigned int, std::vector<Object::feObject*>>::iterator itObject = _drawableObjects.begin();
			for (; itObject != _drawableObjects.end(); itObject++)
			{
				for (int idx = 0; idx < itObject->second.size(); ++idx)
				{
					FrogEngine::Physics::feBoundingSphere* collider = itObject->second[idx]->GetCollider();
					if (cam->GetFrustum()->CheckSphere(collider->GetTransform().GetTranslation(), collider->GetRadius() * collider->GetTransform().GetScale().X()))
						canDraw[itObject->first].push_back(itObject->second[idx]);
				}
			}

			std::map<unsigned int, std::vector<Object::feObject*>>::iterator itModel = canDraw.begin();
			for (; itModel != canDraw.end(); itModel++)
			{
				std::map<feShader* , std::vector<FrogEngine::Mesh::feMesh*>>::iterator itShader = _resMgr->GetModels()[itModel->first]->GetMeshes().begin();
				for (; itShader != _resMgr->GetModels()[itModel->first]->GetMeshes().end(); itShader++)
				{
					itShader->first->Bind();

					std::vector<FrogEngine::Mesh::feMesh*>::iterator itMesh = _resMgr->GetModels()[itModel->first]->GetMeshes()[itShader->first].begin();
					for (unsigned int i = 0; itMesh != _resMgr->GetModels()[itModel->first]->GetMeshes()[itShader->first].end(); itMesh++, i++)
					{
						(*itMesh)->GetBuffer().Bind();

						if ((*itMesh)->GetMtl())
							(*itMesh)->GetMtl()->BindTexture(itShader->first->GetProgram());

						std::vector<Object::feObject*>::iterator itObj = itModel->second.begin();
						for (; itObj != itModel->second.end(); itObj++)
						{
							itShader->first->BindTransform((*itObj)->GetTransform().GetWorldMatrix());
							(*itObj)->Draw(itShader->first, i);
						}

						if ((*itMesh)->GetMtl())
							(*itMesh)->GetMtl()->UnbindTexture();

						(*itMesh)->GetBuffer().Unbind();
					}

					itShader->first->Unbind();
				}
			}

			if (_cubeMap)
			{
				std::map<feShader*, std::vector<FrogEngine::Mesh::feMesh*>>::iterator itShader = _cubeMap->GetComponent<Component::Mesh::feModel>()->GetMeshes().begin();
				_cubeMap->Draw(itShader->first, 0);
			}

			_root->BindShaderCollider();
			_root->DrawCollider();
			_root->UnbindShaderCollider();

			std::map<unsigned int, std::vector<Object::feObject*>>::iterator it = canDraw.begin();
			for (; it != canDraw.end(); it++)
			{
				for (int idx = 0; idx < it->second.size(); idx++)
				{
					it->second[idx] = nullptr;
				}
				it->second.clear();
			}
			canDraw.erase(canDraw.begin(), canDraw.end());
		}

		void feScene::AddDrawableObject(Object::feObject* objToSet)
		{
			_drawableObjects[objToSet->GetComponent<Component::Mesh::feModel>()->GetIdx()].push_back(objToSet);
		}

		void feScene::RemoveObject(Object::feObject* objToDel)
		{
			SearchAndDeleteObject(_root, objToDel);

			_idCount = 0;

			UpdateIDCount(_root);
		}

		void feScene::SearchAndDeleteObject(Object::feObject* node, Object::feObject* objToDel)
		{
			if (!objToDel || !node)
				return;

			if (objToDel == node)
			{
				if (_selectedObject == node)
					_selectedObject = nullptr;

				if (_mainCamera == node)
					_mainCamera = nullptr;

				std::vector<Object::feObject*>::iterator it = _physicsObjects.begin();
				for (; it < _physicsObjects.end(); ++it)
				{
					if (*it == node)
						_physicsObjects.erase(it);
				}

				std::map<unsigned int, std::vector<Object::feObject*>>::iterator itDraw = _drawableObjects.begin();
				for (; itDraw != _drawableObjects.end(); itDraw++)
				{
					std::vector<Object::feObject*>::iterator itObj = itDraw->second.begin();
					for (; itObj != itDraw->second.end(); itObj++)
					{
						if (*itObj == node)
							itDraw->second.erase(itObj);
					}
				}

				delete node;
				node = nullptr;
				objToDel = nullptr;
				return;
			}

			size_t size = node->GetChildren().size();
			for (size_t idx = 0; idx < size; idx++)
				SearchAndDeleteObject(node->GetChildren()[idx], objToDel);
		}

		void feScene::AddPhysicObject(Object::feObject* objToSet)
		{
			_physicsObjects.push_back(objToSet);
		}

		unsigned int feScene::IncreaseIDCount()
		{
			return ++_idCount;
		}

		void feScene::UpdateIDCount(Object::feObject* node)
		{
			node->SetID(IncreaseIDCount());

			size_t size = node->GetChildren().size();
			for (size_t idx = 0; idx < size; idx++)
				UpdateIDCount(node->GetChildren()[idx]);
		}

		void feScene::CheckComponents(Object::feObject* node)
		{
			if (node->GetComponent<Component::Mesh::feModel>())
				AddDrawableObject(node);
			if (node->GetComponent<Component::Video::feCamera>())
				_mainCamera = node;
			if (node->GetComponent<Component::Physics::feCollider>())
				AddPhysicObject(node);

			size_t size = node->GetChildren().size();
			for (size_t idx = 0; idx < size; idx++)
				CheckComponents(node->GetChildren()[idx]);
		}
	} //namespace System
} //namespace FrogEngine