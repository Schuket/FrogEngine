#include "feCamera.h"

#include "Math\Tools.h"

#include "../../Object/feObject.h"
#include "Logger\Logger.h"

#define FOV (45.f * ((atan(1) * 4) / 180.f))

namespace FrogEngine 
{
	namespace Component 
	{
		namespace Video 
		{
			feCamera::feCamera()
				:feComponent()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera is creating. . .");

				_typeID = typeid(feCamera).hash_code();
				_type = ComponentType::Camera;
				
				_frustum = new System::Video::feFrustum();

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera created !");
			}

			feCamera::feCamera(feCamera const& copy)
				:feComponent(copy)
			{
				_width = copy._width;
				_height = copy._height;
				_near = copy._near;
				_far = copy._far;
				_fov = copy._fov;
				_projectionMatrix = copy._projectionMatrix;
				_viewMatrix = copy._viewMatrix;
				_bObject = copy._bObject;
				_frustum = copy._frustum->Clone();
				SetFrustum(_width, _height);
			}

			feCamera::feCamera(unsigned int width, unsigned int height)
				:feCamera()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera is creating. . .");
				SetFrustum(width, height);
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera created !");
			}
			
			feCamera::~feCamera()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera is deleting. . .");
				delete _frustum;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera deleted !");
			}

			void feCamera::Init(Object::feObject* node)
			{
				UpdateCameraMovement(0.f);
			}

			feCamera* feCamera::Clone()
			{
				return new feCamera(*this);
			}

			Math::Matrix4 feCamera::GetProjectionMatrix() const 
			{ 
				return _projectionMatrix; 
			}

			Math::Matrix4 feCamera::GetViewMatrix() const 
			{ 
				return _viewMatrix; 
			}

			unsigned int feCamera::GetHeight() 
			{ 
				return _height; 
			}

			unsigned int feCamera::GetWidth() 
			{ 
				return _width; 
			}

			float feCamera::GetNear() 
			{ 
				return _near; 
			}

			float feCamera::GetFar() 
			{ 
				return _far; 
			}

			float feCamera::GetFov() 
			{ 
				return _fov; 
			}

			void feCamera::SetFOV(float f)
			{
				_fov = f;
				Projection(_fov, (float)_width / (float)_height, _near, _far);
			}

			void feCamera::SetNear(float f)
			{
				_near = f;
				Projection(_fov, (float)_width / (float)_height, _near, _far);
			}

			void feCamera::SetFar(float f)
			{
				_far = f;
				Projection(_fov, (float)_width / (float)_height, _near, _far);
			}

			System::Video::feFrustum* feCamera::GetFrustum() const
			{
				return _frustum;
			}

			void feCamera::SetFrustum(unsigned int width, unsigned int height)
			{
				_width = width;
				_height = height;
				Math::Matrix4::CreateMat4Scale(Math::Vector3d());
				Projection((float)_fov, (float)_width / (float)_height, _near, _far);
				feRenderer::InitViewport(Math::Vector2d((float)_width, (float)_height));
			}

			void feCamera::UpdateBufferObject()
			{
				shaderCamera structCam = CreateShaderStruct();

				_bObject.Update(&structCam, sizeof(structCam), 1);
			}
			
			shaderCamera feCamera::CreateShaderStruct()
			{
				shaderCamera cam;

				cam.proj = _projectionMatrix;
				cam.view = _viewMatrix;

				return cam;
			}
			
			void feCamera::Projection(float fov, float aspectRatio, float nearest, float farthest)
			{
				_projectionMatrix = Math::Matrix4::CreateMat4Perspec(fov, aspectRatio, nearest, farthest);
				_frustum->SetDepth(farthest);
				_frustum->ConstructPlanes(_projectionMatrix, _viewMatrix);
			}

			void feCamera::UpdateCameraMovement(float deltaTime)
			{
				Math::Matrix4 rotMat = Math::Quaternion::QuatToMat4(_owner->GetTransform().GetRotation());
				Math::Vector3d forward = rotMat.GetForward();

				_viewMatrix.LookAt(_owner->GetTransform().GetTranslation(), _owner->GetTransform().GetTranslation() + (forward * -1.f), Math::Vector3d::Up());
				_viewMatrix.ConvertToMatView();

				_frustum->ConstructPlanes(_projectionMatrix, _viewMatrix);
			}
		} //namespace Video
	} //namespace Component
} //namespace FrogEngine