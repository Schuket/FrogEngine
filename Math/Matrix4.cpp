#include "Matrix4.h"

#include <string>

#include "Tools.h"

#include "Vector3d.h"
#include "Vector4d.h"
#include "Quaternion.h"

namespace Math
{
	Matrix4::Matrix4()
	{
		Identity();
	}

	Matrix4::Matrix4(float data[16])
	{
		for (int idx = 0; idx < 16; ++idx)
			_data[idx] = data[idx];
	}

	Matrix4::Matrix4(Vector4d X, Vector4d Y, Vector4d Z, Vector4d W)
	{
		float array[16] = { X.X(), Y.X(), Z.X(), W.X(),
							X.Y(), Y.Y(), Z.Y(), W.Y(),
							X.Z(), Y.Z(), Z.Z(), W.Z(),
							X.W(), Y.W(), Z.W(), W.W() };

		for (int idx = 0; idx < 16; ++idx)
			_data[idx] = array[idx];
	}

	void Matrix4::Identity()
	{
		for (int idx = 0; idx < 16; ++idx)
			_data[idx] = 0.f;

		_data[0] = 1.f;
		_data[5] = 1.f;
		_data[10] = 1.f;
		_data[15] = 1.f;
	}

	Matrix4 Matrix4::operator*(Matrix4 const& mat) const
	{
		float res[16] = { 0 };

		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
				{
					res[(4 * j) + i] += _data[(4 * k) + i] * mat._data[(4 * j) + k];
				}

		return Matrix4(res);
	}

	Matrix4 Matrix4::Transpose() const
	{
		float res[16] = { 0 };

		for (int idx = 0; idx < 16; ++idx)
			res[idx] = _data[idx];

		Tools::Swap(res[1], res[4]);
		Tools::Swap(res[2], res[8]);
		Tools::Swap(res[6], res[9]);
		Tools::Swap(res[3], res[12]);
		Tools::Swap(res[7], res[13]);
		Tools::Swap(res[11], res[14]);

		return Matrix4(res);
	}

