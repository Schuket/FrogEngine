#include "SDLEvent.h"

namespace FrogEngine
{
	namespace SDL
	{
		EventHandler::EventHandler()
		{
		}

		EventHandler::~EventHandler()
		{
		}

		int EventHandler::IsResized()
		{

				return 0;
		}

		int EventHandler::IsClosed()
		{

				return 0;
		}

		int EventHandler::IsKeyBeingPressed(Key key)
		{
			if (key <= Key::UNKNOWN && key >= Key::LAST)
				return 0;

			return 0;
		}

		int EventHandler::IsButtonBeingPressed(Button butt)
		{
			if (butt <= Button::UNKNOWN && butt >= Button::LAST)
				return 0;

			return 0;
		}

		Math::Vector2d EventHandler::GetResizedSize()
		{
			return Math::Vector2d(0.f, 0.f);
		}

	} //namespace SDL
} // namespace FrogEngine