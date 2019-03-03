#include "feEditorCamera.h"

#include "../../System/feInputManager.h"

#include "../../Object/feObject.h"
#include "../feComponent.h"

namespace FrogEngine
{
	namespace Component
	{
		namespace Video
		{
			feEditorCamera::feEditorCamera(unsigned int width, unsigned int height)
				:feCamera(width, height)
			{
				_typeID = typeid(feEditorCamera).hash_code();
				_type = ComponentType::EditorCamera;
			}

			feEditorCamera::~feEditorCamera()
			{}

#pragma region Getter/Setter
			float feEditorCamera::GetMovementSpeed()
			{
				return _mvmtSpeed;
			}

			float feEditorCamera::GetRotationSpeed()
			{
				return _rotSpeed;
			}

			void feEditorCamera::SetMovementSpeed(float speed)
			{
				if (speed > 0.f)
					_mvmtSpeed = speed;
			}

			void feEditorCamera::SetRotationSpeed(float speed)
			{
				if (speed > 0.f)
					_rotSpeed;
			}
#pragma endregion
			void feEditorCamera::Init()
			{
				_owner->GetTransform().RotateDeg(180.f, Math::Vector3d::Up());
				_owner->GetTransform().Translate(Math::Vector3d(0.f, 0.f, 40.f));

				UpdateDirectionVector();

				_viewMatrix.LookAt(_owner->GetTransform().GetTranslation(), _owner->GetTransform().GetTranslation() + _forward, Math::Vector3d::Up());
				_viewMatrix.ConvertToMatView();
			}

			void feEditorCamera::UpdateDirectionVector()
			{
				Math::Matrix4 rotMat = Math::Quaternion::QuatToMat4(_owner->GetTransform().GetRotation());
				_forward = rotMat.GetForward();
				_up = rotMat.GetUp();
				_right = rotMat.GetRight();
			}

			void feEditorCamera::UpdateCameraMovement(float deltaTime)
			{
				LookAtViewMode();
				_frustum->ConstructPlanes(_projectionMatrix, _viewMatrix);
			}

			void feEditorCamera::LookAtViewMode()
			{
				if (_camMoved)
				{
					_owner->GetTransform().Translate(Math::Vector3d(_move));

					_viewMatrix.LookAt(_owner->GetTransform().GetTranslation(), _owner->GetTransform().GetTranslation() + _forward, Math::Vector3d::Up());
					_viewMatrix.ConvertToMatView();

					_move = Math::Vector3d(0.f, 0.f, 0.f);
					_camMoved = false;
				}
			}

			void feEditorCamera::StarshipViewMode()
			{
				if (_camMoved)
				{
					_owner->GetTransform().Translate(Math::Vector3d(_move));

					Math::Matrix4 rotMat = Math::Quaternion::QuatToMat4(_owner->GetTransform().GetRotation());
					Math::Matrix4 translationMat = Math::Matrix4::CreateMat4Translation(_owner->GetTransform().GetTranslation());

					_viewMatrix = rotMat * translationMat;

					_move = Math::Vector3d(0.f, 0.f, 0.f);
					_camMoved = false;
				}
			}

#pragma region HookEvent

			void feEditorCamera::HookBasicKeyInputController(System::feInputManager* inputMgr)
			{
				if (!inputMgr)
					return;

				inputMgr->_keyIsPressed_W.Bind<feEditorCamera, &feEditorCamera::W_InputControllerHandler>(this);
				inputMgr->_keyIsPressed_A.Bind<feEditorCamera, &feEditorCamera::A_InputControllerHandler>(this);
				inputMgr->_keyIsPressed_S.Bind<feEditorCamera, &feEditorCamera::S_InputControllerHandler>(this);
				inputMgr->_keyIsPressed_D.Bind<feEditorCamera, &feEditorCamera::D_InputControllerHandler>(this);			
			}
			void feEditorCamera::HookArrowInputController(System::feInputManager* inputMgr)
			{
				if (!inputMgr)
					return;

				inputMgr->_keyIsPressed_UpArrow.Bind<feEditorCamera, &feEditorCamera::ArrowUp_InputControllerHandler>(this);
				inputMgr->_keyIsPressed_LeftArrow.Bind<feEditorCamera, &feEditorCamera::ArrowLeft_InputControllerHandler>(this);
				inputMgr->_keyIsPressed_DownArrow.Bind<feEditorCamera, &feEditorCamera::ArrowDown_InputControllerHandler>(this);
				inputMgr->_keyIsPressed_RightArrow.Bind<feEditorCamera, &feEditorCamera::ArrowRight_InputControllerHandler>(this);
			}

