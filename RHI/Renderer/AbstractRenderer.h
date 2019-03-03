#pragma once

#include "Math\Vector4d.h"
#include "Math\Vector2d.h"

namespace FrogEngine
{
	enum class TypePolygon
	{
		TRIANGLES = 0,
		LINES,
		POINTS,
		PATCHES
	};

	enum class TypeDraw
	{
		DRAW = 0,
		DRAW_ELEMENT,
		DRAW_INDEXED
	};

	enum class PolygonMode
	{
		FILL = 0,
		LINE,
		POINTS
	};

	enum class DepthMode
	{
		LESS = 0,
		LEQUAL
	};

	class AbstractRenderer
	{
	protected:
		// Functions
		virtual int ClearBuffers(Math::Vector4d color) = 0;

		virtual int InitViewport(Math::Vector2d sizeWindow) = 0;
		virtual int InitDepthStencil() = 0;

		virtual int SetPolygonMode(PolygonMode mode) = 0;
		virtual int SetDepthMode(DepthMode mode) = 0;

		virtual int Draw(size_t count, TypeDraw typeDraw, TypePolygon typePoly) = 0;
	};
} // namespace FrogEngine