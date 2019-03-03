#include "feObject.h"

#include <sstream>

#include "../Component/Mesh/feModel.h"

namespace FrogEngine
{
	namespace Object
	{
		template<typename T>
		T* feObject::GetComponent()
		{
			std::size_t tHashCode = typeid(T).hash_code();
			std::map<std::size_t, Component::feComponent*>::iterator it = _components.begin();
			for (; it != _components.end(); ++it)
			{
				if (it->first == tHashCode)
					return static_cast<T*>(it->second);
			}

			return nullptr;
		}

		template <class Archive>
		void feObject::Save(Archive & ar) const
		{
			size_t len = _children.size();
			for (size_t idx = 0; idx < len; ++idx)
				_children[idx]->Save(ar);

			if (_name != "root")
			{
				std::vector<unsigned int> children;
				for (unsigned int idx = 0; idx < len; ++idx)
					children.push_back(_children[idx]->GetID());

				std::string type = "feObject";

				std::vector<float> pos = _transform.GetLocalTranslation().DataVector();
				std::vector<float> rot = _transform.GetLocalRotation().DataVector();
				std::vector<float> scale = _transform.GetLocalScale().DataVector();

				unsigned int parent = 0;
				if (_parent)
					parent = _parent->GetID();

				ar(CEREAL_NVP(type));
				ar(CEREAL_NVP(_id));
				ar(CEREAL_NVP(_name));
				ar(CEREAL_NVP(pos));
				ar(CEREAL_NVP(rot));
				ar(CEREAL_NVP(scale));
				ar(CEREAL_NVP(parent));
				ar(CEREAL_NVP(children));

				std::map<std::size_t, FrogEngine::Component::feComponent*>::const_iterator it = _components.begin();
				std::map<std::size_t, FrogEngine::Component::feComponent*>::const_iterator end = _components.end();
				
				for (; it != end; it++)
					it->second->Save(ar);
			}
		}

		template <class Archive>
		void feObject::Load(Archive & ar)
		{
			unsigned int id;
			std::string name;

			ar(cereal::make_nvp("_id", id));
			_id = id;

			ar(cereal::make_nvp("_name", name));
			_name = std::string(name);

			std::vector<float> pos;
			std::vector<float> rot;
			std::vector<float> scale;
			
			ar(pos);
			ar(rot);
			ar(scale);
			
			_transform.Translate(Math::Vector3d(pos[0], pos[1], pos[2]));
			_transform.SetRotation(Math::Quaternion(rot[0], rot[1], rot[2], rot[3]));
			_transform.Scale(Math::Vector3d(scale[0], scale[1], scale[2]));
		}
	}
}