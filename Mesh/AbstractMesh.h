#pragma once

#include <vector>
#include "RHI/RHI.h"

namespace FrogEngine
{
	namespace Mesh
	{
		class feMesh;
		class feMeshSkybox;
	}

	class AbstractMesh
	{
	protected:
		virtual void LoadMesh(std::string const& name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& _center, float& _radius) = 0;
	};
}