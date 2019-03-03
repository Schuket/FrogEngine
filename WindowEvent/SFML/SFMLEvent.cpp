
#include <SFML\Window\Mouse.hpp>

#include "SFMLEvent.h"

namespace FrogEngine
{
	namespace SFML
	{
		EventHandler::EventHandler()
		{
		}

		EventHandler::~EventHandler()
		{
		}

	#pragma region PollEvent Func

		int EventHandler::IsResized()
		{
			return (_ev.type == sf::Event::Resized);
		}

		int EventHandler::IsClosed()
		{
			return (_ev.type == sf::Event::Closed);
		}

		int EventHandler::DoMouseEnteredWindow()
		{
			return (_ev.type == sf::Event::MouseEntered);
		}

		int EventHandler::DoMouseLeftWindow()
		{
			return (_ev.type == sf::Event::MouseLeft);
		}

		int EventHandler::IsKeyPressed(Key key)
		{
			if (key <= Key::UNKNOWN && key >= Key::LAST)
				return 0;

			return (_ev.type == sf::Event::KeyPressed) && (_ev.key.code == sf::Keyboard::Key(key));
		}

		int EventHandler::IsKeyReleased(Key key)
		{
			if (key <= Key::UNKNOWN && key >= Key::LAST)
				return 0;

			return (_ev.type == sf::Event::KeyReleased) && (_ev.key.code == sf::Keyboard::Key(key));
		}

		int EventHandler::IsButtonPressed(Button butt)
		{
			if (butt <= Button::UNKNOWN && butt >= Button::LAST)
				return 0;
	
			return (_ev.type == sf::Event::MouseButtonPressed) && (_ev.key.code == (sf::Mouse::Button)butt);
		}

		int EventHandler::IsButtonReleased(Button butt)
		{
			if (butt <= Button::UNKNOWN && butt >= Button::LAST)
				return 0;

			return (_ev.type == sf::Event::MouseButtonReleased) && (_ev.key.code == (sf::Mouse::Button)butt);
		}

	#pragma endregion

		int EventHandler::IsKeyBeingPressed(Key key)
		{
			if (key <= Key::UNKNOWN && key >= Key::LAST)
				return 0;

			return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
		}

		int EventHandler::IsButtonBeingPressed(Button butt)
		{
			if (butt <= Button::UNKNOWN && butt >= Button::LAST)
				return 0;

			return sf::Mouse::isButtonPressed((sf::Mouse::Button)butt);
		}

		Math::Vector2d EventHandler::GetResizedSize()
		{
			return Math::Vector2d(float(_ev.size.width), float(_ev.size.height));
		}

	} //namespace SFML
} // namespace FrogEngine