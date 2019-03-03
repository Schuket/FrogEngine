#pragma once

#include <string>
#include "Math/Vector2d.h"
#include <windows.h>

namespace FrogEngine
{
	enum Attributes
	{
		DEPTH = 0,
		STENCIL,
		ANTIALIASING
	};

	class AbstractWindow
	{
	public:

		virtual void Create(unsigned int width, unsigned int height, std::string title, HWND id) = 0;
		virtual void SetAttribute(Attributes attrib, unsigned int value) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		
		virtual void SwapBuffers() = 0;
		
		// Don't Forget to Implement this in every child
		//bool PollEvent(EventHandler* _ev)
		
		virtual Math::Vector2d GetSize() = 0;
		virtual Math::Vector2d GetMousePos() = 0;
		virtual int SetMousePos(Math::Vector2d) = 0;
		virtual void SetHandle(HWND id) = 0;

		virtual bool HasFocus() = 0;
		virtual int IsOpen() = 0;
		virtual void Close() = 0;
		virtual void Shutdown() = 0;
	};

} // namespace FrogEngine