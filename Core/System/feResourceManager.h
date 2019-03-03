#ifdef CORE_EXPORTS
#define RESSOURCEMANAGER_WRAPPER __declspec(dllexport)
#else
#define RESSOURCEMANAGER_WRAPPER __declspec(dllimport)
#endif

#pragma once

#include <string>
#include <vector>

namespace FrogEngine 
{
	namespace Component
	{
		class feComponent;

		namespace Mesh
		{
			class feModel;
		} // namespace Data
	} // namespace Component

	namespace Mesh
	{
		class feMeshSkybox;
	} // namespace Mesh

	namespace Object
	{
		class feObject;
	} // namespace Object

	namespace System 
	{
		class feSceneManager;

		namespace Video 
		{
			class feDriver;
		} // namespace video
		
		enum ResourceType
		{
			None = 0,
			Obj,
			Fbx,
		};

		class feResourceManager
		{
		public:
			// Ctor / Dtor
			feResourceManager() = delete;
			feResourceManager(feSceneManager* scnMgr, Video::feDriver* drv);
			~feResourceManager();

			// Getter / Setter
			std::vector<FrogEngine::Component::Mesh::feModel*>& GetModels();

			// Functions
			/* Load a model (.obj, .fbx)
			* path : The path towards a model file with the extension .obj or .fbx
			*/
			RESSOURCEMANAGER_WRAPPER Component::feComponent* LoadModel(std::string const& path);
			/* Load a skybox for the current scene (.obj)
			The pictures, for the all side of the cube, must have a name like : 
			"right.jpg"
			"left.jpg"
			"top.jpg"
			"bottom.jpg"
			"back.jpg"
			"front.jpg"
			* path : The path towards a model folder
			*/
			RESSOURCEMANAGER_WRAPPER Object::feObject* LoadSkybox(std::string const& path);
			void UseMemoryMask(bool status);
		private:
			// Functions
			Component::feComponent* LoadObj(std::string const& pathDirectory, std::string const& name);
			Component::feComponent* CheckMemoryMask(std::string name);
			Component::feComponent* CreateMesh(std::string pathDirectory, std::string name);

			// Variables
			bool _useMemoryMask = true;

			feSceneManager* _scnMgr;
			Video::feDriver* _drv;

			std::vector<FrogEngine::Component::Mesh::feModel*> _models;
		};
	} // namespace System
} // namespace FrogEngine