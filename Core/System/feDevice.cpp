#include "feDevice.h"

#include "feScene.h"
#include "feSceneManager.h"
#include "feLightManager.h"
#include "feInputManager.h"
#include "Video/feDriver.h"
#include "feResourceManager.h"
#include "feSerializeManager.h"

#include "Physics\fePhysicsManager.h"

#include "../Component/Video/feEditorCamera.h"
#include "../Component/Light/feDirectionalLight.h"
#include "../Component/Physics/feBoxCollider.h" 
#include "../Component/Physics/feSphereCollider.h"
#include "../Component/Physics/feCapsuleCollider.h" 
#include "../Object/feObject.h"

#include "Math\Vector3d.h"

#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace System 
	{

		feDevice::~feDevice()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDevice is deleting. . .");
			_driver = nullptr;
			_scnMgr = nullptr;
			_inputMgr = nullptr;
			_physicsMgr = nullptr;
			_window = nullptr;
			_time = nullptr;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDevice deleted !");
		}

		feDevice* feDevice::Create()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDevice is creating. . .");
			feDevice* feDev = new feDevice();

			feDev->_driver = Video::feDriver::Create();
			feDev->_scnMgr = feSceneManager::Create();
			feDev->_inputMgr = feInputManager::Create(feDev->_window, feDev->_scnMgr);
			feDev->_physicsMgr = Physics::fePhysicsManager::Create();
			feDev->_driver->SetSceneManager(feDev->_scnMgr);
			feDev->_scnMgr->SetInputManager(feDev->_inputMgr);

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDevice created !");
			return feDev;
		}

		void feDevice::SetDefaultParameters(HWND id)
		{
			_window->SetAttribute(FrogEngine::Attributes::DEPTH, 24);
			_window->SetAttribute(FrogEngine::Attributes::STENCIL, 8);
			_window->SetAttribute(FrogEngine::Attributes::ANTIALIASING, 2);
			_window->Create(800, 800, "Frog Engine", id);

			_driver->SetDefaultParameters();
			_scnMgr->SetDefaultParameters(800, 800, _driver);
			_physicsMgr->Init();
			_driver->SetSceneManager(_scnMgr);
			_scnMgr->SetInputManager(_inputMgr);
			_scnMgr->SetPhysicsManager(_physicsMgr);
		}

		void feDevice::SetHasOnSimulation(bool const& b)
		{
			_hasOnSimulation = b;
		}

		feSceneManager* feDevice::GetScnMgr() const
		{
			return _scnMgr;
		}

		feInputManager* feDevice::GetInputMgr() const 
		{
			return _inputMgr;
		}

		Time* feDevice::GetTime() const
		{
			return _time;
		}

		Window* feDevice::GetWindow() const
		{
			return _window;
		}

		void feDevice::RunInit()
		{
			feRenderer::SetPolygonMode(PolygonMode::FILL);
			_scnMgr->AddScene();
			_scnMgr->GetRessourceLoader()->LoadSkybox("../Textures/Skybox/");

			Object::feObject* obj = _scnMgr->CreateObject(nullptr);
			obj->SetName("Iron Man");
			_scnMgr->AddComponent(obj, _scnMgr->GetRessourceLoader()->LoadModel("../Textures/ironman/ironman.fbx"));

			Object::feObject* objC = _scnMgr->CreateObject(nullptr);
			objC->SetName("Camera");
			objC->GetTransform().Translate(Math::Vector3d(0.f, 0.f, 60.f));

			unsigned int x = _scnMgr->GetEditorCamera()->GetComponent<Component::Video::feEditorCamera>()->GetWidth();
			unsigned int y = _scnMgr->GetEditorCamera()->GetComponent<Component::Video::feEditorCamera>()->GetHeight();

			_scnMgr->AddComponent(objC, new Component::Video::feCamera(x,y));

			Object::feObject* dirLight = _scnMgr->CreateObject(nullptr);
			dirLight->SetName("DirLight");
			_scnMgr->AddComponent(dirLight, new Component::Light::feDirectionalLight());


			_scnMgr->HookMouseInputController(_inputMgr);
			_scnMgr->GetEditorCamera()->GetComponent<Component::Video::feEditorCamera>()->HookArrowInputController(_inputMgr);
			_scnMgr->GetEditorCamera()->GetComponent<Component::Video::feEditorCamera>()->HookBasicKeyInputController(_inputMgr);
			
			//Physics
			obj->GetTransform().SetTranslation(Math::Vector3d(0.f, 10.f, 0.f));

			Component::Physics::feCapsuleCollider* caps = new Component::Physics::feCapsuleCollider(1.f, 2.f, 1.f);
			_scnMgr->AddComponent(obj, caps);

			caps->SetRotationFreezeRatio(1.f, 1.f, 1.f);

			Object::feObject* ground = _scnMgr->CreateObject();
			ground->SetName("Ground");
			ground->GetTransform().SetTranslation(Math::Vector3d(0.f, -10.f, 0.f));
			_scnMgr->AddComponent(ground, new Component::Physics::feBoxCollider(Math::Vector3d(20.f, 2.f, 20.f), 0.f));

			Object::feObject* obstacle = _scnMgr->CreateObject();
			obstacle->SetName("Cube Obstacle");
			obstacle->GetTransform().SetTranslation(Math::Vector3d(5.f, 0.f, 0.f));
			Component::Physics::feBoxCollider* obs = new Component::Physics::feBoxCollider(Math::Vector3d(2.f, 2.f, 2.f), 1.f);
			_scnMgr->AddComponent(obstacle, obs);

			Object::feObject* sphere1 = _scnMgr->CreateObject(nullptr);
			sphere1->SetName("Cube1");
			_scnMgr->AddComponent(sphere1, _scnMgr->GetRessourceLoader()->LoadModel("../Textures/sphere.obj"));
			sphere1->GetTransform().SetTranslation(Math::Vector3d(7.2f, 5.f, 0.f));
			Component::Physics::feSphereCollider* col = new Component::Physics::feSphereCollider(1.f, 1.f);
			_scnMgr->AddComponent(sphere1, col);

			
			Object::feObject* cube2 = _scnMgr->CreateObject(sphere1);
			cube2->SetName("Cube1");
			_scnMgr->AddComponent(cube2, _scnMgr->GetRessourceLoader()->LoadModel("../Textures/Cube/Cube.obj"));
			cube2->GetTransform().SetTranslation(Math::Vector3d(0.f, 3.f, 0.f));

			//End of INIT
			_physicsMgr->ManageScene(_scnMgr->GetCurrentScene());
		}

		void feDevice::StartSimulation()
		{
			if (_hasOnSimulation)
				return;
			_scnMgr->AddSimulatorScene();
			_hasOnSimulation = true;
		}
		
		void feDevice::StopSimulation()
		{
			if (!_hasOnSimulation)
				return;
			_scnMgr->RemoveSimulatorScene();
			_hasOnSimulation = false;
		}

		void feDevice::Run()
		{
			Component::Video::feCamera* cam = nullptr;

			if (_hasOnSimulation)
			{
				if (_scnMgr->GetCurrentScene()->GetMainCamera())
					cam = _scnMgr->GetCurrentScene()->GetMainCamera()->GetComponent<Component::Video::feCamera>();

				float deltaTime = _time->DeltaTime();
				_inputMgr->Update(deltaTime, cam);
				_physicsMgr->Simulate(deltaTime);

				_driver->Draw(_scnMgr, cam);

				//Debug
				_physicsMgr->DrawPhysicsGizmo();

				_window->SwapBuffers();
			}
			else
			{
				cam = _scnMgr->GetEditorCamera()->GetComponent<Component::Video::feEditorCamera>();

				float deltaTime = _time->DeltaTime();
				_inputMgr->Update(deltaTime, cam);
				
				_driver->Draw(_scnMgr, cam);

				//Debug
				_physicsMgr->DrawPhysicsGizmo();
				_window->SwapBuffers();
			}
		}

		void feDevice::Shutdown()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDevice::Shutdown() is calling. . .");
			_physicsMgr->ClearAllManagedCollider();
			_window->Shutdown();
			_driver->Shutdown();
			_scnMgr->Shutdown();

			delete _physicsMgr;
			delete _driver;
			delete _scnMgr;
			delete _inputMgr;
			delete _window;
			delete _time;

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDevice::Shutdown() called !");
		}

		feDevice::feDevice()
		{
			_driver = nullptr;
			_scnMgr = nullptr;
			_inputMgr = nullptr;
			_physicsMgr = nullptr;
			_window = new Window();
			_time = new Time();
		}

	} //namesapce System
} //namespace FrogEngine