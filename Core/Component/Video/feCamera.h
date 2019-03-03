#ifdef CORE_EXPORTS
#define CAMERA_WRAPPER __declspec(dllexport)
#else
#define CAMERA_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include "../feComponent.h"

#include <vector>

#include "Math\Vector3d.h"
#include "Math\Vector2d.h"
#include "Math\Matrix4.h"

#include "RHI/RHI.h"
#include "WindowEvent/WindowEvent.h"
#include "../../System/Video/feFrustum.h"

namespace FrogEngine 
{
	namespace Object
	{
		class feTransform;
	} // namespace Object

	namespace System
	{
		class feInputManager;
	} // namespace System

	namespace Component
	{
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

			class feCamera : public Component::feComponent
			{
			public:
				// Ctor / Dtor
				//Create Camera
				CAMERA_WRAPPER feCamera();
				//Create copy Camera
				CAMERA_WRAPPER feCamera(feCamera const& copy);
				//Create Camera with a specific size 
				CAMERA_WRAPPER feCamera(unsigned int width, unsigned int height);
				virtual ~feCamera();
				
				void Init(Object::feObject* node);
				feCamera* Clone();

				// Functions
				#pragma region Getter/Setter
					Math::Matrix4 GetProjectionMatrix() const;
					Math::Matrix4 GetViewMatrix() const;

					unsigned int GetHeight();
					unsigned int GetWidth();
					// Return the near
					CAMERA_WRAPPER float GetNear();
					// Return the far
					CAMERA_WRAPPER float GetFar();
					// Return the fov
					CAMERA_WRAPPER float GetFov();

					/* Set the fov (field of view)
					* f : the new FOV
					*/
					CAMERA_WRAPPER void SetFOV(float f);
					/* Set the near
					* f : the new near
					*/
					CAMERA_WRAPPER void SetNear(float f);
					/* Set the far
					* f : the new far
					*/
					CAMERA_WRAPPER void SetFar(float f);
					System::Video::feFrustum* GetFrustum() const;

					/* Set the projection and initialize the viewport
					
					*/
					CAMERA_WRAPPER void SetFrustum(unsigned int width, unsigned int height);
				#pragma endregion

				virtual void UpdateCameraMovement(float deltaTime);

				void UpdateBufferObject();
			
				template <class Archive>
				void Save(Archive & ar) const;

			protected:
				// Functions
				shaderCamera CreateShaderStruct();
				void Projection(float fov, float aspectRatio, float nearest, float farthest);

				// Variables
				unsigned int _width = 800;
				unsigned int _height = 800;
				float _near = 0.1f;
				float _far = 1000.f;
				float _fov = (45.f * ((atan(1.f) * 4.f) / 180.f));

				Math::Matrix4 _projectionMatrix;
				Math::Matrix4 _viewMatrix;

				feBufferObject _bObject;
				System::Video::feFrustum* _frustum;
			};
		} //namesapace Video
	} //namespace Component
} //namespace FrogEngine

#include "feCamera.inl"