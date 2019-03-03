#ifdef CORE_EXPORTS
#define MODEL_WRAPPER __declspec(dllexport)
#else
#define MODEL_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <string>
#include <map>
#include <vector>

#include "RHI/RHI.h"

#include "../feComponent.h"

namespace FrogEngine
{
	class feMaterial;

	namespace Mesh
	{
		class feMesh;
	} // namespace Mesh

	namespace Component
	{
		namespace Mesh
		{
			class feModel : public feComponent
			{
			public:
				// Ctor / Dtor
				// Create Model
				MODEL_WRAPPER feModel();
				// Create a model with a specific name
				MODEL_WRAPPER feModel(std::string const& name);
				// Create a copy model
				MODEL_WRAPPER feModel(feModel const& copy);
				~feModel();

				/* Init the feModel when he is attaching with an object
				* node : the object who has the feModel
				*/
				MODEL_WRAPPER void Init(Object::feObject* node);

				// Clone this feModel
				MODEL_WRAPPER feModel* Clone();

				// Functions
#pragma region Getters / Setter
				// Return the name
				MODEL_WRAPPER std::string GetName() const;
				// Return all meshes
				MODEL_WRAPPER std::map<feShader*, std::vector<FrogEngine::Mesh::feMesh*>>& GetMeshes() { return _meshes; }
				// Return the center
				MODEL_WRAPPER Math::Vector3d GetCenter() const;
				// Return the radius
				MODEL_WRAPPER float GetRadius() const;
				// Return the path of the files
				MODEL_WRAPPER std::string GetPath();
				// Return the index
				MODEL_WRAPPER unsigned int GetIdx() const;

				/* Set the name
				* newName : the new name
				*/
				MODEL_WRAPPER void SetName(std::string newName);
				/* Set the center
				* center : the new center
				*/
				MODEL_WRAPPER void SetCenter(Math::Vector3d const& center);
				/* Set the radius
				* radius : the new radius
				*/
				MODEL_WRAPPER void SetRadius(float const& radius);
				/* Set the index
				* idx : the new index
				*/
				MODEL_WRAPPER void SetIdx(unsigned int const& idx);
				/* Set the path
				* path : the new path
				*/
				MODEL_WRAPPER void SetPath(std::string const& path);
#pragma endregion

				template <class Archive>
				void Save(Archive & ar) const;

				template <class Archive>
				void Load(Archive & ar);

			private:

				// Variables
				std::map<feShader*, std::vector<FrogEngine::Mesh::feMesh*>> _meshes;

				Math::Vector3d _center;
				float _radius;

				unsigned int _idx;

				std::string _path;
				std::string _name;
			};
		} // namespace Mesh
	} // namespace Component
} // namespace FrogEngine