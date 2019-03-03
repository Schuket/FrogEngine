#pragma once

namespace FrogEngine
{
	class AbstractBufferObject
	{
	public:

		// Functions
		virtual int Update(void* objectStruct, int size, int locationID = 0) = 0;

	};

} // namespace FrogEngine