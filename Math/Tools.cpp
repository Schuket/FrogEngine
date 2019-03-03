#include "Tools.h"

#include <cmath>
#include <algorithm>

namespace Math
{
	template<class T>
	T Tools::Clamp(T f, T min, T max)
	{
		return std::min(max, std::max(f, min));
	}

	template TOOLS_API int Tools::Clamp(int f, int min, int max);
	template TOOLS_API float Tools::Clamp(float f, float min, float max);
	template TOOLS_API double Tools::Clamp(double f, double min, double max);
	template TOOLS_API unsigned int Tools::Clamp(unsigned int f, unsigned int min, unsigned int max);

	void Tools::Swap(float& val1, float& val2)
	{
		float inter = val1;
		val1 = val2;
		val2 = inter;
	}

	float Tools::Deg2Rad(float value)
	{
		return float(PI * value / 180.f);
	}

	float Tools::Rad2Deg(float value)
	{
		return float(180.f * value / PI);
	}
	void Tools::Split(std::string origin, const char* separator, bool begin, std::string& res1, std::string& res2)
	{
		std::string::size_type n;

		if (begin)
			n = origin.find(separator);
		else
			n = origin.find_last_of(separator);

		res1 = origin.substr(0, n);

		res2 = origin.substr(n + 1, origin.size());
	}
	Vector3d Tools::Normalized(const Vector3d vec)
	{
		float Norm = sqrt((vec.X() * vec.X()) + (vec.Y() * vec.Y()) + (vec.Z() * vec.Z()));

		float x = vec.X() / Norm;
		float y = vec.Y() / Norm;
		float z = vec.Z() / Norm;

		return Vector3d(x, y, z);
	}
	Vector3d Tools::Cross(const Vector3d vec1, const Vector3d vec2)
	{
		float x = (vec1.Y() * vec2.Z()) - (vec1.Z() * vec2.Y());
		float y = (vec1.Z() * vec2.X()) - (vec1.X() * vec2.Z());
		float z = (vec1.X() * vec2.Y()) - (vec1.Y() * vec2.X());
		
		return Vector3d(x, y, z);
	}

	float Tools::Sign(float value)
	{
		return (value >= 0.f) ? 1.f : -1.f;
	}

	bool Tools::Epsilon(int v1, int v2)
	{
		if (abs(v1 - v2) <= 1)
			return true;
		
		return false;
	}

	bool Tools::Epsilon(float v1, float v2)
	{
		if (abs(v1 - v2) <= 0.001)
			return true;

		return false;
	}

	float Tools::ToRatio(float f)
	{
		return Clamp(f, 0.f, 1.f);
	}

	float Tools::ReverseRatio(float f)
	{
		return f * -1 + 1;
	}
}