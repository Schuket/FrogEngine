#include "feMeshSkybox.h"

#include "Image/Image.h"
#include "RHI\Texture\GLTexture.h"
#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace Mesh
	{
		feMeshSkybox::feMeshSkybox()
			: feMesh()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox is creating. . .");
			_name = "Unnamed Skybox";
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox created !");
		}

		feMeshSkybox::feMeshSkybox(feVertices data, std::vector<std::string> faces)
			:feMesh()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox is creating. . .");
			_name = "Unnamed Skybox";
			Init(data, faces);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox created !");
		}

		feMeshSkybox::~feMeshSkybox()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox is deleting. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox deleted !");
		}

		feMeshSkybox::feMeshSkybox(feMeshSkybox const& copy)
			:feMesh(copy)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox is copying. . .");
			_name = copy._name;
			_texture = copy._texture;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feMeshSkybox copied !");
		}

#pragma region Getters/Setters
		std::string feMeshSkybox::GetName()
		{
			return _name;
		}

		void feMeshSkybox::SetName(std::string const& name)
		{
			_name = name;
		}
#pragma endregion

		feMeshSkybox* feMeshSkybox::Clone()
		{
			return new feMeshSkybox(*this);
		}

		void feMeshSkybox::Draw()
		{
			_shader->Bind();

			feRenderer::SetDepthMode(DepthMode::LEQUAL);
			_buffer.Bind();

			_texture.Bind(_shader->GetProgram());

			feRenderer::Draw(36, TypeDraw::DRAW, TypePolygon::TRIANGLES);

			_texture.Unbind();

			_buffer.Unbind();
			feRenderer::SetDepthMode(DepthMode::LESS);

			_shader->Unbind();
		}

		void feMeshSkybox::Init(feVertices data, std::vector<std::string> faces)
		{
			int err = _buffer.Create(data);
			if (err)
				Logging::Logger::Instance().Log(Logging::CRITICAL, "feMeshSkybox::Init -> buffer.Create error");

			_texture.LoadSkybox(faces, FrogEngine::TypeTexture::TEXTURE_CUBE_MAP);
			_texture.SetIdx(0);
			_texture.SetSamplerName("skybox");
		}
	} // namespace Mesh
} // namespace Data