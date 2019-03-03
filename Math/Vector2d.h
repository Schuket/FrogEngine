#ifdef MATH_EXPORTS
#define VECTOR2D_API __declspec(dllexport) 
#else
#define VECTOR2D_API __declspec(dllimport) 
#endif

#pragma once

#include <string>

namespace Math
{
	struct Vector2d
	{
		// Ctor / Dtor
		VECTOR2D_API Vector2d();
		VECTOR2D_API Vector2d(float x, float y);
		VECTOR2D_API ~Vector2d();

		// Functions
		VECTOR2D_API bool operator==(Vector2d const& vec) const;
		VECTOR2D_API bool operator!=(Vector2d const& vec) const;
		
		VECTOR2D_API Vector2d operator+(Vector2d const& vec) const;
		VECTOR2D_API Vector2d operator-(Vector2d const& vec) const;
		VECTOR2D_API Vector2d operator*(float const value) const;
		VECTOR2D_API Vector2d GetNormalize() const;
		
		VECTOR2D_API Vector2d& operator+=(Vector2d const& vec);
		VECTOR2D_API Vector2d& operator-=(Vector2d const& vec);
		VECTOR2D_API Vector2d& operator*=(float const value);
		VECTOR2D_API Vector2d& Normalized();
		
		VECTOR2D_API float Norm() const;
		
		VECTOR2D_API std::string ShowValue() const;

#pragma region Getters/Setters
		VECTOR2D_API void X(float const& value) { _x = value; };
		VECTOR2D_API void Y(float const& value) { _y = value; };
		
		VECTOR2D_API float X() const { return _x; };
		VECTOR2D_API float Y() const { return _y; };
#pragma endregion
		VECTOR2D_API bool CheckIfEqual(Vector2d const& vec) const;

	private:
		// Variables
		float _x, _y;
	};
}