			void feEditorCamera::UnhookBasicKeyInputController(System::feInputManager* inputMgr)
			{
				if (!inputMgr)
					return;

				inputMgr->_keyIsPressed_W.Unbind<feEditorCamera, &feEditorCamera::W_InputControllerHandler>();
				inputMgr->_keyIsPressed_A.Unbind<feEditorCamera, &feEditorCamera::A_InputControllerHandler>();
				inputMgr->_keyIsPressed_S.Unbind<feEditorCamera, &feEditorCamera::S_InputControllerHandler>();
				inputMgr->_keyIsPressed_D.Unbind<feEditorCamera, &feEditorCamera::D_InputControllerHandler>();
			}
			void feEditorCamera::UnhookArrowInputController(System::feInputManager* inputMgr)
			{
				if (!inputMgr)
					return;

				inputMgr->_keyIsPressed_UpArrow.Unbind<feEditorCamera, &feEditorCamera::ArrowUp_InputControllerHandler>();
				inputMgr->_keyIsPressed_LeftArrow.Unbind<feEditorCamera, &feEditorCamera::ArrowLeft_InputControllerHandler>();
				inputMgr->_keyIsPressed_DownArrow.Unbind<feEditorCamera, &feEditorCamera::ArrowDown_InputControllerHandler>();
				inputMgr->_keyIsPressed_RightArrow.Unbind<feEditorCamera, &feEditorCamera::ArrowRight_InputControllerHandler>();
			}
#pragma endregion

#pragma region EventFunction

			void feEditorCamera::W_InputControllerHandler(float deltaTime)
			{
				_move += (_forward * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feEditorCamera::S_InputControllerHandler(float deltaTime)
			{
				_move -= (_forward * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feEditorCamera::A_InputControllerHandler(float deltaTime)
			{
				_move -= (_right * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feEditorCamera::D_InputControllerHandler(float deltaTime)
			{
				_move += (_right * _mvmtSpeed * deltaTime);
				_camMoved = true;
			}

			void feEditorCamera::ArrowUp_InputControllerHandler(float deltaTime)
			{
				if (_forward.Y() > 0.999f)
					return;

				_owner->GetTransform().RotateDeg(_rotSpeed * deltaTime, _right);
				UpdateDirectionVector();
				_camMoved = true;
			}

			void feEditorCamera::ArrowLeft_InputControllerHandler(float deltaTime)
			{
				_owner->GetTransform().RotateDeg(_rotSpeed * deltaTime, Math::Vector3d::Up());

				UpdateDirectionVector();
				_camMoved = true;
			}

			void feEditorCamera::ArrowDown_InputControllerHandler(float deltaTime)
			{
				if (_forward.Y() < -0.999f)
					return;

				_owner->GetTransform().RotateDeg(-_rotSpeed * deltaTime, _right);
				UpdateDirectionVector();
				_camMoved = true;
			}

			void feEditorCamera::ArrowRight_InputControllerHandler(float deltaTime)
			{
				_owner->GetTransform().RotateDeg(-_rotSpeed * deltaTime, Math::Vector3d::Up());

				UpdateDirectionVector();
				_camMoved = true;
			}

#pragma endregion
		}
	}
}