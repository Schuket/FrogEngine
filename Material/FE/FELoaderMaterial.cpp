#include "FELoaderMaterial.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include <vector>

#include "..\feMaterial.h"

#include "Math\Tools.h"
#include "Image/Image.h"
#include "Logger/Logger.h"

using namespace std::experimental::filesystem::v1;

namespace FrogEngine
{
	namespace FE
	{
		FrogEngine::feMaterial* LoaderMaterial::Load(std::string const& name, std::string const& fileName, std::string const& pathDirectory)
		{

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial[" + name + "] is loading. . .");
			FrogEngine::feMaterial* mtl = new FrogEngine::feMaterial();
			
			mtl->_pathDirectory = pathDirectory;

			std::ifstream file;
			file.open(FindFile(pathDirectory, fileName), std::ios::binary);

			if (!file.good())
			{
				mtl->_mapKd = "White.png";
				LoadPng("../Textures/", mtl);

				return mtl;
			}

			std::string line;
			std::string type;
			std::string curName;

			float x, y, z;

			while (std::getline(file, line))
			{
				if (line.size() > 0)
				{
					std::stringstream lineStream(line);
					lineStream >> type;

					if (type == "newmtl")
						lineStream >> curName;

					if (curName == name)
					{
						if (type == "Ns")
							lineStream >> mtl->_ns;
						else if (type == "Ni")
							lineStream >> mtl->_ni;
						else if (type == "d")
							lineStream >> mtl->_d;
						else if (type == "Tr")
							lineStream >> mtl->_tr;
						else if (type == "Tf")
						{
							lineStream >> x >> y >> z;
							mtl->_tf = Vector3d(x, y, z);
						}
						else if (type == "illum")
							lineStream >> mtl->_illum;
						else if (type == "Ka")
						{
							lineStream >> x >> y >> z;
							mtl->_ka = Vector3d(x, y, z);
						}
						else if (type == "Kd")
						{
							lineStream >> x >> y >> z;
							mtl->_kd = Vector3d(x, y, z);
						}
						else if (type == "Ks")
						{
							lineStream >> x >> y >> z;
							mtl->_ks = Vector3d(x, y, z);
						}
						else if (type == "Ke")
						{
							lineStream >> x >> y >> z;
							mtl->_ke = Vector3d(x, y, z);
						}
						else if (type == "map_Kd" && mtl->_mapKd == "")
						{
							mtl->_mapKd = RecoverNameTex(line);
							LoadPng(mtl->_pathDirectory, mtl);
						}
					}
				}
			}

			if (mtl->_mapKd == "")
			{
				mtl->_mapKd = "White.png";
				LoadPng("../Textures/", mtl);
			}
			mtl->UpdateBufferObject();

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMaterial[" + name + "] loaded !");
			return mtl;
		}

		void LoaderMaterial::LoadPng(std::string const& pathDirectory, FrogEngine::feMaterial* mtl)
		{
			std::string name = FindFile(pathDirectory, mtl->_mapKd);

			mtl->_texture.Load(name, FrogEngine::TypeTexture::TEXTURE_2D, FrogEngine::TypeTexture::TEXTURE_2D);
		}
		
		std::string LoaderMaterial::RecoverNameTex(std::string line)
		{
			std::string mapKd;

			Math::Tools::Split(line, " ", true, line, mapKd);

			if (mapKd.back() == '\0' || mapKd.back() == '\r' || mapKd.back() == ' ')
				mapKd.pop_back();

			if (mapKd.find("\\") != std::string::npos)
				Math::Tools::Split(mapKd, "\\", false, line, mapKd);

			return mapKd;
		}

		std::string LoaderMaterial::FindFile(std::string const& directory, std::string const& name)
		{
			std::vector<std::string> childrenDirectory;
			
			for (const directory_iterator::value_type& p : directory_iterator(directory))
			{
				if (!p.path().has_extension())
					childrenDirectory.push_back(p.path().filename().string());

				if (p.path().filename() == name)
					return p.path().string();
			}

			std::string result;

			for (int idx = 0; idx < childrenDirectory.size(); ++idx)
			{
				result = FindFile(directory + childrenDirectory[idx], name);

				if (result != "File not found")
					return result;
			}
			
			return "File not found";
		}
	}
}