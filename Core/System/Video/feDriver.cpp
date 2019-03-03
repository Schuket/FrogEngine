#include "feDriver.h"

#include "../feSceneManager.h"
#include "Core\Component\Video\feCamera.h"

#include "Logger\Logger.h"

namespace FrogEngine {
	namespace System {
		namespace Video {
		
			feDriver::~feDriver()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDriver is deleting. . .");

				_shaders.clear();

				_scnMgr = nullptr;
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDriver deleted !");
			}

			feDriver* feDriver::Create()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDriver is creating. . .");
				feDriver* feDrv = new feDriver();

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDriver created !");
				return feDrv;
			}

#pragma region Getter/Setter
			feShader* feDriver::GetProgramByName(std::string const& name)
			{
				std::map<std::string, feShader*>::iterator it = _shaders.begin();
				for (; it != _shaders.end(); it++)
				{
					if (it->first == name)
						return it->second;
				}

				return nullptr;
			}

			void feDriver::SetDefaultParameters()
			{
				feRenderer::InitDepthStencil();
			}

			void feDriver::SetSceneManager(feSceneManager* const& feScnMgr)
			{
				_scnMgr = feScnMgr;
			}
#pragma endregion

			void feDriver::Shutdown()
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDriver::Shutdown() is calling. . .");
				std::map<std::string, feShader*>::iterator it = _shaders.begin();
				for (; it != _shaders.end(); it++)
				{
					delete it->second;
					it->second = nullptr;
				}
				_shaders.erase(_shaders.begin(), _shaders.end());
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feDriver::Shutdown() called !");
			}

			void feDriver::Draw(feSceneManager* feScnMgr, Component::Video::feCamera* cam)
			{
				feRenderer::ClearBuffers(Math::Vector4d(0.3f, 0.3f, 0.3f, 1.0f));

				if (cam)
					feScnMgr->Draw(cam);
			}

			feShader* feDriver::LoadShader(std::string const& name)
			{
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + name + "] is loading. . .");
				feShader* id = GetProgramByName(name);

				if (id)
				{
					Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + name + "] loaded !");
					return id;
				}
				else
				{
					feShader* shader = new feShader();
					if (shader->Create(name) == Error::RHI_SUCCESS)
					{
						_shaders[name] = shader;

						Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + name + "] loaded !");

						return shader;
					}
				}

				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + name + "] didn't load !");

				return nullptr;
			}

			feDriver::feDriver()
			{
				_scnMgr = nullptr;
			}
		} // namespace Video
	} //namespace System
} //namespace FrogEngine