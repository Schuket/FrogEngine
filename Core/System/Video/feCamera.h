#ifdef CAMERA_EXPORTS
#define CAMERA_WRAPPER __declspec(dllexport)
#else
#define CAMERA_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "../../Object/feObject.h"

#include "Math\Vector3d.h"
#include "Math\Vector2d.h"
#include "Math\Matrix4.h"

#include "RHI/RHI.h"
#include "WindowEvent/WindowEvent.h"
#include "feFrustum.h"

namespace FrogEngine 
{
	namespace Object
	{
		class feTransform;
	} // namespace Object

	namespace System 
	{
		class feInputManager;

		namespace Video 
		{

			struct shaderCamera
			{
				Math::Matrix4 proj;
				Math::Matrix4 view;
			};

			enum PolygoneMode 
			{
				Fill = 0,
				Line,
				Point
			};

			enum class ViewMode 
			{
				LookAtView = 0,
				StarshipView = 1,
			};

			[event_receiver(native)]
			class feCamera : public Object::feObject
			{
			public:
				// Ctor / Dtor
				feCamera();
				feCamera(unsigned int width, unsigned int height);
				~feCamera();
				
				// Functions
				#pragma region Getter/Setter
					Math::Matrix4 GetProjectionMatrix() const;
					Math::Matrix4 GetViewMatrix() const;

					CAMERA_WRAPPER unsigned int GetHeight();
					CAMERA_WRAPPER unsigned int GetWidth();
					CAMERA_WRAPPER float GetNear();
					CAMERA_WRAPPER float GetFar();
					CAMERA_WRAPPER float GetFov();
					CAMERA_WRAPPER float GetMovementSpeed();
					CAMERA_WRAPPER float GetRotationSpeed();
					CAMERA_WRAPPER feFrustum* GetFrustum() const;

					CAMERA_WRAPPER void SetMovementSpeed(float speed);
					CAMERA_WRAPPER void SetRotationSpeed(float speed);
					CAMERA_WRAPPER void SetFrustum(unsigned int width, unsigned int height);
				#pragma endregion
				
				Math::Matrix4 LookAt(Math::Vector3d eye, Math::Vector3d target, Math::Vector3d up);

				void HookBasicKeyInputController(feInputManager* classPtr);
				void HookArrowInputController(feInputManager* classPtr);
				void UnhookBasicKeyInputController(feInputManager* classPtr);
				void UnhookArrowInputController(feInputManager* classPtr);

				void UpdateCameraMovement(float deltaTime);
				void UpdateBufferObject();
			
			private:
				// Functions
				shaderCamera CreateShaderStruct();
				void Projection(float fov, float aspectRatio, float nearest, float farthest);
				
				void UpdateDirectionVector();
				void LookAtViewMode();
				void StarshipViewMode();
				
				#pragma region EventHandler

				void W_InputControllerHandler(float DeltaTime);
				void S_InputControllerHandler(float DeltaTime);
				void A_InputControllerHandler(float DeltaTime);
				void D_InputControllerHandler(float DeltaTime);

				void ArrowUp_InputControllerHandler(float DeltaTime);
				void ArrowLeft_InputControllerHandler(float DeltaTime);
				void ArrowDown_InputControllerHandler(float DeltaTime);
				void ArrowRight_InputControllerHandler(float DeltaTime);

				#pragma endregion

				// Variables
				unsigned int _width = 800;
				unsigned int _height = 800;
				float _near = 0.1f;
				float _far = 1000.f;
				float _fov = (45.f * ((atan(1.f) * 4.f) / 180.f));

				float _mvmtSpeed = 10.f;
				float _rotSpeed = 75.f;

				Math::Matrix4 _projectionMatrix;
				Math::Matrix4 _viewMatrix;

				bool _camMoved = false;
				Math::Vector3d _move;

				Math::Vector3d _forward;
				Math::Vector3d _right;
				Math::Vector3d _up;

				feBufferObject _bObject;
				feFrustum* _frustum;
			};

		} //namesapace Video
	} //namespace System
} //namespace FrogEngine