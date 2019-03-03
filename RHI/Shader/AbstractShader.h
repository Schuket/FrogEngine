#pragma once

#include "Math/Matrix4.h"

namespace FrogEngine
{
	class AbstractShader
	{
	public:
		// Functions
		virtual int Create(std::string name) = 0;

		virtual int Bind() = 0;
		virtual int Unbind() = 0;

		virtual int BindTransform(Math::Matrix4 worldPos) = 0;
		
		#pragma region Getter
			std::string GetName() { return _name; }
		#pragma endregion

	protected:
		// Variables
		std::string _name;
	};

} //namespace FrogEngine