	Matrix4 Matrix4::Inverse() const
	{
		float res[16], inv[16], det;

		int i;

		inv[0] = _data[5] * _data[10] * _data[15] -
			_data[5] * _data[11] * _data[14] -
			_data[9] * _data[6] * _data[15] +
			_data[9] * _data[7] * _data[14] +
			_data[13] * _data[6] * _data[11] -
			_data[13] * _data[7] * _data[10];

		inv[4] = -_data[4] * _data[10] * _data[15] +
			_data[4] * _data[11] * _data[14] +
			_data[8] * _data[6] * _data[15] -
			_data[8] * _data[7] * _data[14] -
			_data[12] * _data[6] * _data[11] +
			_data[12] * _data[7] * _data[10];

		inv[8] = _data[4] * _data[9] * _data[15] -
			_data[4] * _data[11] * _data[13] -
			_data[8] * _data[5] * _data[15] +
			_data[8] * _data[7] * _data[13] +
			_data[12] * _data[5] * _data[11] -
			_data[12] * _data[7] * _data[9];

		inv[12] = -_data[4] * _data[9] * _data[14] +
			_data[4] * _data[10] * _data[13] +
			_data[8] * _data[5] * _data[14] -
			_data[8] * _data[6] * _data[13] -
			_data[12] * _data[5] * _data[10] +
			_data[12] * _data[6] * _data[9];

		inv[1] = -_data[1] * _data[10] * _data[15] +
			_data[1] * _data[11] * _data[14] +
			_data[9] * _data[2] * _data[15] -
			_data[9] * _data[3] * _data[14] -
			_data[13] * _data[2] * _data[11] +
			_data[13] * _data[3] * _data[10];

		inv[5] = _data[0] * _data[10] * _data[15] -
			_data[0] * _data[11] * _data[14] -
			_data[8] * _data[2] * _data[15] +
			_data[8] * _data[3] * _data[14] +
			_data[12] * _data[2] * _data[11] -
			_data[12] * _data[3] * _data[10];

		inv[9] = -_data[0] * _data[9] * _data[15] +
			_data[0] * _data[11] * _data[13] +
			_data[8] * _data[1] * _data[15] -
			_data[8] * _data[3] * _data[13] -
			_data[12] * _data[1] * _data[11] +
			_data[12] * _data[3] * _data[9];

		inv[13] = _data[0] * _data[9] * _data[14] -
			_data[0] * _data[10] * _data[13] -
			_data[8] * _data[1] * _data[14] +
			_data[8] * _data[2] * _data[13] +
			_data[12] * _data[1] * _data[10] -
			_data[12] * _data[2] * _data[9];

		inv[2] = _data[1] * _data[6] * _data[15] -
			_data[1] * _data[7] * _data[14] -
			_data[5] * _data[2] * _data[15] +
			_data[5] * _data[3] * _data[14] +
			_data[13] * _data[2] * _data[7] -
			_data[13] * _data[3] * _data[6];

		inv[6] = -_data[0] * _data[6] * _data[15] +
			_data[0] * _data[7] * _data[14] +
			_data[4] * _data[2] * _data[15] -
			_data[4] * _data[3] * _data[14] -
			_data[12] * _data[2] * _data[7] +
			_data[12] * _data[3] * _data[6];

		inv[10] = _data[0] * _data[5] * _data[15] -
			_data[0] * _data[7] * _data[13] -
			_data[4] * _data[1] * _data[15] +
			_data[4] * _data[3] * _data[13] +
			_data[12] * _data[1] * _data[7] -
			_data[12] * _data[3] * _data[5];

		inv[14] = -_data[0] * _data[5] * _data[14] +
			_data[0] * _data[6] * _data[13] +
			_data[4] * _data[1] * _data[14] -
			_data[4] * _data[2] * _data[13] -
			_data[12] * _data[1] * _data[6] +
			_data[12] * _data[2] * _data[5];

		inv[3] = -_data[1] * _data[6] * _data[11] +
			_data[1] * _data[7] * _data[10] +
			_data[5] * _data[2] * _data[11] -
			_data[5] * _data[3] * _data[10] -
			_data[9] * _data[2] * _data[7] +
			_data[9] * _data[3] * _data[6];

		inv[7] = _data[0] * _data[6] * _data[11] -
			_data[0] * _data[7] * _data[10] -
			_data[4] * _data[2] * _data[11] +
			_data[4] * _data[3] * _data[10] +
			_data[8] * _data[2] * _data[7] -
			_data[8] * _data[3] * _data[6];

		inv[11] = -_data[0] * _data[5] * _data[11] +
			_data[0] * _data[7] * _data[9] +
			_data[4] * _data[1] * _data[11] -
			_data[4] * _data[3] * _data[9] -
			_data[8] * _data[1] * _data[7] +
			_data[8] * _data[3] * _data[5];

		inv[15] = _data[0] * _data[5] * _data[10] -
			_data[0] * _data[6] * _data[9] -
			_data[4] * _data[1] * _data[10] +
			_data[4] * _data[2] * _data[9] +
			_data[8] * _data[1] * _data[6] -
			_data[8] * _data[2] * _data[5];

		det = _data[0] * inv[0] + _data[1] * inv[4] + _data[2] * inv[8] + _data[3] * inv[12];

		if (det == 0)
			return Matrix4();

		det = 1.f / det;

		for (i = 0; i < 16; i++)
			res[i] = inv[i] * det;

		return Matrix4(res);
	}

	Vector4d Matrix4::operator*(Vector4d vec)
	{
		float x = (vec.X() * _data[0]) + (vec.Y() * _data[1]) + (vec.Z() * _data[2]) + (vec.W() * _data[3]);
		float y = (vec.X() * _data[4]) + (vec.Y() * _data[5]) + (vec.Z() * _data[6]) + (vec.W() * _data[7]);
		float z = (vec.X() * _data[8]) + (vec.Y() * _data[9]) + (vec.Z() * _data[10]) + (vec.W() * _data[11]);
		float w = (vec.X() * _data[12]) + (vec.Y() * _data[13]) + (vec.Z() * _data[14]) + (vec.W() * _data[15]);

		return Vector4d(x, y, z, w);
	}

