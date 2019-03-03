#ifdef RHI_EXPORTS
#define D3D_BUFFER_RHI __declspec(dllexport)
#else
#define D3D_BUFFER_RHI __declspec(dllimport)
#endif

#pragma once

#include "AbstractBuffer.h"

namespace FrogEngine
{
	namespace D3D
	{
		class feBuffer : public AbstractBuffer
		{
		public:
			// Ctor
			D3D_BUFFER_RHI feBuffer() { }

			// Functions
			D3D_BUFFER_RHI virtual int Create(feVertices data) { return 0; }
			D3D_BUFFER_RHI virtual int Bind() { return 0; }
			D3D_BUFFER_RHI virtual int Unbind() { return 0; }
		};
	} // namespace D3D
} //namespace FrogEngine