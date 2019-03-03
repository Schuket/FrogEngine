#ifdef WINDOWEVENT_EXPORTS
#define SDL_EVENT_WRAPPER __declspec(dllexport) 
#else
#define SDL_EVENT_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "../AbstractEvent.h"

namespace FrogEngine
{
#pragma region Input Enum
	//Same order as SFML -> need Changes to be like SDL
	enum class Key : int
	{
		UNKNOWN = -1,
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		NUM0,
		NUM1,
		NUM2,
		NUM3,
		NUM4,
		NUM5,
		NUM6,
		NUM7,
		NUM8,
		NUM9,
		ESCAPE,
		LCONTROL,
		LSHIFT,
		LALT,
		LSYSTEM,
		RCONTROL,
		RSHIFT,
		RALT,
		RSYSTEM,
		MENU,
		LBRACKET,
		RBRACKET,
		SEMICOLON,
		COMMA,
		DOT,
		QUOTE,
		SLASH,
		BACKSLASH,
		TILDE,
		EQUAL,
		DASH,
		SPACE,
		RETURN,
		BACKSPACE,
		TAB,
		PAGEUP,
		PAGEDOWN,
		END,
		HOME,
		INSERT,
		DELETEKEY,
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		NUMPAD0,
		NUMPAD1,
		NUMPAD2,
		NUMPAD3,
		NUMPAD4,
		NUMPAD5,
		NUMPAD6,
		NUMPAD7,
		NUMPAD8,
		NUMPAD9,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		PAUSE,
		LAST
	};

	enum class Button : int
	{
		UNKNOWN = -1,
		LEFT = 0,
		RIGHT,
		MIDDLE,
		BUTTON4,
		BUTTON5,
		LAST
	};

#pragma endregion

	namespace SDL
	{
		class EventHandler : public AbstractEventHandler
		{
		public:
			friend class Window;

			SDL_EVENT_WRAPPER EventHandler();
			SDL_EVENT_WRAPPER ~EventHandler();

			SDL_EVENT_WRAPPER int IsResized();
			SDL_EVENT_WRAPPER int IsClosed();
			SDL_EVENT_WRAPPER int IsKeyBeingPressed(Key key);
			SDL_EVENT_WRAPPER int IsButtonBeingPressed(Button butt);

			SDL_EVENT_WRAPPER Math::Vector2d GetResizedSize();
		};

	} //namespace SDL
} //namespace FrogEngine