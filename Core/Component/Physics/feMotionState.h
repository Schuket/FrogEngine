#pragma once

#include "btBulletDynamicsCommon.h"


namespace FrogEngine
{
	namespace Object
	{
		class feObject;
		class feTransform;
	}

	namespace Component
	{
		namespace Physics
		{
			class feCollider;


			class feMotionState : public btMotionState
			{
			public:
				feMotionState(Object::feObject* feObj, Object::feTransform* colliderTransform, feCollider* owner);
				feMotionState(feMotionState& copy);

				void UpdateBulletColliderTransform(Object::feTransform trs);

			private:
				virtual void getWorldTransform(btTransform& worldTrans) const;
				virtual void setWorldTransform(const btTransform& worldTrans);

				feCollider* _owner;
				Object::feObject* _obj;
				Object::feTransform* _offset;
			};
		}
	}
}