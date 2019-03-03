#include "feCamera.h"

#include "Math\Tools.h"

#include "../feInputManager.h"

#include "Logger\Logger.h"

#define FOV (45.f * ((atan(1) * 4) / 180.f))

namespace FrogEngine 
{
	namespace System 
	{
		namespace Video 
		{
			feCamera::feCamera()
				: feObject()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera is creating. . .");

				_frustum = new feFrustum();
				SetName("Main Camera");
				_transform.SetOwner(this);
				_transform.RotateDeg(180.f, Math::Vector3d::Up());

				UpdateDirectionVector();

				LookAt(_transform.GetTranslation(), _transform.GetTranslation() + _forward, Math::Vector3d::Up());

				shaderCamera shaderStruct = CreateShaderStruct();
				_bObject.Init(&shaderStruct, sizeof(shaderStruct));

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feCamera created !");
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

			float feCamera::GetMovementSpeed()
			{
				return _mvmtSpeed;
			}

			float feCamera::GetRotationSpeed()
			{
				return _rotSpeed;
			}

			feFrustum* feCamera::GetFrustum() const
			{
				return _frustum;
			}

			void feCamera::SetMovementSpeed(float speed)
			{
				if (speed > 0.f)
					_mvmtSpeed = speed;
			}

			void feCamera::SetRotationSpeed(float speed)
			{
				if (speed > 0.f)
					_rotSpeed;
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
				LookAtViewMode();
				_frustum->ConstructPlanes(_projectionMatrix, _viewMatrix);
			}

			void feCamera::LookAtViewMode()
			{
				if (_camMoved)
				{
					_transform.Translate(Math::Vector3d(_move));

					LookAt(_transform.GetTranslation(), _transform.GetTranslation() + _forward, Math::Vector3d::Up());
				
					_move = Math::Vector3d(0.f, 0.f, 0.f);
					_camMoved = false;
				}
			}

			void feCamera::StarshipViewMode()
			{
				if (_camMoved)
				{
					_transform.Translate(Math::Vector3d(_move));

					Math::Matrix4 rotMat = Math::Quaternion::QuatToMat4(_transform.GetRotation());
					Math::Matrix4 translationMat = Math::Matrix4::CreateMat4Translation(_transform.GetTranslation());

					_viewMatrix = rotMat * translationMat;

					_move = Math::Vector3d(0.f, 0.f, 0.f);
					_camMoved = false;
				}
			}

			void feCamera::UpdateDirectionVector()
			{
				Math::Matrix4 rotMat = Math::Quaternion::QuatToMat4(_transform.GetRotation());
				_forward = rotMat.GetForward();
				_up = rotMat.GetUp();
				_right = rotMat.GetRight();
			}

			Math::Matrix4 feCamera::LookAt(Math::Vector3d eye, Math::Vector3d target, Math::Vector3d up)
			{
				Math::Vector3d zAxis = eye - target;
				zAxis.Normalized();
				Math::Vector3d xAxis = zAxis.Cross(up);
				xAxis.Normalized();
				Math::Vector3d yAxis = xAxis.Cross(zAxis);

				float orientationData[16] = { 
					xAxis.X(), yAxis.X(), zAxis.X(), 0.0f,
					xAxis.Y(), yAxis.Y(), zAxis.Y(), 0.0f,
					xAxis.Z(), yAxis.Z(), zAxis.Z(), 0.0f,
					-xAxis.Dot(eye), -yAxis.Dot(eye), -zAxis.Dot(eye), 1.f };

				_viewMatrix = Math::Matrix4(orientationData);

				return (_viewMatrix);
			}

#pragma region HookEvent

