#ifdef WINDOWEVENT_EXPORTS
#define SFML_WINDOW_WRAPPER __declspec(dllexport) 
#else
#define SFML_WINDOW_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include <SFML/Window/Window.hpp>

#include "../AbstractWindow.h"

namespace FrogEngine
{
	namespace SFML
	{
		class EventHandler;

		class Window : public AbstractWindow
		{
		public:
			SFML_WINDOW_WRAPPER Window();
			SFML_WINDOW_WRAPPER ~Window();

			SFML_WINDOW_WRAPPER void Create(unsigned int width, unsigned int height, std::string title, HWND id = nullptr);
			SFML_WINDOW_WRAPPER void SetAttribute(Attributes attrib, unsigned int value);
			SFML_WINDOW_WRAPPER void Init(unsigned int width, unsigned int height, std::string title);
			SFML_WINDOW_WRAPPER void Resize(unsigned int width, unsigned int height);
			
			SFML_WINDOW_WRAPPER void SwapBuffers();
			SFML_WINDOW_WRAPPER bool PollEvent(EventHandler* _ev);

			SFML_WINDOW_WRAPPER Math::Vector2d GetSize();
			SFML_WINDOW_WRAPPER Math::Vector2d GetMousePos();
			SFML_WINDOW_WRAPPER int SetMousePos(Math::Vector2d);
			SFML_WINDOW_WRAPPER void SetHandle(HWND id);

			SFML_WINDOW_WRAPPER bool HasFocus();
			SFML_WINDOW_WRAPPER int IsOpen();
			SFML_WINDOW_WRAPPER void Close();
			SFML_WINDOW_WRAPPER void Shutdown();

			SFML_WINDOW_WRAPPER void SetSFMLWindow(sf::Window* newSFMLWindow);

		private:
			sf::Window* _window;
			sf::ContextSettings _settings;
			sf::WindowHandle _handle;
		};
	} //namespace SFML
} //namespace Wrapper