#include "Vector3d.h"

#include <string>

#include "Vector2d.h"
#include "Quaternion.h"

namespace Math
{
	Vector3d::Vector3d()
	{
		_x = _y = _z = 0.f;
	}

	Vector3d::Vector3d(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	Vector3d::Vector3d(Vector2d v, float z)
	{
		_x = v.X();
		_y = v.Y();
		_z = z;
	}

	Vector3d::~Vector3d()
	{}

	Vector3d Vector3d::Up()
	{
		return Vector3d(0.f, 1.f, 0.f);
	}

	Vector3d Vector3d::Forward()
	{
		return Vector3d(0.f, 0.f, -1.f);
	}

	Vector3d Vector3d::Right()
	{
		return Vector3d(1.f, 0.f, 0.f);
	}

	bool Vector3d::operator==(Vector3d const& vec) const
	{
		return CheckIfEqual(vec);
	}

	bool Vector3d::operator!=(Vector3d const& vec) const
	{
		return !CheckIfEqual(vec);
	}

	Vector3d Vector3d::operator+(Vector3d const& vec) const
	{
		float x = _x + vec._x;
		float y = _y + vec._y;
		float z = _z + vec._z;

		return Vector3d(x, y ,z);
	}

	Vector3d Vector3d::operator-(Vector3d const& vec) const
	{
		float x = _x - vec._x;
		float y = _y - vec._y;
		float z = _z - vec._z;

		return Vector3d(x, y, z);
	}

	Vector3d Vector3d::operator*(float const value) const
	{
		float x = _x * value;
		float y = _y * value;
		float z = _z * value;

		return Vector3d(x, y, z);
	}

	Vector3d Vector3d::GetNormalize() const
	{
		if (Norm() == 0.f)
			return Vector3d(0.f, 0.f, 0.f);

		float x = _x / Norm();
		float y = _y / Norm();
		float z = _z / Norm();

		return Vector3d(x, y, z);
	}

	Vector3d Vector3d::GetRotated(Quaternion quat) const
	{
		Math::Quaternion quatToRotate = Math::Quaternion(_x, _y, _z, 0.f);
		Math::Quaternion conjQuat = quat.GetConjugate();

		Math::Quaternion rotated = (quat * quatToRotate) * conjQuat;

		return Math::Vector3d(rotated.X(), rotated.Y(), rotated.Z());
	}

	Vector3d Vector3d::Cross(Vector3d const& vec) const
	{
		float x = (_y * vec._z) - (_z * vec._y);
		float y = (_z * vec._x) - (_x * vec._z);
		float z = (_x * vec._y) - (_y * vec._x);

		return Vector3d(x, y, z);
	}

	Vector3d& Vector3d::operator+=(Vector3d const& vec)
	{
		*this = *this + vec;

		return *this;
	}

	Vector3d& Vector3d::operator-=(Vector3d const& vec)
	{
		*this = *this - vec;

		return *this;
	}

	Vector3d& Vector3d::operator*=(float const value)
	{
		*this = *this * value;

		return *this;
	}

	Vector3d& Vector3d::Normalized()
	{
		*this = GetNormalize();

		return *this;
	}

	Vector3d& Vector3d::Rotate(Quaternion quat)
	{
		*this = GetRotated(quat);

		return *this;
	}

	float Vector3d::Norm() const
	{
		return sqrt((_x * _x) + (_y * _y) + (_z * _z));
	}

	float Vector3d::Dot(Vector3d const& vec) const
	{
		return (_x * vec._x) + (_y * vec._y) + (_z * vec._z);
	}

	float Vector3d::Magnitude() const
	{
		return sqrt((_x * _x) + (_y * _y) + (_z * _z));
	}

	float* Vector3d::DataArray()
	{
		float res[] = { _x, _y, _z };

		return res;
	}

	std::vector<float> Vector3d::DataVector()
	{
		std::vector<float> res = { _x, _y, _z };
		return res;
	}

	std::string Vector3d::ShowValue() const
	{
		std::string x = std::to_string(_x);
		std::string y = std::to_string(_y);
		std::string z = std::to_string(_z);

		return "Vector3d = { " + x + ", " + y + ", " + z + "}";
	}

	bool Vector3d::CheckIfEqual(Vector3d const& vec) const
	{
		if (_x == vec._x && _y == vec._y && _z == vec._z)
			return true;
		
		return false;
	}
}