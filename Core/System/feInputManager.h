#pragma once

#include "WindowEvent\WindowEvent.h"

#include "Tools\feEvent.h"

namespace Math
{
	struct Vector2d;
}

namespace FrogEngine 
{
	namespace Component
	{
		namespace Video
		{
			class feCamera;
		} // namespace video
	} // namespace Component

	namespace System 
	{
		class feSceneManager;

		class feInputManager 
		{
		public:
			// Ctor / Dtor
			feInputManager() = delete;
			feInputManager(feInputManager const&) = delete;
			feInputManager(feInputManager&&) = delete;
			feInputManager operator=(feInputManager const&) = delete;
			feInputManager operator=(feInputManager &&) = delete;
			~feInputManager();

			static feInputManager* Create(Window*, feSceneManager*);

			// Functions
			void Update(float DeltaTime, Component::Video::feCamera*);

			void SetWindow(sf::Window* newWindow);

			void HandleContinousEvent(EventHandler eventhdl, float deltaTime);


		#pragma region Event
			feEvent<void()> _keyPressed_Escape;
			feEvent<void()> _keyPressed_Space;
			
			feEvent<void(float, float)> _mousePressed_LeftClick;
			feEvent<void(float, float)> _mousePressed_RightClick;

			//feEvent<void(float, float)> _mouseIsPressed_LeftClick;
			//feEvent<void(float, float)> _mouseIsPressed_RightClick;

			feEvent<void(float)> _keyIsPressed_U;
			feEvent<void(float)> _keyIsPressed_I;
			feEvent<void(float)> _keyIsPressed_O;
			feEvent<void(float)> _keyIsPressed_J;
			feEvent<void(float)> _keyIsPressed_K;
			feEvent<void(float)> _keyIsPressed_L;

			feEvent<void(float)> _keyIsPressed_W;
			feEvent<void(float)> _keyIsPressed_A;
			feEvent<void(float)> _keyIsPressed_S;
			feEvent<void(float)> _keyIsPressed_D;

			feEvent<void(float)> _keyIsPressed_UpArrow;
			feEvent<void(float)> _keyIsPressed_LeftArrow;
			feEvent<void(float)> _keyIsPressed_DownArrow;
			feEvent<void(float)> _keyIsPressed_RightArrow;
			
		#pragma endregion

		private:
			// Ctor
			feInputManager(Window*, feSceneManager*);
			
			// Variables
			feSceneManager* _scnMgr;
			Window* _window;
		};
	} //namespace System
} //namespace FrogEngine