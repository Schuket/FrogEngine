#include "Quaternion.h"

#include "Tools.h"
#include "Matrix4.h"

namespace Math {

	Quaternion::Quaternion()
	{
		_w = 1.f; _x = 0.f; _y = 0.f; _z = 0.f;
	}
	Quaternion::Quaternion(float qx, float qy, float qz, float qw)
	{
		_w = qw; _x = qx; _y = qy; _z = qz;
	}
	Quaternion::~Quaternion() {}

	Quaternion Quaternion::QuatFromAxisRad(float radians, float x, float y, float z)
	{
		Quaternion result;
		result._w = cos(radians / 2.0f);
		result._x = sin(radians / 2.0f) * x;
		result._y = sin(radians / 2.0f) * y;
		result._z = sin(radians / 2.0f) * z;
		
		return result;
	}

	Quaternion Quaternion::QuatFromAxisDeg(float deg, float x, float y, float z)
	{
		return QuatFromAxisRad(Tools::Deg2Rad(deg), x, y, z);
	}

	Matrix4 Quaternion::QuatToMat4(const Quaternion& q)
	{
		float w = q._w;
		float x = q._x;
		float y = q._y;
		float z = q._z;

		float matData[16] = { 1.0f - 2.0f * y * y - 2.0f * z * z,
								2.0f * x * y + 2.0f * w * z,
								2.0f * x * z - 2.0f * w * y,
								0.f,
								2.0f * x * y - 2.0f * w * z,
								1.0f - 2.0f * x * x - 2.0f * z * z,
								2.0f * y * z + 2.0f * w * x,
								0.f,
								2.0f * x * z + 2.0f * w * y,
								2.0f * y * z - 2.0f * w * x,
								1.0f - 2.0f * x * x - 2.0f * y * y,
								0.0f,
								0.0f,
								0.0f,
								0.0f,
								1.0f };

		return Matrix4(matData);
	}

	Quaternion Quaternion::Normalize(Quaternion& q)
	{
		float sum = q._x * q._x + q._y * q._y + q._z * q._z + q._w * q._w;
		const float tresh = 0.0001f;
		if (fabs(1.0f - sum) < tresh)
			return q;
		float mag = sqrt(sum);
		return q / mag;
	}

	float Quaternion::Dot(const Quaternion& q) 
	{
		return _x * q._x + _y * q._y + _z * q._z + _w * q._w;
	}

	Quaternion Quaternion::Slerp(Quaternion& q, Quaternion& r, float t)
	{
		float cos_half_theta = q.Dot(r);

		if (cos_half_theta < 0.0f)
		{
			q.Inv();
			
			cos_half_theta = q.Dot(r);
		}

		if (fabs(cos_half_theta) >= 1.0f)
			return q;

		float sin_half_theta = sqrt(1.0f - cos_half_theta * cos_half_theta);
		Quaternion result;
		if (fabs(sin_half_theta) < 0.001f)
		{
			result._w = (1.f - t) * q._w +t * r._w;
			result._x = (1.f - t) * q._x +t * r._x;
			result._y = (1.f - t) * q._y +t * r._y;
			result._z = (1.f - t) * q._z +t * r._z;
				
			return result;
		}

		float half_theta = acos(cos_half_theta);
		float a = sin((1.0f - t) * half_theta) / sin_half_theta;
		float b = sin(t * half_theta) / sin_half_theta;

		result._w = q._w * a + b * r._w;
		result._x = q._x * a + b * r._x;
		result._y = q._y * a + b * r._y;
		result._z = q._z * a + b * r._z;

		return result;
	}

	Quaternion Quaternion::operator/(float value)
	{
		Quaternion result;
		result._w = _w / value;
		result._x = _x / value;
		result._y = _y / value;
		result._z = _z / value;
		return result;
	}

	Quaternion Quaternion::operator*(float value)
	{
		Quaternion result;
		result._w = _w * value;
		result._x = _x * value;
		result._y = _y * value;
		result._z = _z * value;
		return result;
	}

	Quaternion Quaternion::operator*(const Quaternion& q)
	{
		Quaternion result;
		result._w = q._w * _w - q._x * _x - q._y * _y - q._z * _z;
		result._x = q._w * _x + q._x * _w - q._y * _z + q._z * _y;
		result._y = q._w * _y + q._x * _z + q._y * _w - q._z * _x;
		result._z = q._w * _z - q._x * _y + q._y * _x + q._z * _w;
		return result;
	}

	Quaternion Quaternion::operator+(const Quaternion& q)
	{
		Quaternion result;
		result._w = _w + q._w;
		result._x = _x + q._x;
		result._y = _y + q._y;
		result._z = _z + q._z;
		return result;
	}

	void Quaternion::operator=(Quaternion const& quat)
	{
		_w = quat._w;
		_x = quat._x;
		_y = quat._y;
		_z = quat._z;
	}

	bool Quaternion::operator==(Quaternion const& quat)
	{
		if (Tools::Epsilon(_x, quat._x) && Tools::Epsilon(_y, quat._y) && Tools::Epsilon(_z, quat._z) && Tools::Epsilon(_w, quat._w))
			return true;

		return false;
	}

	bool Quaternion::operator!=(Quaternion const& quat)
	{
		if (*this == quat)
			return false;

		return true;
	}

	void Quaternion::operator*=(float const& value)
	{
		*this = *this * value;
	}

	void Quaternion::operator*=(const Quaternion& q)
	{
		Quaternion result;
		result._w = q._w * _w - q._x * _x - q._y * _y - q._z * _z;
		result._x = q._w * _x + q._x * _w - q._y * _z + q._z * _y;
		result._y = q._w * _y + q._x * _z + q._y * _w - q._z * _x;
		result._z = q._w * _z - q._x * _y + q._y * _x + q._z * _w;

		_w = result._w;
		_x = result._x;
		_y = result._y;
		_z = result._z;
	}

	void Quaternion::Inv()
	{
		_w *= -1.f;
		_x *= -1.f;
		_y *= -1.f;
		_z *= -1.f;
	}

	Quaternion Quaternion::GetConjugate() const
	{
		Quaternion conj;
		conj._w = _w;
		conj._x = _x * -1;
		conj._y = _y * -1;
		conj._z = _z * -1;
		return conj;
	}

	float Quaternion::Norm()
	{
		return sqrt((_x * _x) + (_y * _y) + (_z * _z) + (_w * _w));
	}

	std::vector<float> Quaternion::DataVector()
	{
		std::vector<float> res = { _x, _y, _z, _w };
		return res;

	}

	std::string Quaternion::ShowValue()
	{
		std::string result = "X : " + std::to_string(_x) + " | Y : " + std::to_string(_y) + " | Z : " + std::to_string(_z) + " | W : " + std::to_string(_w);
		return result;
	}

	float Quaternion::X() const	{ return _x; }
	float Quaternion::Y() const { return _y; }
	float Quaternion::Z() const { return _z; }
	float Quaternion::W() const { return _w; }

	void Quaternion::X(float const& value) { _x = value; }
	void Quaternion::Y(float const& value) { _y = value; }
	void Quaternion::Z(float const& value) { _z = value; }
	void Quaternion::W(float const& value) { _w = value; }

} //namespace Math