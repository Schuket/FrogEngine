#ifdef RHI_EXPORTS
#define GL_BUFFER_OBJECT_RHI __declspec(dllexport)
#else
#define GL_BUFFER_OBJECT_RHI __declspec(dllimport)
#endif

#pragma once

#include <GL/glew.h>
#include "AbstractBufferObject.h"

namespace FrogEngine
{
	enum Error;

	namespace OPENGL
	{
		class feBufferObject : public AbstractBufferObject
		{
		public:
			// Ctor / Dtor
			GL_BUFFER_OBJECT_RHI feBufferObject();
			GL_BUFFER_OBJECT_RHI ~feBufferObject();

			// Functions
			GL_BUFFER_OBJECT_RHI int Update(void* objectStruct, int size, int locationID = 0);

		private:
			// Functions
			Error RHIGLGenBuffers(GLsizei n);
			Error RHIGLBindBuffer(GLenum target);
			Error RHIGLUnbindBuffer(GLenum target);
			Error RHIGLBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
			Error RHIGLBindBufferBase(GLenum target, GLuint index);
			Error RHIGLDeleteBuffers(GLsizei n);

			// Variables
			GLuint _UBO;
		};
	} // namesapce OPENGL
} // namespace FrogEngine