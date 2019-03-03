#pragma once

#include <vector>

#include "Math\Vector4d.h"
#include "Math\Vector3d.h"
#include "Math\Matrix4.h"

namespace FrogEngine
{
	namespace System
	{
		namespace Video
		{
			class feFrustum
			{
			public:
				feFrustum();
				feFrustum(feFrustum const& copy);
				~feFrustum();

				feFrustum* Clone();

#pragma region Getter / Setter
				void SetDepth(float const& depth);

				float GetDepth() const;
#pragma endregion

				void ConstructPlanes(Math::Matrix4 proj, Math::Matrix4 view);
				
				bool CheckSphere(Math::Vector3d center, float radius);
			private:
				std::vector<Math::Vector4d> _planes;

				float _depth;
			};
		} // namespace Video
	} // namespace System
} // namespace FrogEngine