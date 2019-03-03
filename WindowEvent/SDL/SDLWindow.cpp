#include "SDLWindow.h"
#include "SDLEvent.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace SDL
	{
		Window::Window()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SDLWindow is creating. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SDLWindow created !");
		}

		Window::~Window()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SDLWindow is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SDLWindow deleted !");
		}

		void Window::Create(unsigned int width, unsigned int height, std::string title, HWND id)
		{
			
		}

		void Window::SetAttribute(Attributes attrib, unsigned int value)
		{
			switch (attrib)
			{
			case DEPTH:
				
				break;
			case STENCIL:
				
				break;
			case ANTIALIASING:
				
				break;
			}
		}

		void Window::Resize(unsigned int width, unsigned int height)
		{
			
		}

		void Window::SwapBuffers()
		{
			
		}

		bool Window::PollEvent(EventHandler* _ev)
		{
			return 0;
		}

		Math::Vector2d Window::GetSize()
		{
			/*if (_window == nullptr)
				return Math::Vector2d(0.f, 0.f);*/


			return Math::Vector2d(0.f, 0.f);
		}

		Math::Vector2d Window::GetMousePos()
		{
			/*if (_window == nullptr)
				return Math::Vector2d(0.f, 0.f);*/


			return Math::Vector2d(0.f, 0.f);
		}

		int Window::SetMousePos(Math::Vector2d vec)
		{
			/*if (_window == nullptr)
				return 0;*/

			return 1;
		}

		bool Window::HasFocus()
		{
			return 0;// _window->hasFocus();
		}

		int Window::IsOpen()
		{
			return 0;// _window->isOpen();
		}

		void Window::Close()
		{
			//_window->close();
		}

		void Window::Shutdown()
		{
			//delete _window;
		}

	} // namespace SDL
} // namespace FrogEngine