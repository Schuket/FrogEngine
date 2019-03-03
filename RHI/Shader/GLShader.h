#pragma once

#ifdef RHI_EXPORTS
#define GL_SHADER_RHI __declspec(dllexport)
#else
#define GL_SHADER_RHI __declspec(dllimport)
#endif


#include "AbstractShader.h"

#include <GL/glew.h>

namespace FrogEngine
{
	enum Error;
	   
	namespace OPENGL
	{
		class feShader : public AbstractShader
		{
		public:
			// Ctor / Dtor
			GL_SHADER_RHI feShader();
			GL_SHADER_RHI feShader(std::string, int&);
			GL_SHADER_RHI ~feShader();

			// Functions
			GL_SHADER_RHI uint32_t GetProgram();

			GL_SHADER_RHI int Create(std::string);

			GL_SHADER_RHI int Bind();
			GL_SHADER_RHI int Unbind();
			GL_SHADER_RHI int BindTransform(Math::Matrix4 worldPos);
			GL_SHADER_RHI feShader* Clone();
		private:
			feShader(feShader const& copy);
			// Functions
			int BindUBOs();
			int BindUBO(const GLchar* blockName, GLuint blockBinding);

			int LoadAllShaders(std::string);

			int LoadShader(GLuint type, const char* path);
			int ReadShaderFile(std::string& buffer, const char* path);
			int AssignID(GLuint& shader, GLuint type);
			int CompileShader(GLuint shader, std::string buffer);

			int Link();

			//Use to Manage Error 
			#pragma region OpenGL Encapsulation 

			Error RHIGLCreateShader(GLuint& shader, GLuint type);
			Error RHIGLCreateProgram(GLuint& prg);

			Error RHIGLUseProgram(GLuint shader);

			Error RHIGLShaderSource(GLuint shader, GLsizei count, const GLchar** str, const GLint* len);
			Error RHIGLCompileShader(GLuint shader);
			Error RHIGLGetShaderiv(GLuint shader, GLenum pname, GLint* params);
			Error RHIGLGetShaderInfoLog(GLuint shader, GLsizei maxLen, GLsizei* len, GLchar* log);

			Error RHIGLAttachShader(GLuint prg, GLuint shader);
			Error RHIGLLinkProgram(GLuint prg);
			Error RHIGLGetProgramiv(GLuint prg, GLenum pname, GLint* params);
			Error RHIGLGetProgramInfoLog(GLuint prg, GLsizei maxlen, GLsizei* len, GLchar* log);

			Error RHIGLDeleteShader(GLuint shader);
			Error RHIGLDeleteProgram(GLuint prg);

			Error RHIGLGetUniformLocation(GLint& loc, GLuint prg, const GLchar* name);
			Error RHIGLUniformMatrix4fv(GLint loc, GLsizei count, GLboolean transpose, const std::vector<float> value);

			Error RHIGLGetUniformBlockIndex(GLint& loc, GLuint prg, const GLchar* blockName);
			Error RHIGLUniformBlockBinding(GLuint prg, GLuint blockIndex, GLuint blockBinding);

			#pragma endregion
			
			// Variables
			GLuint _program = 0;
			GLuint _vertexShader = 0;
			GLuint _fragmentShader = 0;
			GLuint _geometryShader = 0;
			GLuint _computeShader = 0;
			GLuint _controlShader = 0;
			GLuint _evaluationShader = 0;
		};

	} //namespace OPEN
} //namespace FrogEngine
