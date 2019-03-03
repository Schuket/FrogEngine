#ifdef MATH_EXPORTS
#define VECTOR4D_API __declspec(dllexport) 
#else
#define VECTOR4D_API __declspec(dllimport) 
#endif

#pragma once

#include <string>
#include <vector>

namespace Math
{
	struct Vector2d;
	struct Vector3d;

	struct Vector4d
	{
		// Ctor / Dtor
		VECTOR4D_API Vector4d();
		VECTOR4D_API Vector4d(float x, float y, float z, float w);
		VECTOR4D_API Vector4d(Vector2d v, float z, float w);
		VECTOR4D_API Vector4d(Vector3d v, float w);
		VECTOR4D_API ~Vector4d();

		// Functions
		VECTOR4D_API bool operator==(Vector4d const& vec) const;
		VECTOR4D_API bool operator!=(Vector4d const& vec) const;

		VECTOR4D_API Vector4d operator+(Vector4d const& vec) const;
		VECTOR4D_API Vector4d operator-(Vector4d const& vec) const;
		VECTOR4D_API Vector4d operator*(float const value) const;
		VECTOR4D_API Vector4d GetNormalize() const;

		VECTOR4D_API Vector4d& operator+=(Vector4d const& vec);
		VECTOR4D_API Vector4d& operator-=(Vector4d const& vec);
		VECTOR4D_API Vector4d& operator*=(float const value);
		VECTOR4D_API Vector4d& Normalized();

		VECTOR4D_API float Norm() const;
		VECTOR4D_API float Dot(Vector4d const& vec) const;
		VECTOR4D_API float Magnitude() const;

		VECTOR4D_API std::vector<float> DataVector();
		VECTOR4D_API std::string ShowValue() const;

#pragma region Getters/Setters
		VECTOR4D_API void X(float const& value) { _x = value; };
		VECTOR4D_API void Y(float const& value) { _y = value; };
		VECTOR4D_API void Z(float const& value) { _z = value; };
		VECTOR4D_API void W(float const& value) { _w = value; };

		VECTOR4D_API float X() const { return _x; };
		VECTOR4D_API float Y() const { return _y; };
		VECTOR4D_API float Z() const { return _z; };
		VECTOR4D_API float W() const { return _w; };
#pragma endregion

		VECTOR4D_API bool CheckIfEqual(Vector4d const& vec) const;
	private:
		// Variables
		float _x, _y, _z, _w;
	};
}
