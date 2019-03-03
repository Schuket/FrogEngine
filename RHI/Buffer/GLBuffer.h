#ifdef RHI_EXPORTS
#define GL_BUFFER_RHI __declspec(dllexport)
#else
#define GL_BUFFER_RHI __declspec(dllimport)
#endif

#pragma once

#include <GL/glew.h>

#include "AbstractBuffer.h"

namespace FrogEngine
{
	enum Error;

	namespace OPENGL
	{
		class feBuffer : public AbstractBuffer
		{
		public:
			// Ctor / Dtor
			GL_BUFFER_RHI feBuffer();
			GL_BUFFER_RHI feBuffer(feVertices data, int& error);
			GL_BUFFER_RHI ~feBuffer();

			// Functions
			GL_BUFFER_RHI virtual int Create(feVertices data);
			GL_BUFFER_RHI virtual int Bind();
			GL_BUFFER_RHI virtual int Unbind();

		private:
			// Functions
			int GenID();
			int InitBuffer(GLuint& id, GLenum target, size_t size, void* data, GLenum usage);
			int BindAttribute(GLuint idx, GLint size, GLenum type, GLenum normalized, GLsizei stride, const GLvoid* offset);
			int UnbindBuffers();

			#pragma region OpenGL Encapsulation

			Error RHIGLGenVertexArrays(GLsizei n, GLuint* id);
			Error RHIGLGenBuffers(GLsizei n, GLuint* id);

			Error RHIGLBindVertexArray(GLuint id);
			Error RHIGLBindBuffer(GLenum target, GLuint id);

			Error RHIGLBufferData(GLenum target, size_t size, const GLvoid* data, GLenum usage);

			Error RHIGLVertexAttribPointer(GLuint idx, GLint size, GLenum type, GLenum normalized, GLsizei stride, const GLvoid* offset);
			Error RHIGLEnableVertexAttribArray(GLuint idx);

			Error RHIGLDeleteBuffers(GLsizei n, const GLuint* id);
			Error RHIGLDeleteVertexArrays(GLsizei n, const GLuint* id);

			#pragma endregion

			// Variables
			GLuint _vao = 0;
			GLuint _vbo = 0;
			GLuint _ibo = 0;
		};
	} // namespace OPENGL
} //namespace FrogEngine