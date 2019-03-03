#pragma once

#include "VerticesData.h"

namespace FrogEngine
{
	class AbstractBuffer
	{
	public:
		// Functions
		virtual int Create(feVertices data) = 0;
		virtual int Bind() = 0;
		virtual int Unbind() = 0;
	};
} // namespace FrogEngine