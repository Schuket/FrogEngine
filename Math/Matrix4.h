#ifdef MATH_EXPORTS
#define Matrix4_API __declspec(dllexport) 
#else
#define Matrix4_API __declspec(dllimport) 
#endif

#pragma once 

#include <string>
#include <vector>

namespace Math
{
	struct Vector3d;
	struct Vector4d;
	struct Quaternion;

	struct Matrix4
	{
		// Ctor / Dtor
		Matrix4_API Matrix4();
		Matrix4_API Matrix4(float data[16]);
		Matrix4_API Matrix4(Vector4d X, Vector4d Y, Vector4d Z, Vector4d W);
		Matrix4_API ~Matrix4() = default;

		// Functions
		Matrix4_API void Identity();
				    
		Matrix4_API Matrix4 operator*(Matrix4 const& mat) const;
		Matrix4_API Matrix4 Transpose() const;
		Matrix4_API Matrix4 Inverse() const;
		
		Matrix4_API Vector4d operator*(Vector4d vec);

		Matrix4_API Matrix4& operator*=(Matrix4 const& mat);
		Matrix4_API static Matrix4 CreateMat4Translation(Vector3d const& vec);
		Matrix4_API static Matrix4 CreateMat4Scale(Vector3d const& vec);
		Matrix4_API static Matrix4 CreateMat4RotXDeg(float const& value);
		Matrix4_API static Matrix4 CreateMat4RotYDeg(float const& value);
		Matrix4_API static Matrix4 CreateMat4RotZDeg(float const& value);
		Matrix4_API static Matrix4 CreateMat4Perspec(float fov, float aspectRatio, float near, float far);

		Matrix4_API Math::Vector3d RecoverTranslation();
		Matrix4_API Math::Quaternion RecoverRotation();
		Matrix4_API Math::Vector3d RecoverScale();

		Matrix4_API void ConvertToMatView();
		Matrix4_API Math::Vector3d GetForward();
		Matrix4_API Math::Vector3d GetBackward();
		Matrix4_API Math::Vector3d GetUp();
		Matrix4_API Math::Vector3d GetDown();
		Matrix4_API Math::Vector3d GetRight();
		Matrix4_API Math::Vector3d GetLeft();
		Matrix4_API Math::Matrix4 LookAt(Math::Vector3d eye, Math::Vector3d target, Math::Vector3d up);

		Matrix4_API Math::Quaternion MatToQuat();

		Matrix4_API bool IsOrthogonal() const;
		Matrix4_API bool operator==(Matrix4 const& mat) const;
				    
		Matrix4_API std::string ShowValue() const;
				    
		Matrix4_API float* DataArray();
		Matrix4_API std::vector<float> DataVector();
		
	private:
		// Variables
		float _data[16];
	};
}

