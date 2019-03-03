#include "Vector2d.h"

#include <cmath>

namespace Math
{
	Vector2d::Vector2d()
	{
		_x = _y = 0.f;
	}

	Vector2d::Vector2d(float x, float y)
	{
		_x = x;
		_y = y;
	}

	Vector2d::~Vector2d()
	{}

	bool Vector2d::operator==(Vector2d const& vec) const
	{
		return CheckIfEqual(vec);
	}

	bool Vector2d::operator!=(Vector2d const& vec) const
	{
		return !CheckIfEqual(vec);
	}

	Vector2d Vector2d::operator+(Vector2d const& vec) const
	{
		float x = _x + vec._x;
		float y = _y + vec._y;

		return Vector2d(x,y);
	}

	Vector2d Vector2d::operator-(Vector2d const& vec) const
	{
		float x = _x - vec._x;
		float y = _y - vec._y;

		return Vector2d(x, y);
	}

	Vector2d Vector2d::operator*(float const value) const
	{
		float x = _x * value;
		float y = _y * value;

		return Vector2d(x, y);
	}

	Vector2d Vector2d::GetNormalize() const
	{
		float x = _x / Norm();
		float y = _y / Norm();

		return Vector2d(x, y);
	}

	Vector2d& Vector2d::operator+=(Vector2d const& vec)
	{
		*this = *this + vec;

		return *this;
	}

	Vector2d& Vector2d::operator-=(Vector2d const& vec)
	{
		*this = *this - vec;

		return *this;
	}

	Vector2d& Vector2d::operator*=(float const value)
	{
		*this = *this * value;

		return *this;
	}

	Vector2d& Vector2d::Normalized()
	{
		*this = GetNormalize();

		return *this;
	}

	float Vector2d::Norm() const
	{
		return sqrt((_x * _x) + (_y * _y));
	}

	std::string Vector2d::ShowValue() const
	{
		std::string x = std::to_string(_x);
		std::string y = std::to_string(_y);

		return "Vector2d = { " + x + ", " + y + "}";
	}

	bool Vector2d::CheckIfEqual(Vector2d const& vec) const
	{
		if (_x == vec._x && _y == vec._y)
			return true;

		return false;
	}
}