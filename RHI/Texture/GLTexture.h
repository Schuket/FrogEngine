#ifdef RHI_EXPORTS
#define GL_TEXTURE_RHI __declspec(dllexport)
#else
#define GL_TEXTURE_RHI __declspec(dllimport)
#endif

#pragma once

#include <GL/glew.h>
#include <cstdint>

#include "AbstractTexture.h"

namespace FrogEngine
{
	enum Error;

	namespace OPENGL
	{
		class feTexture : public AbstractTexture
		{
		public:
			// Ctor / Dtor
			GL_TEXTURE_RHI feTexture();
			GL_TEXTURE_RHI ~feTexture();

			// Functions
			GL_TEXTURE_RHI int Load(std::string name, FrogEngine::TypeTexture type, FrogEngine::TypeTexture typeTex);
			GL_TEXTURE_RHI int LoadSkybox(std::vector<std::string> names, FrogEngine::TypeTexture type);
			GL_TEXTURE_RHI int Bind(uint32_t const& prgID);
			GL_TEXTURE_RHI int Unbind();

			GL_TEXTURE_RHI void SetIdx(int const& idx);
			GL_TEXTURE_RHI void SetSamplerName(std::string const& samplerName);

		private:
			// Functions
			int Init();
			int SetParameterTexture();
			int SetParameterCubeMap();
			
			GLenum ConvertTypeTex(FrogEngine::TypeTexture typeTex);

		#pragma region OpenGL Encapsulation

			Error RHIGLUniform1i(GLint location, GLint v0);
			Error RHIGLGetUniformLocation(GLint& loc, GLuint prg, const GLchar* name);
			Error RHIGLActiveTexture(GLenum texture);
			Error RHIGLGenTextures(GLsizei n);
			Error RHIGLBindTexture(GLenum target, GLuint texture);
			Error RHIGLTexParameteri(GLenum target, GLenum pname, GLint param);
			Error RHIGLTexImage2D(GLenum target, GLint level, GLint interFormat, GLsizei width, GLsizei height, GLint border, GLint format, GLenum type, const GLvoid* pixels);
			Error RHIGLDeleteTextures(GLsizei n);
		
		#pragma endregion

			// Variables
			GLuint _tex;
			GLenum _type;

			std::string _samplerName;
			int _idx;
		};
	}// namespace OPENGL
} //namespace FrogEngine