#ifdef MESH_EXPORTS
#define MESH_WRAPPER __declspec(dllexport) 
#else
#define MESH_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "feMesh.h"

namespace FrogEngine
{
	class feMaterialFbx;

	namespace Mesh
	{
		class feMeshFbx : public feMesh
		{
		public:
			MESH_WRAPPER feMeshFbx(std::string const& name, feVertices vData, feMaterial* mtl);
			MESH_WRAPPER ~feMeshFbx();

			MESH_WRAPPER virtual feMeshFbx* Clone() override;
			MESH_WRAPPER virtual void Draw() override;
		private:
			feMeshFbx(feMeshFbx const& copy);

			void Init();
		};
	}
}