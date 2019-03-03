#ifdef MESH_EXPORTS
#define MESH_WRAPPER __declspec(dllexport) 
#else
#define MESH_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "RHI/RHI.h"

namespace FrogEngine
{
	class feMaterial;

	namespace Mesh
	{
		class feMesh
		{
		public:
			// Ctor / Dtor
			MESH_WRAPPER feMesh();
			MESH_WRAPPER ~feMesh();

			// Functions
#pragma region Getters/Setters
			MESH_WRAPPER feMaterial* GetMtl();
			MESH_WRAPPER feBuffer& GetBuffer();
			MESH_WRAPPER feShader* GetShader();

			MESH_WRAPPER void SetShader(feShader* shader);
			MESH_WRAPPER void SetName(std::string const& name);
#pragma endregion
			MESH_WRAPPER virtual feMesh* Clone() = 0;
			MESH_WRAPPER virtual void Draw() = 0;

		protected:
			// Ctor 
			feMesh(feMesh const& copy);

			// Variables
			feVertices _vData;
			feBuffer _buffer;

			feMaterial* _material;
			feShader* _shader;

			std::string _name;
		};
	} // namespace Mesh
} // namespace Data