			void feCamera::HookBasicKeyInputController(feInputManager* classPtr)
			{
				__hook (&System::feInputManager::KeyboardPressing_W, classPtr, &feCamera::W_InputControllerHandler);
				__hook (&System::feInputManager::KeyboardPressing_S, classPtr, &feCamera::S_InputControllerHandler);
				__hook (&System::feInputManager::KeyboardPressing_A, classPtr, &feCamera::A_InputControllerHandler);
				__hook (&System::feInputManager::KeyboardPressing_D, classPtr, &feCamera::D_InputControllerHandler);
			}
			void feCamera::HookArrowInputController(feInputManager* classPtr)
			{
				__hook (&System::feInputManager::KeyboardPressing_ArrowUp, classPtr, &feCamera::ArrowUp_InputControllerHandler);
				__hook (&System::feInputManager::KeyboardPressing_ArrowLeft, classPtr, &feCamera::ArrowLeft_InputControllerHandler);
				__hook (&System::feInputManager::KeyboardPressing_ArrowDown, classPtr, &feCamera::ArrowDown_InputControllerHandler);
				__hook (&System::feInputManager::KeyboardPressing_ArrowRight, classPtr, &feCamera::ArrowRight_InputControllerHandler);
			}
			
			void feCamera::UnhookBasicKeyInputController(feInputManager* classPtr)
			{
				__unhook (&System::feInputManager::KeyboardPressing_W, classPtr, &feCamera::W_InputControllerHandler);
				__unhook (&System::feInputManager::KeyboardPressing_S, classPtr, &feCamera::S_InputControllerHandler);
				__unhook (&System::feInputManager::KeyboardPressing_A, classPtr, &feCamera::A_InputControllerHandler);
				__unhook (&System::feInputManager::KeyboardPressing_D, classPtr, &feCamera::D_InputControllerHandler);
			}
			void feCamera::UnhookArrowInputController(feInputManager* classPtr)
			{
				__unhook (&System::feInputManager::KeyboardPressing_ArrowUp, classPtr, &feCamera::ArrowUp_InputControllerHandler);
				__unhook (&System::feInputManager::KeyboardPressing_ArrowLeft, classPtr, &feCamera::ArrowLeft_InputControllerHandler);
				__unhook (&System::feInputManager::KeyboardPressing_ArrowDown, classPtr, &feCamera::ArrowDown_InputControllerHandler);
				__unhook (&System::feInputManager::KeyboardPressing_ArrowRight, classPtr, &feCamera::ArrowRight_InputControllerHandler);
			}
#pragma endregion

#pragma region EventFunction

			void feCamera::W_InputControllerHandler(float deltaTime)
			{
				_move += (_forward * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feCamera::S_InputControllerHandler(float deltaTime)
			{
				_move -= (_forward * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feCamera::A_InputControllerHandler(float deltaTime)
			{
				_move -= (_right * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feCamera::D_InputControllerHandler(float deltaTime)
			{
				_move += (_right * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}
			
			void feCamera::ArrowUp_InputControllerHandler(float deltaTime)
			{
				if (_forward.Y() > 0.999f)
					return;

				_transform.RotateDeg(_rotSpeed * deltaTime, _right);
				UpdateDirectionVector();
				_camMoved = true;
			}

			void feCamera::ArrowLeft_InputControllerHandler(float deltaTime)
			{
				_transform.RotateDeg(_rotSpeed * deltaTime, Math::Vector3d::Up());

				UpdateDirectionVector();
				_camMoved = true;
			}

			void feCamera::ArrowDown_InputControllerHandler(float deltaTime)
			{
				if (_forward.Y() < -0.999f)
					return;

				_transform.RotateDeg(-_rotSpeed * deltaTime, _right);
				UpdateDirectionVector();
				_camMoved = true;
			}

			void feCamera::ArrowRight_InputControllerHandler(float deltaTime)
			{
				_transform.RotateDeg(-_rotSpeed * deltaTime, Math::Vector3d::Up());

				UpdateDirectionVector();
				_camMoved = true;
			}

#pragma endregion
			
		} //namespace Video
	} //namespace System
} //namespace FrogEngine