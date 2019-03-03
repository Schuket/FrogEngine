#ifdef RHI_EXPORTS
#define D3D_CORE_RHI __declspec(dllexport)
#else
#define D3D_CORE_RHI __declspec(dllimport)
#endif

#pragma once

#include "AbstractRenderer.h"
#include "RHI\Error\RHIError.h"


namespace FrogEngine
{
	namespace D3D
	{
		class feRenderer : public AbstractRenderer
		{
		public:
			// Functions
			D3D_CORE_RHI static int ClearBuffers(Math::Vector4d color) { return RHI_SUCCESS; }

			D3D_CORE_RHI static int InitViewport(Math::Vector2d sizeWindow) { return RHI_SUCCESS; }
			D3D_CORE_RHI static int InitDepthStencil() { return RHI_SUCCESS; }
			D3D_CORE_RHI static int SetPolygonMode(PolygonMode mode) { return RHI_SUCCESS; }
			D3D_CORE_RHI static int SetDepthMode(DepthMode mode) { return RHI_SUCCESS; }

			D3D_CORE_RHI static int Draw(size_t count, TypeDraw typeDraw, TypePolygon typePoly) { return RHI_SUCCESS; }
		};
	} // namespace OPENGL
} // namespace FrogEngine