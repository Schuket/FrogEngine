#ifdef MESH_EXPORTS
#define MESH_WRAPPER __declspec(dllexport) 
#else
#define MESH_WRAPPER __declspec(dllimport) 
#endif

#pragma once

#include "../AbstractMesh.h"

namespace FrogEngine
{
	namespace FE
	{
		class LoaderMesh : public AbstractMesh
		{	
		public:
			MESH_WRAPPER static void LoadMesh(std::string const& pathDirectory, std::string name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius);
			MESH_WRAPPER static Mesh::feMeshSkybox* LoadSkybox(std::vector<std::string> faces);
		private:
			static void LoadMeshObj(std::string const& pathDirectory, std::string const& name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius);
			static void RecoverNameMtl(std::string line, std::string& mtlFileName);
			static void LoadFaceWithVn(std::stringstream& lineStream);
			static void LoadFaceWithoutVn(std::stringstream& lineStream);
			static void CheckLimit(Math::Vector3d vertex, Math::Vector3d& limitPlus, Math::Vector3d& limitMinus);

			static std::vector<Math::Vector3d> _vertices;
			static std::vector<Math::Vector3d> _normales;
			static std::vector<Math::Vector2d> _texCoord;

			static feVertices _meshData;
		};
	} // namespace FE
} // namespace FrogEngine