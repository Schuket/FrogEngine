#pragma once

#include <cereal\archives\xml.hpp>

namespace FrogEngine
{
	namespace Object
	{
		class feObject;
	} // namespace Object

	namespace System
	{
		class feSerializeManager
		{
		public:
			static void SaveScene(unsigned int const& idx, Object::feObject* root);
			static void LoadScene(unsigned int const& idx, Object::feObject* root);
		};
	} // namespace System
} // namespace FrogEngine