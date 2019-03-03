#ifdef RHI_EXPORTS
#define D3D_BUFFER_OBJECT_RHI __declspec(dllexport)
#else
#define D3D_BUFFER_OBJECT_RHI __declspec(dllimport)
#endif

#pragma once

#include "AbstractBufferObject.h"

namespace FrogEngine
{
	namespace D3D
	{
		class feBufferObject : public AbstractBufferObject
		{
		public:
			// Ctor / Dtor
			D3D_BUFFER_OBJECT_RHI feBufferObject() {}
			D3D_BUFFER_OBJECT_RHI ~feBufferObject() {}

			// Functions
			D3D_BUFFER_OBJECT_RHI virtual int Update(void* objectStruct, int size, int locationID = 0) { return 0; };
		};
	} // namesapce D3D
} // namespace FrogEngine