#include "Vector4d.h"


#include "Vector2d.h"
#include "Vector3d.h"

namespace Math
{
	Vector4d::Vector4d()
	{
		_x = _y = _z = _w = 0.f;
	}

	Vector4d::Vector4d(float x, float y, float z, float w)
	{
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}

	Vector4d::Vector4d(Vector2d v, float z, float w)
	{
		_x = v.X();
		_y = v.Y();
		_z = z;
		_w = w;
	}

	Vector4d::Vector4d(Vector3d v, float w)
	{
		_x = v.X();
		_y = v.Y();
		_z = v.Z();
		_w = w;
	}

	Vector4d::~Vector4d()
	{}

	bool Vector4d::operator==(Vector4d const& vec) const
	{
		return CheckIfEqual(vec);
	}

	bool Vector4d::operator!=(Vector4d const& vec) const
	{
		return !CheckIfEqual(vec);
	}

	Vector4d Vector4d::operator+(Vector4d const& vec) const
	{
		float x = _x + vec._x;
		float y = _y + vec._y;
		float z = _z + vec._z;
		float w = _w + vec._w;

		return Vector4d(x, y, z, w);
	}

	Vector4d Vector4d::operator-(Vector4d const& vec) const
	{
		float x = _x - vec._x;
		float y = _y - vec._y;
		float z = _z - vec._z;
		float w = _w - vec._w;

		return Vector4d(x, y, z, w);
	}

	Vector4d Vector4d::operator*(float const value) const
	{
		float x = _x * value;
		float y = _y * value;
		float z = _z * value;
		float w = _w * value;

		return Vector4d(x, y, z, w);
	}

	Vector4d Vector4d::GetNormalize() const
	{
		float x = _x / Norm();
		float y = _y / Norm();
		float z = _z / Norm();
		float w = _w / Norm();

		return Vector4d(x, y, z, w);
	}

	Vector4d& Vector4d::operator+=(Vector4d const& vec)
	{
		*this = *this + vec;

		return *this;
	}

	Vector4d& Vector4d::operator-=(Vector4d const& vec)
	{
		*this = *this - vec;

		return *this;
	}

	Vector4d& Vector4d::operator*=(float const value)
	{
		*this = *this * value;

		return *this;
	}

	Vector4d& Vector4d::Normalized()
	{
		*this = GetNormalize();

		return *this;
	}

	float Vector4d::Norm() const
	{
		return sqrt((_x * _x) + (_y * _y) + (_z * _z) + (_w * _w));
	}

	float Vector4d::Dot(Vector4d const& vec) const
	{
		return (_x * vec._x) + (_y * vec._y) + (_z * vec._z) + (_w * vec._w);
	}

	float Vector4d::Magnitude() const
	{
		return sqrt((_x * _x) + (_y * _y) + (_z * _z) + (_w * _w));
	}

	std::vector<float> Vector4d::DataVector()
	{
		std::vector<float> res = { _x, _y, _z , _w};
		return res;
	}

	std::string Vector4d::ShowValue() const
	{
		std::string x = std::to_string(_x);
		std::string y = std::to_string(_y);
		std::string z = std::to_string(_z);
		std::string w = std::to_string(_w);

		return "Vector4d = { " + x + ", " + y + ", " + z + ", " + w + "}";
	}

	bool Vector4d::CheckIfEqual(Vector4d const& vec) const
	{
		if (_x == vec._x && _y == vec._y && _z == vec._z && _w == vec._w)
			return true;

		return false;
	}
}