#include "feSceneManager.h"

#include "feScene.h"
#include "feInputManager.h"
#include "feLightManager.h"
#include "feResourceManager.h"
#include "feSerializeManager.h"
#include "Video/feDriver.h"
#include "Physics\fePhysicsManager.h"

#include "../Component/Video/feEditorCamera.h"
#include "../Component/Light/feAmbiantLight.h"

#include "../Object/feObject.h"
#include "../Physics/feRay.h"

#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace System 
	{
		feSceneManager::~feSceneManager()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSceneManager is deleting. . .");

			_scenes.clear();

			_idxActiveScene = 0;
			_idxEditorScene = 0;

			_lightMgr = nullptr;
			_drv = nullptr;
			_editorCam = nullptr;
			_resMgr = nullptr;
			_inputMgr = nullptr;

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSceneManager deleted !");
		}

		feSceneManager* feSceneManager::Create()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSceneManager is creating. . .");

			feSceneManager* feScnMgr = new feSceneManager();

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSceneManager created !");
			return feScnMgr;
		}

#pragma region Getter/Setter
		feLightManager* feSceneManager::GetLightManager() const
		{
			return _lightMgr;
		}

		Object::feObject* feSceneManager::GetEditorCamera() const
		{
			return _editorCam;
		}

		feResourceManager* feSceneManager::GetRessourceLoader() const
		{
			return _resMgr;
		}

		int feSceneManager::GetSceneIndex() const
		{
			return _idxActiveScene;
		}

		std::vector<feScene*>& feSceneManager::GetScenes() 
		{
			return _scenes;
		}

		feScene* feSceneManager::GetCurrentScene()
		{
			return _scenes[_idxActiveScene];
		}

		void feSceneManager::SetDefaultParameters(unsigned int const& width, unsigned int const& height, Video::feDriver* const& drv)
		{
			_lightMgr = new feLightManager();
			_drv = drv;
			_editorCam = new Object::feObject("Editor Camera");
			_editorCam->AddComponent(new Component::Video::feEditorCamera(width, height));
			_editorCam->GetComponent<Component::Video::feEditorCamera>()->Init();
			_resMgr = new System::feResourceManager(this, _drv);
		}

		void feSceneManager::SetObjectInScene(Object::feObject* objToSet, Object::feObject* const& parent)
		{
			feScene* curScn = _scenes[_idxActiveScene];

			if (curScn)
			{
				objToSet->SetID(curScn->IncreaseIDCount());

				if (parent == nullptr)
					curScn->GetRoot()->AddChild(objToSet);
				else
					objToSet->SetParent(parent);

				curScn = nullptr;
			}
		}

		void feSceneManager::SetInputManager(feInputManager* const& inputMgr)
		{ 
			_inputMgr = inputMgr; 
		}

#pragma endregion

		feScene* feSceneManager::AddScene()
		{
			_scenes.push_back(new feScene(_resMgr));

			return _scenes.back();
		}

		feScene* feSceneManager::AddSimulatorScene()
		{
			_scenes.push_back(_scenes[_idxActiveScene]->Clone());

			_idxEditorScene = _idxActiveScene;
			_idxActiveScene = (unsigned int)_scenes.size() - 1;

			_phyMgr->ManageScene(_scenes[_idxActiveScene]);

			return _scenes.back();
		}

		void feSceneManager::RemoveSimulatorScene()
		{
			_scenes.erase(_scenes.begin() + _idxActiveScene);

			_idxActiveScene = _idxEditorScene;

			_phyMgr->ManageScene(_scenes[_idxActiveScene]);
		}

		Object::feObject* feSceneManager::CreateObject(Object::feObject* parent)
		{
			Object::feObject* obj = new Object::feObject();

			SetObjectInScene(obj, parent);

			return obj;
		}

		void feSceneManager::AddComponent(Object::feObject* node, Component::feComponent* comp)
		{
			node->AddComponent(comp);

			if (comp->GetType() == Component::ComponentType::Mesh)
				_scenes[_idxActiveScene]->AddDrawableObject(node);
			else if (comp->GetType() == Component::ComponentType::Camera)
				_scenes[_idxActiveScene]->SetMainCamera(node);
			else if (comp->GetType() == Component::ComponentType::Collider)
				_scenes[_idxActiveScene]->AddPhysicObject(node);
			else if (comp->GetType() == Component::ComponentType::Light)
				_lightMgr->GetLights().push_back((Component::Light::feLight*)comp);

		}
		void feSceneManager::SaveCurrentScene()
		{
			feSerializeManager::SaveScene(_idxActiveScene, _scenes[_idxActiveScene]->GetRoot());
		}

		void feSceneManager::Draw(Component::Video::feCamera* cam)
		{
			cam->UpdateBufferObject();

			_lightMgr->UpdateBufferObject();

			_scenes[_idxActiveScene]->Draw(cam);
		}

		void feSceneManager::Shutdown()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSceneManager::Shutdown() is calling. . .");

			delete _lightMgr;
			delete _editorCam;
			delete _resMgr;

			for (int idx = 0; idx < _scenes.size(); ++idx)
				delete _scenes[idx];

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feSceneManager::Shutdown() called !");
		}

		void feSceneManager::HookMouseInputController(feInputManager* classPtr)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "###~~~###~~~### feSceneManager::HookMouseInputController ###~~~###~~~###");
			classPtr->_mousePressed_LeftClick.Bind<feSceneManager, &feSceneManager::LeftMouseClick>(this);
		}

		void feSceneManager::LeftMouseClick(float posX, float posY)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "~~~~~~~ feSceneManager::LeftMouseClick ~~~~~~~");
			feScene* currScene = GetScenes()[_idxActiveScene];

			Math::Vector2d mousePos(posX, posY);

			FrogEngine::Physics::feRay ray = FrogEngine::Physics::feRay(mousePos, _editorCam->GetComponent<Component::Video::feEditorCamera>());

			std::vector<Object::feObject*> rootChildren = currScene->GetRoot()->GetChildren();
			std::vector<Object::feObject*>::iterator first = rootChildren.begin();
			std::vector<Object::feObject*>::iterator last = rootChildren.end();

			for (; first != last; ++first)
				(*first)->CheckRayCollisionWithObjectAndChildren(&ray);

			Object::feObject* objectHit = ray.GetFirstObjectHit();
			Object::feObject* previousObject = currScene->GetSelectedObject();

			if (previousObject != objectHit)
			{
				if (previousObject != nullptr)
					previousObject->UnHookKeyboardInputController(_inputMgr);

				currScene->SetSelectedObject(objectHit);
				if (objectHit != nullptr)
					objectHit->HookKeyboardInputController(_inputMgr);
			}
		}

		feSceneManager::feSceneManager()
		{
			_idxActiveScene = 0;
			_idxEditorScene = 0;

			_lightMgr = nullptr;
			_drv = nullptr;
			_editorCam = nullptr;
			_resMgr = nullptr;
			_inputMgr = nullptr;
		}
	} //namespace System
} //namespace FrogEngine