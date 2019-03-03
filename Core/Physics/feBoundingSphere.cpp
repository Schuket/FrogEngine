#include "feBoundingSphere.h"

#include "Core\Object\feObject.h"
#include "RHI\Shader\GLShader.h"
#include "Logger\Logger.h"

namespace FrogEngine
{
	namespace Physics
	{
			feBoundingSphere::feBoundingSphere()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feBoundingSphere is creating. . .");
				_radius = 25.f;
				_shader = new feShader();
				_shader->Create("boundingsphere");

				
				feVertices data;
				data.PushVertex(Math::Vector3d(), Math::Vector2d(), Math::Vector3d());

				_buffer.Create(data);
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feBoundingSphere created !");
			}

			feBoundingSphere::feBoundingSphere(feBoundingSphere const& copy)
			{
				_transform.SetTranslation(copy._transform.GetLocalTranslation());
				_transform.SetScale(copy._transform.GetLocalScale());
				_transform.SetRotation(copy._transform.GetLocalRotation());

				_shader = copy._shader->Clone();
				_buffer = copy._buffer;
				_bObject = copy._bObject;
			}

			feBoundingSphere::feBoundingSphere(float const& radius, Math::Vector3d pos)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feBoundingSphere is creating. . .");
				_radius = radius;
				_transform.Translate(pos);
				_shader = new feShader();
				_shader->Create("boundingsphere");

				feVertices data;
				data.PushVertex(Math::Vector3d(), Math::Vector2d(), Math::Vector3d());

				_buffer.Create(data);
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feBoundingSphere created !");
			}

			feBoundingSphere::~feBoundingSphere()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feBoundingSphere is deleting. . .");
				delete _shader;

				_shader = nullptr;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feBoundingSphere deleted !");
			}

			feBoundingSphere* feBoundingSphere::Clone()
			{
				return new feBoundingSphere(*this);
			}

#pragma region Getter/Setter
			Object::feTransform& feBoundingSphere::GetTransform()
			{
				return _transform;
			}

			float feBoundingSphere::GetRadius()
			{
				return _radius;
			}

			void feBoundingSphere::SetCenter(Math::Vector3d const& center)
			{
				_transform.SetTranslation(center);
			}

			void feBoundingSphere::SetRadius(float const& radius)
			{
				_radius = radius;
			}

			void feBoundingSphere::SetShader(feShader* const& shader)
			{
				_shader = shader;
			}
#pragma endregion

			shaderCollider feBoundingSphere::CreateShaderStruct()
			{
				shaderCollider collider;

				collider.worldMatrix = _transform.GetWorldMatrix();
				collider.scale = _transform.GetScale();
				collider.radius = _radius;

				return collider;
			}

			void feBoundingSphere::UpdateBufferObject()
			{
				_bObject.Update(&CreateShaderStruct(), sizeof(CreateShaderStruct()), 4);
			}

			void feBoundingSphere::BindShader()
			{
				_shader->Bind();
			}

			void feBoundingSphere::BindBuffer()
			{
				_buffer.Bind();
			}

			void feBoundingSphere::UnbindBuffer()
			{
				_buffer.Unbind();
			}

			void feBoundingSphere::UnbindShader()
			{
				_shader->Unbind();
			}

			void feBoundingSphere::Draw()
			{
				UpdateBufferObject();
				feRenderer::Draw(1, TypeDraw::DRAW, TypePolygon::POINTS);
			}
	}
}