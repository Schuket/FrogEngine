#ifdef MESH_EXPORTS
#define MESH_WRAPPER __declspec(dllexport) 
#else
#define MESH_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "feMesh.h"

namespace FrogEngine
{
	namespace Mesh
	{
		class feMeshSkybox : public feMesh
		{
		public:
			// Ctor / Dtor
			MESH_WRAPPER feMeshSkybox();
			MESH_WRAPPER feMeshSkybox(feVertices data, std::vector<std::string> faces);
			MESH_WRAPPER ~feMeshSkybox();

#pragma region Getters/Setters

			MESH_WRAPPER std::string GetName();
			MESH_WRAPPER void SetName(std::string const& name);

#pragma endregion
			// Functions
			MESH_WRAPPER virtual feMeshSkybox* Clone();
			MESH_WRAPPER virtual void Draw();
		private:
			// Ctor 
			feMeshSkybox(feMeshSkybox const& copy);

			// Functions
			void Init(feVertices data, std::vector<std::string> faces);

			// Variables
			std::string _name;
			feTexture _texture;
		};
	} // namespace Mesh
} // namespace Data