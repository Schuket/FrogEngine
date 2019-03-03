#ifdef MATH_EXPORTS
#define TOOLS_API __declspec(dllexport) 
#else
#define TOOLS_API __declspec(dllimport) 
#endif

#define PI 3.14159265359f

#include <string>
#include "Vector3d.h"

namespace Math
{
	struct Tools
	{
		// Functions
		template<class T>
		static T Clamp(T f, T min, T max);

		TOOLS_API static void Swap(float& val1, float& val2);
		TOOLS_API static float Deg2Rad(float value);
		TOOLS_API static float Rad2Deg(float value);
		TOOLS_API static void Split(std::string origin, const char* separator, bool begin, std::string& res1, std::string& res2);
		TOOLS_API static Vector3d Normalized(const Vector3d vec);
		TOOLS_API static Vector3d Cross(const Vector3d vec1, const Vector3d vec2);
		TOOLS_API static float Sign(float value);
		TOOLS_API static bool Epsilon(int v1, int v2);
		TOOLS_API static bool Epsilon(float v1, float v2);

		//Clamp any number into a ratio from 0 to 1
		TOOLS_API static float ToRatio(float f);
		//Ration need to be in range of 0 to 1
		TOOLS_API static float ReverseRatio(float f);
	};
}