#include "FELoaderMesh.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "../feMeshSkybox.h"
#include "../feMeshObj.h"

#include "Math/Tools.h"
#include "Material/Material.h"
#include "Logger/Logger.h"

#include "../FBXSDK/SDKLoaderMesh.h"

namespace FrogEngine
{
	namespace FE
	{
		std::vector<Math::Vector3d> LoaderMesh::_vertices = {};
		std::vector<Math::Vector3d> LoaderMesh::_normales = {};
		std::vector<Math::Vector2d> LoaderMesh::_texCoord = {};

		feVertices LoaderMesh::_meshData = feVertices();

		void LoaderMesh::LoadMesh(std::string const& pathDirectory, std::string name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh[" + name + "] is loading. . .");
			std::string ext;
			Math::Tools::Split(name, ".", false, name, ext);
			name += "." + ext;

			if (ext == "obj")
				LoadMeshObj(pathDirectory, name, meshes, center, radius);
			else if (ext == "fbx")
				SDK::LoaderMesh::LoadScene(pathDirectory, name, meshes, center, radius);

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMesh[" + name + "] loaded !");
		}

		Mesh::feMeshSkybox* LoaderMesh::LoadSkybox(std::vector<std::string> faces)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox is loading. . .");

			_meshData.Clear();

			std::ifstream file;
			file.open("../Textures/Cube/Cube.obj", std::ios::binary);
			if (!file.good())
			{
				std::cout << "FAILED -> to load model[../Textures/Cube/Cube.obj]" << std::endl;
				return nullptr;
			}

			std::string nameMesh, nameMeshPrev;
			std::string mtlFileName;
			std::string mtlName;
			std::string line;
			std::string type;
			float x, y, z;

			while (std::getline(file, line))
			{
				if (line.size() > 0)
				{
					std::stringstream lineStream(line);
					lineStream >> type;

					if (type == "mtllib" && mtlFileName == "")
					{
						RecoverNameMtl(line, mtlFileName);
					}
					else if (type == "g")
					{
						lineStream >> nameMesh;
					}
					else if (type == "usemtl")
					{
						nameMeshPrev = nameMesh;

						lineStream >> mtlName;
					}
					else if (type == "v")
					{
						lineStream >> x >> y >> z;

						_vertices.push_back(Math::Vector3d(x, y, z));
					}
					else if (type == "vt")
					{
						lineStream >> x >> y;
						_texCoord.push_back(Math::Vector2d(x, -y));
					}
					else if (type == "vn")
					{
						lineStream >> x >> y >> z;
						_normales.push_back(Math::Vector3d(x, y, z));
					}
					else if (type == "f")
					{
						if (_normales.size() > 0)
							LoadFaceWithVn(lineStream);
						else
							LoadFaceWithoutVn(lineStream);
					}
				}
			}

			_vertices.clear();
			_normales.clear();
			_texCoord.clear();

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox loaded !");
			return new Mesh::feMeshSkybox(_meshData, faces);
		}

		void LoaderMesh::LoadMeshObj(std::string const& pathDirectory, std::string const& name, std::vector<Mesh::feMesh*>& meshes, Math::Vector3d& center, float& radius)
		{
			_meshData.Clear();

			std::ifstream file;
			file.open(pathDirectory + name, std::ios::binary);
			if (!file.good())
			{
				std::cout << "FAILED -> to load model[" << name << "]" << std::endl;
				return;
			}

			Math::Vector3d limitPlus;
			Math::Vector3d limitMinus;

			std::string nameMesh, nameMeshPrev;
			std::string mtlFileName;
			std::string mtlName;
			std::string line;
			std::string type;
			float x, y, z;

			while (std::getline(file, line))
			{
				if (line.size() > 0)
				{
					std::stringstream lineStream(line);
					lineStream >> type;

					if (type == "mtllib" && mtlFileName == "")
					{
						RecoverNameMtl(line, mtlFileName);
					}
					else if (type == "g")
					{
						lineStream >> nameMesh;
					}
					else if (type == "usemtl")
					{
						if (_meshData._positions.size() > 0)
						{
							meshes.push_back((Mesh::feMesh*)(new FrogEngine::Mesh::feMeshObj(nameMeshPrev, _meshData, LoaderMaterial::Load(mtlName, mtlFileName, pathDirectory))));

							nameMesh = "NoName";
							nameMeshPrev = "NoName";
							_meshData.Clear();
						}
						else
							nameMeshPrev = nameMesh;

						lineStream >> mtlName;
					}
					else if (type == "v")
					{
						lineStream >> x >> y >> z;

						CheckLimit(Math::Vector3d(x, y, z), limitPlus, limitMinus);

						_vertices.push_back(Math::Vector3d(x, y, z));
					}
					else if (type == "vt")
					{
						lineStream >> x >> y;
						_texCoord.push_back(Math::Vector2d(x, -y));
					}
					else if (type == "vn")
					{
						lineStream >> x >> y >> z;
						_normales.push_back(Math::Vector3d(x, y, z));
					}
					else if (type == "f")
					{
						if (_normales.size() > 0)
							LoadFaceWithVn(lineStream);
						else
							LoadFaceWithoutVn(lineStream);
					}
				}
			}

			if (_meshData._positions.size() > 0)
				meshes.push_back((Mesh::feMesh*)(new FrogEngine::Mesh::feMeshObj(nameMeshPrev, _meshData, LoaderMaterial::Load(mtlName, mtlFileName, pathDirectory))));

			_meshData.Clear();
			_vertices.clear();
			_normales.clear();
			_texCoord.clear();

			center.X((limitPlus.X() + limitMinus.X()) / 2.f);
			center.Y((limitPlus.Y() + limitMinus.Y()) / 2.f);
			center.Z((limitPlus.Z() + limitMinus.Z()) / 2.f);
			
			limitPlus.X((limitPlus.X() - limitMinus.X()) /2.f );
			limitPlus.Y((limitPlus.Y() - limitMinus.Y()) /2.f );
			limitPlus.Z((limitPlus.Z() - limitMinus.Z()) /2.f );

			radius = limitPlus.X();
			radius = limitPlus.Y() >= limitPlus.X() && limitPlus.Y() >= limitPlus.Z() ? limitPlus.Y() : radius;
			radius = limitPlus.Z() >= limitPlus.X() && limitPlus.Z() >= limitPlus.Y() ? limitPlus.Z() : radius;

			std::cout << "Model[" + name + "] Load !" << std::endl;
		}