	Matrix4& Matrix4::operator*=(Matrix4 const& mat)
	{
		*this = *this * mat;

		return *this;
	}

	Matrix4 Matrix4::CreateMat4Translation(Vector3d const& vec)
	{
		Matrix4 mat;
		mat.Identity();

		mat._data[12] = vec.X();
		mat._data[13] = vec.Y();
		mat._data[14] = vec.Z();

		return mat;
	}

	Matrix4 Matrix4::CreateMat4Scale(Vector3d const& vec)
	{
		Matrix4 mat;
		mat.Identity();

		mat._data[0] = vec.X();
		mat._data[5] = vec.Y();
		mat._data[10] = vec.Z();

		return mat;
	}

	Matrix4 Matrix4::CreateMat4RotXDeg(float const& value)
	{
		Matrix4 mat;
		mat.Identity();

		float rad = Tools::Deg2Rad(value);

		mat._data[5] = cos(rad);
		mat._data[6] = sin(rad);
		mat._data[9] = -sin(rad);
		mat._data[10] = cos(rad);

		return mat;
	}

	Matrix4 Matrix4::CreateMat4RotYDeg(float const& value)
	{
		Matrix4 mat;
		mat.Identity();

		float rad = Tools::Deg2Rad(value);

		mat._data[0] = cos(rad);
		mat._data[2] = -sin(rad);
		mat._data[8] = sin(rad);
		mat._data[10] = cos(rad);

		return mat;
	}

	Matrix4 Matrix4::CreateMat4RotZDeg(float const& value)
	{
		Matrix4 mat;
		mat.Identity();

		float rad = Tools::Deg2Rad(value);

		mat._data[0] = cos(rad);
		mat._data[1] = sin(rad);
		mat._data[4] = -sin(rad);
		mat._data[5] = cos(rad);

		return mat;
	}

	Matrix4 Matrix4::CreateMat4Perspec(float fov, float aspectRatio, float near, float far)
	{
		float d = 1.0f / tan(fov / 2.0f);
		float range = 1.0f / (near - far);

		float data[16] = { d / aspectRatio, 0.0f, 0.0f, 0.0f ,
							0.0f, d, 0.0f, 0.0f ,
							0.0f, 0.0f, (near + far) * range, -1.0f,
							0.0f, 0.0f, (near * far * 2.0f) * range, 0.0f };


		return Matrix4(data);
	}

	Math::Vector3d Matrix4::RecoverTranslation()
	{
		return Math::Vector3d(_data[12], _data[13], _data[14]);
	}

	Math::Quaternion Matrix4::RecoverRotation()
	{
		Math::Vector3d scale = RecoverScale();

		float data[16] = {
			_data[0] / scale.X(), _data[1] / scale.Y(), _data[2] / scale.Z(), 0.f,
			_data[4] / scale.X(), _data[5] / scale.Y(), _data[6] / scale.Z(), 0.f,
			_data[8] / scale.X(), _data[9] / scale.Y(), _data[10] / scale.Z(), 0.f,
			0.f, 0.f, 0.f, 1.f
		};

		Math::Matrix4 rot(data);

		return rot.MatToQuat();
	}

	Math::Vector3d Matrix4::RecoverScale()
	{
		Math::Vector3d scale;

		Math::Vector3d column1(_data[0], _data[4], _data[8]);
		Math::Vector3d column2(_data[1], _data[5], _data[9]);
		Math::Vector3d column3(_data[2], _data[6], _data[10]);

		scale.X(column1.Magnitude());
		scale.Y(column2.Magnitude());
		scale.Z(column3.Magnitude());

		return scale;
	}

	void Matrix4::ConvertToMatView()
	{
		_data[12] *= -1.f;
		_data[13] *= -1.f;
		_data[14] *= -1.f;
	}

	Math::Vector3d Matrix4::GetForward()
	{
		return Vector3d(_data[2], _data[6], _data[10]);
	}

