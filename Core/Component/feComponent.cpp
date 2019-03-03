#include "feComponent.h"

namespace FrogEngine
{
	namespace Component
	{
		feComponent::feComponent(feComponent const& copy)
		{
			_typeID = copy._typeID;
			_type = copy._type;
		}

		feComponent::~feComponent()
		{
			_owner = nullptr;
		}

		std::size_t feComponent::GetTypeID() const
		{
			return _typeID;
		}

		ComponentType feComponent::GetType() const
		{
			return _type;
		}

		Object::feObject* feComponent::GetOwner() const
		{
			return _owner;
		}

		void feComponent::SetOwner(Object::feObject* const& owner)
		{
			_owner = owner;
		}
	
	} //namespace Component
} //namespace FrogEngine