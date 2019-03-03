#include "feResourceManager.h"

#include "feScene.h"
#include "feSceneManager.h"

#include "Video\feDriver.h"

#include "../Object/feObject.h"
#include "..\Component\Mesh\feModel.h"

#include "Math\Tools.h"
#include "Mesh\Mesh.h"

#include "Logger\Logger.h"

namespace FrogEngine {
	namespace System {

		feResourceManager::feResourceManager(feSceneManager* scnMgr, Video::feDriver* drv)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feResourceManager is creating. . .");
			_scnMgr = scnMgr;
			_drv = drv;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feResourceManager created !");
		}

		feResourceManager::~feResourceManager()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feResourceManager is deleting. . .");
			//size_t nbr = _models.size();
			//for (int idx = 0; idx < nbr; ++idx)
			//	delete _models[idx];
			_models.clear();

			_scnMgr = nullptr;
			_drv = nullptr;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feResourceManager deleted !");
		}

		std::vector<FrogEngine::Component::Mesh::feModel*>& feResourceManager::GetModels()
		{
			return _models;
		}

		Component::feComponent* feResourceManager::LoadModel(std::string const& path)
		{
			std::string pathDirectory, name;
			Math::Tools::Split(path, "/", false, pathDirectory, name);
			pathDirectory += "/";

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel[" + name + "] is loading. . .");

			return LoadObj(pathDirectory, name);
		}

		Object::feObject* feResourceManager::LoadSkybox(std::string const& path)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Skybox[" + path + "] is loading. . .");
			Object::feObject* skybox = new Object::feObject();

			std::vector<feScene*> sceneArray = _scnMgr->GetScenes();
			int sceneIndex = _scnMgr->GetSceneIndex();

			std::vector<std::string> faces;
			faces.push_back(path + "right.jpg");
			faces.push_back(path + "left.jpg");
			faces.push_back(path + "top.jpg");
			faces.push_back(path + "bottom.jpg");
			faces.push_back(path + "back.jpg");
			faces.push_back(path + "front.jpg");
	
			Component::Mesh::feModel* model = new Component::Mesh::feModel(path);
			model->SetPath(path);

			FrogEngine::Mesh::feMeshSkybox* mesh = LoaderMesh::LoadSkybox(faces);

			feShader* shader = _drv->LoadShader("cubemap");

			mesh->SetShader(shader);
			mesh->SetName(path);

			model->GetMeshes()[shader].push_back(mesh);

			model->SetIdx((unsigned int const)_models.size());
			_models.push_back(model);

			skybox->AddComponent(model);

			sceneArray[sceneIndex]->SetSkybox(skybox);

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Skybox[" + path + "] loaded !");
			return skybox;
		}

		void feResourceManager::UseMemoryMask(bool status)
		{
			if (status == _useMemoryMask)
				return;
			_useMemoryMask = status;
		}

		Component::feComponent* feResourceManager::CreateMesh(std::string pathDirectory, std::string name)
		{
			std::string ext;
			Math::Tools::Split(name, ".", false, name, ext);
			name += "." + ext;

			Component::Mesh::feModel* model = new Component::Mesh::feModel(name + " Model Component");

			model->SetPath(pathDirectory + name);

			std::vector<FrogEngine::Mesh::feMesh*> meshes;

			Math::Vector3d center;
			float radius = 0.f;

			LoaderMesh::LoadMesh(pathDirectory, name, meshes, center, radius);

			model->SetCenter(center);
			model->SetRadius(radius);

			feShader* shader;
			
			if (ext == "fbx") 
				shader = _drv->LoadShader("basicFBX");
			else
				shader = _drv->LoadShader("basic");

			for (int idx = 0; idx < meshes.size(); ++idx)
			{
				meshes[idx]->SetShader(shader);
				model->GetMeshes()[shader].push_back(meshes[idx]);
			}

			model->SetIdx((const unsigned int)_models.size());
			_models.push_back(model);

			return model;
		}

		Component::feComponent* feResourceManager::LoadObj(std::string const& pathDirectory, std::string const& name)
		{
			Component::feComponent* obj = nullptr;

			if (_useMemoryMask)
				obj = CheckMemoryMask(name);

			if (!obj)
				obj = CreateMesh(pathDirectory, name);

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel[" + name + "] loaded !");

			return obj;
		}

		Component::feComponent* feResourceManager::CheckMemoryMask(std::string name)
		{
			size_t size = _models.size();
			for (int idx = 0; idx < size; ++idx)
				if (_models[idx]->GetName().compare(name) == 0)
					return _models[idx];

			return nullptr;
		}
	} //namespace System
} //FrogEngine