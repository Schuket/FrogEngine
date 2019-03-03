#pragma once

#define FBXSDK_SHARED
#include "fbxsdk.h"

#ifdef FBXSDK_SHARED
#pragma comment(lib, "libfbxsdk.lib")
#else
#pragma comment(lib, "libfbxsdk-md.lib")
#endif

#include <string>
#include <vector>
#include "Math\Vector3d.h"

namespace FrogEngine
{
	namespace Mesh
	{
		class feMesh;
	}

	namespace SDK
	{
		class LoaderMesh
		{
		public:
			static void LoadScene(std::string const& pathDirectory, std::string const& name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius);
			static void ProcessNode(const FbxNode* node, const FbxNode* parent, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius);
			static void LoadMesh(const FbxNode* node, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius);
			static void CheckLimit(Math::Vector3d vertex, Math::Vector3d& limitPlus, Math::Vector3d& limitMinus);
		};
	}
}