#pragma once

namespace FrogEngine
{
	class AbstractTime
	{
	protected:
		// Functions
		virtual float DeltaTime() = 0;
		virtual void RestartDeltaTime() = 0;
		virtual void RestartTime() = 0;
		virtual void Scale(float scale) = 0;
		virtual void ResetScale() = 0;

	protected:
		// Variables
		float _scale;
	};
} // namespace FrogEngine