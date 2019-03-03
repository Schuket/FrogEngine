#ifdef MESH_EXPORTS
#define MESH_WRAPPER __declspec(dllexport) 
#else
#define MESH_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "feMesh.h"

namespace FrogEngine
{
	class feMaterial;

	namespace Mesh
	{
		class feMeshObj : public feMesh
		{
		public:
			// Ctor / Dtor
			MESH_WRAPPER feMeshObj(std::string const& name, feVertices Data, feMaterial* mtl = nullptr);
			MESH_WRAPPER ~feMeshObj();

			// Functions
			MESH_WRAPPER virtual feMeshObj* Clone() override;
			MESH_WRAPPER virtual void Draw() override;

		private:
			// Ctor
			feMeshObj(feMeshObj const& copy);

			// Functions
			void Init();
		};
	} // namespace Mesh
} // namespace Data