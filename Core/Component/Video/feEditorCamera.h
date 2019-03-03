#pragma once

#include "feCamera.h"

namespace FrogEngine
{
	namespace System
	{
		class feInputManager;
	} // namespace System

	namespace Component
	{
		namespace Video
		{
			enum class ViewMode
			{
				LookAtView = 0,
				StarshipView = 1,
			};

			class feEditorCamera: public feCamera
			{
			public:
				feEditorCamera(unsigned int width, unsigned int height);
				~feEditorCamera();

				void Init(Object::feObject* node) {};

#pragma region Getter/Setter
				float GetMovementSpeed();
				float GetRotationSpeed();

				void SetMovementSpeed(float speed);
				void SetRotationSpeed(float speed);
#pragma endregion
#pragma region HookEvent
				void HookBasicKeyInputController(System::feInputManager* classPtr);
				void HookArrowInputController(System::feInputManager* classPtr);
				void UnhookBasicKeyInputController(System::feInputManager* classPtr);
				void UnhookArrowInputController(System::feInputManager* classPtr);
#pragma endregion

				void Init();
				void UpdateCameraMovement(float deltaTime);

			private:
				void LookAtViewMode();
				void StarshipViewMode();
				void UpdateDirectionVector();

				Math::Vector3d _forward;
				Math::Vector3d _right;
				Math::Vector3d _up;

				float _mvmtSpeed = 10.f;
				float _rotSpeed = 75.f;

				bool _camMoved = false;
				Math::Vector3d _move;

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
			};
		}
	}
}