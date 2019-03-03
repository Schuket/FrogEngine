#include "feModel.h"

#include "Core/Object/feObject.h"
#include "Core/Physics/feboundingsphere.h"
#include "Core/System/feSerializeManager.h"

#include "Material/feMaterial.h"
#include "Mesh/Mesh.h"

#include "Logger\Logger.h"


namespace FrogEngine
{
	namespace Component
	{
		namespace Mesh
		{
			feModel::feModel()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel is creating. . .");
				_name = "Unamed Model";
				_type = Component::ComponentType::Mesh;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel created !");
			}

			feModel::feModel(std::string const& name)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel is creating. . .");
				_name = name;
				_typeID = typeid(feModel).hash_code();
				_type = ComponentType::Mesh;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel created !");
			}

			feModel::~feModel()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel is deleting. . .");

				std::map<feShader*, std::vector<FrogEngine::Mesh::feMesh*>>::iterator it = _meshes.begin();
				for (; it != _meshes.end(); it++)
				{
					for (int idx = 0; idx < it->second.size(); idx++)
					{
						delete it->second[idx];
					}
					it->second.clear();
				}
				_meshes.clear();
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel deleted !");
			}

			feModel::feModel(feModel const& copy)
				:feComponent(copy)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel is copying. . .");
				_name = copy._name;
				_path = copy._path;
				_meshes = copy._meshes;
				_radius = copy._radius;
				_center = copy._center;
				_idx = copy._idx;

				std::map<feShader*, std::vector<FrogEngine::Mesh::feMesh*>>::iterator it = _meshes.begin();

				for (; it != _meshes.end(); it++)
					for (int idx = 0; idx < it->second.size(); idx++)
						it->second[idx] = it->second[idx]->Clone();

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feModel copied !");
			}

			void feModel::Init(Object::feObject* node)
			{
				if (!node)
					return;

				node->GetCollider()->SetCenter(_center);
				node->GetCollider()->SetRadius(_radius);
				node->UpdateWorldPos();
				node->GetCollider()->UpdateBufferObject();
			}

			feModel* feModel::Clone()
			{
				return new feModel(*this);
			}

			std::string feModel::GetPath()
			{
				return _path;
			}

			unsigned int feModel::GetIdx() const
			{
				return _idx;
			}

			void feModel::SetIdx(unsigned int const& idx)
			{
				_idx = idx;
			}

			void feModel::SetPath(std::string const& path)
			{
				_path = path;
			}
			
			std::string feModel::GetName() const 
			{
				return _name;
			}
			
			Math::Vector3d feModel::GetCenter() const 
			{
				return _center; 
			}

			float feModel::GetRadius() const 
			{
				return _radius; 
			}

			void feModel::SetName(std::string newName) 
			{
				_name = newName; 
			}

			void feModel::SetCenter(Math::Vector3d const& center) 
			{
				_center = center;
			}
			
			void feModel::SetRadius(float const& radius) 
			{
				_radius = radius; 
			}

			template <class Archive>
			void feModel::Save(Archive & ar) const
			{
				std::string type = "feModel";

				ar(CEREAL_NVP(type));
				ar(CEREAL_NVP(_path));
			}

			template MODEL_WRAPPER void feModel::Save(cereal::XMLOutputArchive& ar) const;

			template <class Archive>
			void feModel::Load(Archive & ar)
			{
				std::string path;

				ar(cereal::make_nvp("_path", path));
				_path = path;
			}

			template MODEL_WRAPPER void feModel::Load(cereal::XMLInputArchive& ar);
		} //namespace Mesh
	} // namespace Component
} // namespace FrogEngine