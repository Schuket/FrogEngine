#include "feSerializeManager.h"

#include <fstream>

#include <cereal\cereal.hpp>
#include <cereal/types/vector.hpp>

#include "../Component/Mesh/feModel.h"
#include "../Object/feObject.h"

namespace FrogEngine
{
	namespace System
	{
		void feSerializeManager::SaveScene(unsigned int const& idx, Object::feObject* root)
		{
			/*std::ofstream os("Scene" + std::to_string(idx) + ".xml");
			cereal::XMLOutputArchive archive(os);

			root->Save(archive);*/
		}

		void feSerializeManager::LoadScene(unsigned int const& idx, Object::feObject* root)
		{
			//std::ifstream is("Scene" + std::to_string(idx) + ".xml");
			//cereal::XMLInputArchive archive(is);
			//
			//std::string type;
			//
			//Object::feObject* obj = new Object::feObject();
			//
			//while (archive.getNodeName())
			//{
			//	archive(type);
			//
			//	if (type == "feObject")
			//	{
			//		obj = new Object::feObject();
			//
			//		obj->Load(archive);
			//
			//		std::string parent;
			//
			//		archive(parent);
			//
			//		if (parent == "0")
			//			obj->SetParent(root);
			//	}
			//	else if (type == "feModel")
			//	{
			//		std::string value;
			//		
			//		archive(value);
			//		
			//		const rttr::type classType = rttr::type::get_by_name(type.c_str());
			//		
			//		if (classType)
			//		{
			//			rttr::constructor ctor = classType.get_constructor({});
			//			rttr::variant var = ctor.invoke();
			//			
			//			if (var.can_convert(classType))
			//			{
			//				if (var.convert(classType))
			//				{
			//					const Component::feComponent& comp = var.get_value<Component::feComponent>();
			//				}
			//			}
			//		}
			//	}
			//}
			//root->Load(archive);
		}
	} // namespace System
} // namespace FrogEngine