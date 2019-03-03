#include "VerticesData.h"
#include "../Error/RHIError.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	feVertices::feVertices()
	{
	}

	feVertices::~feVertices()
	{
	}

	int feVertices::GetVertexSize()
	{
		int vertexSize = 0;

		if (!_positions.empty())
			vertexSize += 3;

		if (!_texCoords.empty())
			vertexSize += 2;

		if (!_normales.empty())
			vertexSize += 3;

		if (!_tangent.empty())
			vertexSize += 3;

		return vertexSize;
	}

	size_t feVertices::GetVerticesNb()
	{
		return _positions.size(); 
	}

	std::vector<float> feVertices::GetFloatArray()
	{
		std::vector<float> vec;
		bool _tex = _texCoords.size() != _positions.size() ? false : true;
		bool _norm = _normales.size() != _positions.size() ? false : true;
		bool _tan = _tangent.size() != _positions.size() ? false : true;

		for (int i = 0; i < _positions.size(); i++)
		{
			vec.push_back(_positions[i].X());
			vec.push_back(_positions[i].Y());
			vec.push_back(_positions[i].Z());

			if (_tex)
			{
				vec.push_back(_texCoords[i].X());
				vec.push_back(_texCoords[i].Y());
			}

			if (_norm)
			{
				vec.push_back(_normales[i].X());
				vec.push_back(_normales[i].Y());
				vec.push_back(_normales[i].Z());
			}

			if (_tan)
			{
				vec.push_back(_tangent[i].X());
				vec.push_back(_tangent[i].Y());
				vec.push_back(_tangent[i].Z());
			}
		}

		return vec;
	}

	int feVertices::SetPositions(const float* pos, int size)
	{
		for (int i = 0; i < size; i += 3)
		{
			_positions.push_back(Math::Vector3d(pos[i], pos[i + 1], pos[i + 2]));
		}
		return RHI_SUCCESS;
	}

	int feVertices::SetTexCoords(const float* tex, int size)
	{
		for (int i = 0; i < size; i += 2)
		{
			_texCoords.push_back(Math::Vector2d(tex[i], tex[i + 1]));
		}
		return RHI_SUCCESS;
	}

	int feVertices::SetNormals(const float* normal, int size)
	{
		for (int i = 0; i < size; i += 3)
		{
			_normales.push_back(Math::Vector3d(normal[i], normal[i + 1], normal[i + 2]));
		}
		return RHI_SUCCESS;
	}

	int feVertices::SetPositions(Math::Vector3d const& vec)
	{
		_positions.push_back(vec);
		
		return RHI_SUCCESS;
	}

	int feVertices::SetTexCoords(Math::Vector2d const& vec)
	{
		_texCoords.push_back(vec);

		return RHI_SUCCESS;
	}

	int feVertices::SetNormals(Math::Vector3d const& vec)
	{
		_normales.push_back(vec);

		return RHI_SUCCESS;
	}

	int feVertices::SetTangent(Math::Vector3d const& vec)
	{
		_tangent.push_back(vec);

		return RHI_SUCCESS;
	}

	int feVertices::SetIndices(const uint16_t* indices, int size)
	{
		for (int i = 0; i < size; i++)
		{
			_indices.push_back(uint16_t(indices[i]));
		}
		return RHI_SUCCESS;
	}

	void feVertices::PushVertex(Math::Vector3d pos, Math::Vector2d tex, Math::Vector3d norm)
	{
		_positions.push_back(pos);
		_texCoords.push_back(tex);
		_normales.push_back(norm);
	}

	void feVertices::Clear()
	{
		_positions.clear();
		_texCoords.clear();
		_normales.clear();
	}

} // namespace FrogEngine