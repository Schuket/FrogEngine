
#include "SFMLWindow.h"
#include "SFMLEvent.h"

#include <iostream>
#include "SFML\Graphics.hpp"
#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace SFML
	{
		Window::Window()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SFMLWindow is creating. . .");
			_handle = sf::WindowHandle();
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SFMLWindow created !");
		}

		Window::~Window()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SFMLWindow is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "SFMLWindow deleted !");
		}

		void Window::Create(unsigned int width, unsigned int height, std::string title, HWND id)
		{
			_settings.majorVersion = 4;
			_settings.minorVersion = 5;
			_settings.depthBits = 24;
			_settings.stencilBits = 8;
			_settings.antialiasingLevel = 2;
			_settings.attributeFlags = sf::ContextSettings::Core;
			
			if (id)
				_window  = new sf::Window(id, _settings);
			else
				_window = new sf::Window(sf::VideoMode(width, height), title, sf::Style::Default, _settings);


			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, " *** OpenGL Context Settings *** ");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, " -> Version : ", (int)_settings.majorVersion, ".", (int)_settings.minorVersion);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, " -> Depth Bits : ", (int)_settings.depthBits);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, " -> Stencil Bits : ", (int)_settings.stencilBits);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, " -> Antialising Level : ", (int)_settings.antialiasingLevel);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, " *** *********************** *** ");
		}

		void Window::SetAttribute(Attributes attrib, unsigned int value)
		{
			switch (attrib)
			{
			case DEPTH:
				_settings.depthBits = value;
				break;
			case STENCIL:
				_settings.stencilBits = value;
				break;
			case ANTIALIASING:
				_settings.antialiasingLevel = value;
				break;
			}
		}

		void Window::Resize(unsigned int width, unsigned int height)
		{
			if (_window)
				_window->setSize(sf::Vector2u(width, height));
		}

		void Window::SwapBuffers()
		{
			if (_window)
				_window->display();
		}

		bool Window::PollEvent(EventHandler* _ev)
		{
			if (_window == nullptr)
				return false;
			return _window->pollEvent(_ev->_ev);
		}

		Math::Vector2d Window::GetSize()
		{
			if (_window == nullptr)
				return Math::Vector2d(0.f, 0.f);

			sf::Vector2u size = _window->getSize();

			return Math::Vector2d(float(size.x), float(size.y));
		}

		Math::Vector2d Window::GetMousePos()
		{
			if (_window == nullptr)
				return Math::Vector2d(0.f, 0.f);

			sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);

			return Math::Vector2d(float(mousePos.x), float(mousePos.y));
		}

		int Window::SetMousePos(Math::Vector2d vec)
		{
			if (_window == nullptr)
				return 0;

			sf::Vector2i vec2(int(vec.X()), int(vec.Y()));
			sf::Mouse::setPosition(vec2, *_window);

			return 1;
		}

		void Window::SetHandle(HWND id)
		{
			_handle = id;
			_handle->unused = false;
		}

		bool Window::HasFocus()
		{
			if (_window == nullptr)
				return false;
			return _window->hasFocus();
		}

		int Window::IsOpen()
		{
			if (!_window)
				return 0;
			return _window->isOpen();
		}

		void Window::Close()
		{
			if (_window)
				_window->close();
		}

		void Window::Shutdown()
		{
			if (_window)
			delete _window;
		}

		void Window::SetSFMLWindow(sf::Window* newSFMLWindow)
		{
			_window = newSFMLWindow;
		}
	} // namespace SFML
} // namespace FrogEngine