	Math::Vector3d Matrix4::GetBackward()
	{
		return GetForward() * -1.f;
	}
	
	Math::Vector3d Matrix4::GetUp()
	{
		return Vector3d(_data[1], _data[5], _data[9]);
	}

	Math::Vector3d Matrix4::GetDown()
	{
		return GetUp() * -1.f;
	}

	Math::Vector3d Matrix4::GetRight()
	{
		return Vector3d(_data[0], _data[4], _data[8]);
	}

	Math::Vector3d Matrix4::GetLeft()
	{
		return GetRight() * -1.f;
	}

	Math::Matrix4 Matrix4::LookAt(Math::Vector3d eye, Math::Vector3d target, Math::Vector3d up)
	{
		Math::Vector3d zAxis = eye - target;
		zAxis.Normalized();
		Math::Vector3d xAxis = zAxis.Cross(up);
		xAxis.Normalized();
		Math::Vector3d yAxis = xAxis.Cross(zAxis);

		float orientationData[16] = {
			xAxis.X(), yAxis.X(), zAxis.X(), 0.0f,
			xAxis.Y(), yAxis.Y(), zAxis.Y(), 0.0f,
			xAxis.Z(), yAxis.Z(), zAxis.Z(), 0.0f,
			xAxis.Dot(eye), yAxis.Dot(eye), zAxis.Dot(eye), 1.f };

		*this = Math::Matrix4(orientationData);

		return *this;
	}

	Math::Quaternion Matrix4::MatToQuat()
	{
		Math::Quaternion q;
		
		float trace = _data[0] + _data[5] + _data[10];
		float s;

		if (trace > 0)
		{
			s = 0.5f / sqrtf(trace + 1.f);

			q.W(0.25f / s);
			q.X((_data[6] - _data[9]) * s);
			q.Y((_data[8] - _data[2]) * s);
			q.Z((_data[1] - _data[4]) * s);
		}
		else
		{
			if (_data[0] > _data[5] && _data[0] > _data[10])
			{
				s = 2.0f * sqrtf(1.f + _data[0] - _data[5] - _data[10]);

				q.W((_data[6] - _data[9]) / s);
				q.X(0.25f * s);
				q.Y((_data[1] + _data[4]) / s);
				q.Z((_data[2] + _data[8]) / s);
			}
			else if (_data[5] > _data[10])
			{
				s = 2.0f * sqrtf(1.0f + _data[5] - _data[0] - _data[10]);

				q.W((_data[8] - _data[2]) / s);
				q.X((_data[1] + _data[4]) / s);
				q.Y(0.25f * s);
				q.Z((_data[6] + _data[9]) / s);
			}
			else
			{
				s = 2.0f * sqrtf(1.0f + _data[10] - _data[0] - _data[5]);

				q.W((_data[1] - _data[4]) / s);
				q.X((_data[2] + _data[8]) / s);
				q.Y((_data[6] + _data[9]) / s);
				q.Z(0.25f * s);
			}
		}

		return q;
	}

	bool Matrix4::IsOrthogonal() const
	{
		Matrix4 result = *this * Transpose();
		Matrix4 identity;

		if (result == identity)
			return true;

		return false;
	}

	bool Matrix4::operator==(Matrix4 const& mat) const
	{
		for (int idx = 0; idx < 16; ++idx)
		{
			if (_data[idx] != mat._data[idx])
				return false;
		}

		return true;
	}

	std::string Matrix4::ShowValue() const
	{
		std::string res = "Matrix4 = {\n";

		for (int idxLine = 0; idxLine < 4; ++idxLine)
		{
			for (int idxCol = 0; idxCol < 4; ++idxCol)
			{
				res += std::to_string(_data[(4 * idxLine) + idxCol]);
				res += ", ";
			}
			res += "\n";
		}

		res += "}";
		return res;
	}


	float* Matrix4::DataArray()
	{
		return _data;
	}

	std::vector<float> Matrix4::DataVector()
	{
		std::vector<float> data;

		for (int i = 0; i < 16; i++)
		{
			data.push_back(_data[i]);
		}

		return data;
	}
}