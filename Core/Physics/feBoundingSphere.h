#pragma once

#include "Math\Vector3d.h"

#include "Core/Object/feTransform.h"
#include "RHI/RHI.h"

namespace FrogEngine
{
	namespace Physics
	{
			struct shaderCollider
			{
				Math::Matrix4 worldMatrix;
				Math::Vector3d scale;
				float radius;
			};

			class feBoundingSphere
			{
			public:
				feBoundingSphere();
				feBoundingSphere(float const& radius, Math::Vector3d pos);
				~feBoundingSphere();

				feBoundingSphere* Clone();

#pragma region Getter/Setter
				Object::feTransform& GetTransform();
				float GetRadius();
				void SetCenter(Math::Vector3d const& center);
				void SetRadius(float const& radius);
				void SetShader(feShader* const& shader);
#pragma endregion

				virtual shaderCollider CreateShaderStruct();

				void BindShader();
				void BindBuffer();

				void UnbindBuffer();
				void UnbindShader();
				void UpdateBufferObject();
				void Draw();
				
				float _radius;
			private:
				feBoundingSphere(feBoundingSphere const& copy);
				Object::feTransform _transform;

				feShader* _shader;
				feBuffer _buffer;
				feBufferObject _bObject;
			};
		
	} //namespace Physics
} //namespace FrogEngine