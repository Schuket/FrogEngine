#ifdef MATH_EXPORTS
#define VECTOR3D_API __declspec(dllexport) 
#else
#define VECTOR3D_API __declspec(dllimport) 
#endif

#pragma once

#include <string>
#include <vector>

namespace Math
{
	struct Vector2d;
	struct Quaternion;

	struct VECTOR3D_API Vector3d
	{
		// Ctor / Dtor
		Vector3d();
		Vector3d(float x, float y, float z);
		Vector3d(Vector2d v, float z);
		~Vector3d();

		// Functions
		static Vector3d Up();
		static Vector3d Forward();
		static Vector3d Right();

		bool operator==(Vector3d const& vec) const;
		bool operator!=(Vector3d const& vec) const;
		
		Vector3d operator+(Vector3d const& vec) const;
		Vector3d operator-(Vector3d const& vec) const;
		Vector3d operator*(float const value) const;
		
		Vector3d GetNormalize() const;
		Vector3d GetRotated(Quaternion quat) const;
		Vector3d Cross(Vector3d const& vec) const;

		Vector3d& operator+=(Vector3d const& vec);
		Vector3d& operator-=(Vector3d const& vec);
		Vector3d& operator*=(float const value);
		Vector3d& Normalized();
		Vector3d& Rotate(Quaternion quat);

		float Norm() const;
		float Dot(Vector3d const& vec) const;
		float Magnitude() const;

		float* DataArray();
		std::vector<float> DataVector();
		std::string ShowValue() const;

#pragma region Getters/Setters
		void X(float const& value) { _x = value; };
		void Y(float const& value) { _y = value; };
		void Z(float const& value) { _z = value; };
		
		float X() const { return _x; };
		float Y() const { return _y; };
		float Z() const { return _z; };
#pragma endregion

		bool CheckIfEqual(Vector3d const& vec) const;

	private:
		// Variables
		float _x, _y, _z;
	};
}