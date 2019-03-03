#ifdef RHI_EXPORTS
#define VERTICES_DATA_RHI __declspec(dllexport)
#else
#define VERTICES_DATA_RHI __declspec(dllimport)
#endif

#pragma once

#include <vector>

#include "Math/Vector2d.h"
#include "Math/Vector3d.h"

namespace FrogEngine
{
	struct feVertices
	{
		VERTICES_DATA_RHI feVertices();
		VERTICES_DATA_RHI ~feVertices();

		// Function
#pragma region Getter/Setter

		VERTICES_DATA_RHI int GetVertexSize();
		VERTICES_DATA_RHI size_t GetVerticesNb();
		VERTICES_DATA_RHI std::vector<float> GetFloatArray();

		VERTICES_DATA_RHI int SetPositions(const float* pos, int size);
		VERTICES_DATA_RHI int SetTexCoords(const float* tex, int size);
		VERTICES_DATA_RHI int SetNormals(const float* normal, int size);
		VERTICES_DATA_RHI int SetPositions(Math::Vector3d const& vec);
		VERTICES_DATA_RHI int SetTexCoords(Math::Vector2d const& vec);
		VERTICES_DATA_RHI int SetNormals(Math::Vector3d const& vec);
		VERTICES_DATA_RHI int SetTangent(Math::Vector3d const& vec);
		VERTICES_DATA_RHI int SetIndices(const uint16_t* indices, int size);

#pragma endregion

		VERTICES_DATA_RHI void PushVertex(Math::Vector3d pos, Math::Vector2d tex, Math::Vector3d norm);
		VERTICES_DATA_RHI void Clear();

		// Variables
		std::vector<Math::Vector3d> _positions;
		std::vector<Math::Vector2d> _texCoords;
		std::vector<Math::Vector3d> _normales;
		std::vector<Math::Vector3d> _tangent;

		std::vector<uint16_t> _indices;

	};
} // namespace FrogEngine