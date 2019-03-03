#pragma once

#include "../Math/Vector2d.h"

namespace FrogEngine
{
	class feImage;

	struct AbstractImage
	{
		virtual feImage LoadImg(std::string name) = 0;
		virtual void FreeCache() = 0;
	};
} // namespace FrogEngine