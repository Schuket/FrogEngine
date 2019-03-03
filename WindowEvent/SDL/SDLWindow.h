#ifdef WINDOWEVENT_EXPORTS
#define SDL_WINDOW_WRAPPER __declspec(dllexport) 
#else
#define SDL_WINDOW_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "../AbstractWindow.h"

namespace FrogEngine
{
	namespace SDL
	{
		class EventHandler;

		class Window : public AbstractWindow
		{
		public:
			SDL_WINDOW_WRAPPER Window();
			SDL_WINDOW_WRAPPER ~Window();

			SDL_WINDOW_WRAPPER void Create(unsigned int width, unsigned int height, std::string title, HWND id = nullptr);
			SDL_WINDOW_WRAPPER void SetAttribute(Attributes attrib, unsigned int value);
			SDL_WINDOW_WRAPPER void Resize(unsigned int width, unsigned int height);

			SDL_WINDOW_WRAPPER void SwapBuffers();
			SDL_WINDOW_WRAPPER bool PollEvent(EventHandler* _ev);

			SDL_WINDOW_WRAPPER Math::Vector2d GetSize();
			SDL_WINDOW_WRAPPER Math::Vector2d GetMousePos();
			SDL_WINDOW_WRAPPER int SetMousePos(Math::Vector2d);
			SDL_WINDOW_WRAPPER void SetHandle(HWND id) {}

			SDL_WINDOW_WRAPPER bool HasFocus();
			SDL_WINDOW_WRAPPER int IsOpen();
			SDL_WINDOW_WRAPPER void Close();
			SDL_WINDOW_WRAPPER void Shutdown();

		private:
			/*sdl::window _window;
			sdl::Context _contxt;*/
		};
	} //namespace SFML
} //namespace FrogEngine