		void LoaderMesh::RecoverNameMtl(std::string line, std::string& mtlFileName)
		{
			std::string res1;
			std::string res2;

			Math::Tools::Split(line, " ", true, res1, res2);

			mtlFileName = res2;

			if (mtlFileName.back() == '\0' || mtlFileName.back() == '\r' || mtlFileName.back() == ' ')
				mtlFileName.pop_back();
		}

		void LoaderMesh::LoadFaceWithVn(std::stringstream& lineStream)
		{
			std::vector<unsigned int> trVertices;
			std::vector<unsigned int> trTexCoord;
			std::vector<unsigned int> trNormales;

			std::string line;

			for (int count = 0; count < 3; ++count)
			{
				std::string idxVertices;
				std::string idxTexCoord;
				std::string idxNormales;

				lineStream >> line;

				Math::Tools::Split(line, "/", true, idxVertices, idxTexCoord);
				Math::Tools::Split(idxTexCoord, "/", false, idxTexCoord, idxNormales);

				trVertices.push_back(std::stoi(idxVertices));
				if (idxTexCoord != "")
					trTexCoord.push_back(std::stoi(idxTexCoord));
				trNormales.push_back(std::stoi(idxNormales));
			}

			for (int count = 0; count < 3; ++count)
			{
				_meshData._indices.push_back((uint16_t)_meshData._indices.size());

				_meshData.SetPositions(_vertices[trVertices[count] - 1]);
				_meshData.SetNormals(_normales[trNormales[count] - 1]);

				if (trTexCoord.size() > 0)
					_meshData.SetTexCoords(_texCoord[trTexCoord[count] - 1]);
			}
		}

		void LoaderMesh::LoadFaceWithoutVn(std::stringstream& lineStream)
		{
			std::vector<unsigned int> trVertices;
			std::vector<unsigned int> trTexCoord;

			std::string line;

			for (int count = 0; count < 3; ++count)
			{
				std::string idxVertices;
				std::string idxTexCoord;

				lineStream >> line;

				Math::Tools::Split(line, "/", true, idxVertices, idxTexCoord);

				trVertices.push_back(std::stoi(idxVertices));
				trTexCoord.push_back(std::stoi(idxTexCoord));
			}

			Math::Vector3d first = _vertices[trVertices[1] - 1] - _vertices[trVertices[0] - 1];
			Math::Vector3d second = _vertices[trVertices[2] - 1] - _vertices[trVertices[0] - 1];

			Math::Vector3d normal = first.Cross(second);

			for (int count = 0; count < 3; ++count)
			{
				_meshData._indices.push_back((uint16_t)_meshData._indices.size());
				_meshData.PushVertex(_vertices[trVertices[count] - 1], _texCoord[trTexCoord[count] - 1], normal);
			}
		}

		void LoaderMesh::CheckLimit(Math::Vector3d vertex, Math::Vector3d& limitPlus, Math::Vector3d& limitMinus)
		{
			if (vertex.X() > limitPlus.X())
				limitPlus.X(vertex.X());
			else if (vertex.X() < limitMinus.X())
				limitMinus.X(vertex.X());

			if (vertex.Y() > limitPlus.Y())
				limitPlus.Y(vertex.Y());
			else if (vertex.Y() < limitMinus.Y())
				limitMinus.Y(vertex.Y());

			if (vertex.Z() > limitPlus.Z())
				limitPlus.Z(vertex.Z());
			else if (vertex.Z() < limitMinus.Z())
				limitMinus.Z(vertex.Z());
		}
	} // namespace FE
} // namespace FrogEngine