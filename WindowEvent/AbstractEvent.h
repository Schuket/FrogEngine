#pragma once

#include "Math/Vector2d.h"

namespace FrogEngine
{
	enum class Key;
	enum class Button;

	class AbstractEventHandler
	{
	public:

		virtual int IsResized() = 0;
		virtual int IsClosed() = 0;
		virtual int IsKeyBeingPressed(Key key) = 0;
		virtual int IsButtonBeingPressed(Button button) = 0;

		virtual Math::Vector2d GetResizedSize() = 0;
	};

}// namespace FrogEngine