#include "feComponent.h"

namespace FrogEngine {
	namespace Component	{

		template <class Archive>
		void feComponent::Save(Archive & ar) const
		{
			switch (_type)
			{
			case ComponentType::Camera:
				_owner->GetComponent<Video::feCamera>()->Save(ar);
				return;
			case ComponentType::Mesh:
				_owner->GetComponent<Mesh::feModel>()->Save(ar);
				return;
			case ComponentType::Light:
				_owner->GetComponent<Light::feLight>()->Save(ar);
				return;
			}
		}
	}
}