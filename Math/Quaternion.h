#ifdef MATH_EXPORTS
#define Quaternion_API __declspec(dllexport) 
#else
#define Quaternion_API __declspec(dllimport) 
#endif

#pragma once

#include <string>
#include <vector>

namespace Math
{
	struct Matrix4;
	struct Vector3d;

	struct Quaternion 
	{
		// Ctor / Dtor
		Quaternion_API Quaternion();
		Quaternion_API Quaternion(float qx, float qy, float qz, float qw);
		Quaternion_API ~Quaternion();
		
		Quaternion_API Quaternion operator/(float value);
		Quaternion_API Quaternion operator*(float value);
		Quaternion_API Quaternion operator*(const Quaternion& quat);
		Quaternion_API Quaternion operator+(const Quaternion& quat);
		Quaternion_API void operator=(Quaternion const& quat);
		Quaternion_API void operator*=(float const& value);
		Quaternion_API void operator*=(const Quaternion& value);
		Quaternion_API bool operator==(Quaternion const& quat);
		Quaternion_API bool operator!=(Quaternion const& quat);

		Quaternion_API static Quaternion QuatFromAxisRad(float radians, float x, float y, float z);
		Quaternion_API static Quaternion QuatFromAxisDeg(float deg, float x, float y, float z);
		Quaternion_API static Quaternion Normalize(Quaternion& quat);
		Quaternion_API static Quaternion Slerp(Quaternion& q, Quaternion& r, float t);
		Quaternion_API static Matrix4 QuatToMat4(const Quaternion& quat);

		Quaternion_API float Dot(const Quaternion& quat);

		Quaternion_API std::vector<float> DataVector();
		Quaternion_API std::string ShowValue();

		Quaternion_API void Inv();
		Quaternion_API Quaternion GetConjugate() const;

		Quaternion_API float Norm();

		Quaternion_API float X() const;
		Quaternion_API float Y() const;
		Quaternion_API float Z() const;
		Quaternion_API float W() const;
		Quaternion_API void X(float const& value);
		Quaternion_API void Y(float const& value);
		Quaternion_API void Z(float const& value);
		Quaternion_API void W(float const& value);
	private:
		// Variables
		float _x, _y, _z, _w;
	};

} //namespace Math