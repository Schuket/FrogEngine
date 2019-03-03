#include "feInputManager.h"

#include "feSceneManager.h"

#include "../Component/Video/feEditorCamera.h"

#include "Logger\Logger.h"

namespace FrogEngine 
{
	namespace System 
	{
		feInputManager::feInputManager(Window* window, feSceneManager* scnMgr)
		{
			_window = window;
			_scnMgr = scnMgr;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feInputManager created !");
		}

		feInputManager::~feInputManager()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feInputManager is deleting. . .");
			_scnMgr = nullptr;
			_window = nullptr;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feInputManager deleted !");
		}

		feInputManager* feInputManager::Create(Window* window, feSceneManager* scnMgr)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feInputManager is creating. . .");
			return new feInputManager(window, scnMgr);
		}

		void feInputManager::SetWindow(sf::Window* newWindow)
		{
			_window->SetSFMLWindow(newWindow);
		}

		void feInputManager::Update(float deltaTime, Component::Video::feCamera* cam)
		{
			EventHandler eventHandler;

			if (!_window)
				return;

			while (_window->PollEvent(&eventHandler))
			{
				if (eventHandler.IsClosed())
				{
					_window->Close();
					return;
				}
				if (eventHandler.IsResized())
				{
					Math::Vector2d newSize = eventHandler.GetResizedSize();
					_window->Resize((unsigned int)newSize.X(), (unsigned int)newSize.Y());

					if (cam)
						cam->SetFrustum((unsigned int)newSize.X(), (unsigned int)newSize.Y());
				}

				if (eventHandler.IsButtonPressed(FrogEngine::Button::LEFT))
				{
					Math::Vector2d mousePos = _window->GetMousePos();
					_mousePressed_LeftClick.Invoke(mousePos.X(), mousePos.Y());
				}
				if (eventHandler.IsButtonPressed(FrogEngine::Button::RIGHT))
				{
					Math::Vector2d mousePos = _window->GetMousePos();
					_mousePressed_RightClick.Invoke(mousePos.X(), mousePos.Y());
				}
			}
			HandleContinousEvent(eventHandler, deltaTime); 

			if (cam)
				cam->UpdateCameraMovement(deltaTime);
		}

		void feInputManager::HandleContinousEvent(EventHandler eventHandler, float deltaTime)
		{
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::W))
				_keyIsPressed_W.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::A))
				_keyIsPressed_A.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::S))
				_keyIsPressed_S.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::D))
				_keyIsPressed_D.Invoke(deltaTime);

			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::U))
				_keyIsPressed_U.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::I))
				_keyIsPressed_I.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::O))
				_keyIsPressed_O.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::J))
				_keyIsPressed_J.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::K))
				_keyIsPressed_K.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::L))
				_keyIsPressed_L.Invoke(deltaTime);

			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::UP))
				_keyIsPressed_UpArrow.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::LEFT))
				_keyIsPressed_LeftArrow.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::DOWN))
				_keyIsPressed_DownArrow.Invoke(deltaTime);
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::RIGHT))
				_keyIsPressed_RightArrow.Invoke(deltaTime);

			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::ESCAPE))
				_keyPressed_Escape.Invoke();
			if (eventHandler.IsKeyBeingPressed(FrogEngine::Key::SPACE))
				_keyPressed_Space.Invoke();
		}
	} //namespace System
} //namespace FrogEngine