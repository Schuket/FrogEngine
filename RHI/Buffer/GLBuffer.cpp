#include "GLBuffer.h"
#include "../Error/RHIError.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace OPENGL
	{
		feBuffer::feBuffer() 
		{ 
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBuffer is creating. . .");
			
			int error = GenID();
			if (error)
				Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "Error in OpenGL feBuffer Ctor");

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBuffer created !");
		}

		feBuffer::feBuffer(feVertices data, int& error)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBuffer is creating. . .");
			
			error = GenID();
			if (error) return;

			error = Create(data);

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBuffer created !");
		}

		feBuffer::~feBuffer()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBuffer is deleting. . .");
			RHIGLDeleteBuffers(1, &_ibo);
			RHIGLDeleteBuffers(1, &_vbo);
			RHIGLDeleteVertexArrays(1, &_vao);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBuffer deleted !");
		}

		int feBuffer::Create(feVertices data)
		{
			if (data._positions.empty())
				return RHIError::CastError(RHI_BUFFER_ERROR, WARNING, "You try to create buffer without any position");

			std::vector<float> vecData = data.GetFloatArray();
			int vertexSize = data.GetVertexSize();

			int error = RHIGLBindVertexArray(_vao);
			if (error) return error;

			error = InitBuffer(_vbo, GL_ARRAY_BUFFER, vecData.size() * sizeof(float), &vecData[0], GL_STATIC_DRAW);
			if (error) return error;

			if (!data._indices.empty())
			{
				error = InitBuffer(_ibo, GL_ELEMENT_ARRAY_BUFFER, data._indices.size() * sizeof(uint16_t), &data._indices[0], GL_STATIC_DRAW);
				if (error) return error;
			}

			error = BindAttribute(0, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), 0);
			if (error) return error;

			if (!data._texCoords.empty())
			{
				error = BindAttribute(1, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
				if (error) return error;
			}
			if (!data._normales.empty())
			{
				if (data._texCoords.empty())
				{
					error = BindAttribute(2, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
					if (error) return error;
				}
				else
				{
					error = BindAttribute(2, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(5 * sizeof(float)));
					if (error) return error;
				}
			}
			if (!data._tangent.empty())
			{
				error = BindAttribute(3, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(8 * sizeof(float)));
				if (error) return error;
			}

			error = UnbindBuffers();
			if (error) return error;

			return RHI_SUCCESS;
		}

		int feBuffer::Bind()
		{
			int error = RHIGLBindVertexArray(_vao);
			if (error) return error;

			return RHI_SUCCESS;
		}

		int feBuffer::Unbind()
		{
			int error = RHIGLBindVertexArray(0);
			if (error) return error;

			return RHI_SUCCESS;
		}

		//private

		int feBuffer::GenID()
		{
			int error = RHIGLGenVertexArrays(1, &_vao);
			if (error) return error;

			error = RHIGLGenBuffers(1, &_vbo);
			if (error) return error;


			error = RHIGLGenBuffers(1, &_ibo);
			if (error) return error;


			return RHI_SUCCESS;
		}

		int feBuffer::InitBuffer(GLuint& id, GLenum target, size_t size, void* data, GLenum usage)
		{
			int error = RHIGLBindBuffer(target, id);
			if (error) return error;

			error = RHIGLBufferData(target, size, data, usage);
			if (error) return error;

			return RHI_SUCCESS;
		}

		int feBuffer::BindAttribute(GLuint idx, GLint size, GLenum type, GLenum normalized, GLsizei stride, const GLvoid* offset)
		{
			int error = RHIGLVertexAttribPointer(idx, size, type, normalized, stride, offset);
			if (error) return error;

			error = RHIGLEnableVertexAttribArray(idx);
			if (error) return error;

			return RHI_SUCCESS;
		}

		int feBuffer::UnbindBuffers()
		{
			int error = RHIGLBindVertexArray(0);
			if (error) return error;

			error = RHIGLBindBuffer(GL_ARRAY_BUFFER, 0);
			if (error) return error;

			if (_ibo)
			{
				error = RHIGLBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				if (error) return error;
			}
			return RHI_SUCCESS;
		}

#pragma region OpenGL Encapsulation

		Error feBuffer::RHIGLGenVertexArrays(GLsizei n, GLuint* id)
		{
			glGenVertexArrays(n, id);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLGenVertexArrays : n is negative. Can't create negative number of buffer");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLGenVertexArrays");
		}

		Error feBuffer::RHIGLGenBuffers(GLsizei n, GLuint* id)
		{
			glGenBuffers(n, id);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLGenBuffers : n is negative. Can't create negative number of buffer");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLGenBuffers");
		}

		Error feBuffer::RHIGLBindVertexArray(GLuint id)
		{
			glBindVertexArray(id);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLBindVertexArray : Vertex array id is not valid. Check its Initialization.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLBindVertexArray");
		}

		Error feBuffer::RHIGLBindBuffer(GLenum target, GLuint id)
		{
			glBindBuffer(target, id);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feBuffer::RHIGLBindBuffer : target is not an allowed value.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLBindBuffer : Vertex buffer is not valid. Check its Initialization");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLBindBuffer");
		}

		Error feBuffer::RHIGLBufferData(GLenum target, size_t size, const GLvoid* data, GLenum usage)
		{
			glBufferData(target, size, data, usage);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLBufferData : size is negative.");
			else if (error == GL_OUT_OF_MEMORY)
				return RHIError::CastError(RHI_OUT_OF_MEMORY, CRITICAL, "feBuffer::RHIGLBufferData : OpenGL can't create a buffer of this specified size.");
			else if (error == GL_INVALID_ENUM)
			{
				if (usage != GL_STREAM_DRAW && usage != GL_STREAM_READ && usage != GL_STREAM_COPY && usage != GL_STATIC_DRAW && usage != GL_STATIC_READ
					&& usage != GL_STATIC_COPY && usage != GL_DYNAMIC_DRAW && usage != GL_DYNAMIC_READ && usage != GL_DYNAMIC_COPY)
					return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feBuffer::RHIGLBufferData : usage is not an allowed value.");
				else
					return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feBuffer::RHIGLBufferData : target is not an allowed value.");
			}
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLBufferData : you may have bind the targeted buffer to 0. Otherwise, check the IMMUTABLE_FLAG of the buffer.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLBufferData");
		}

		Error feBuffer::RHIGLVertexAttribPointer(GLuint idx, GLint size, GLenum type, GLenum normalized, GLsizei stride, const GLvoid* offset)
		{
			glVertexAttribPointer(idx, size, type, normalized, stride, offset);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : type is not an accepted value.");
			else if (error == GL_INVALID_VALUE)
			{
				if (stride < 0)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : stride is negative.");
				else if (idx >= GL_MAX_VERTEX_ATTRIBS)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : index is greater than or equal to GL_MAX_VERTEX_ATTRIBS.");
				else
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : size is not 1, 2, 3, 4 or GL_BGRA.");
			}
			else if (error == GL_INVALID_OPERATION)
			{
				if (size == GL_BGRA && normalized == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : if size is GL_BGRA, normalized must be true.");
				else if (size == GL_BGRA && (type == GL_UNSIGNED_BYTE || type == GL_INT_2_10_10_10_REV || type == GL_UNSIGNED_INT_2_10_10_10_REV))
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : type doesn't match the size GL_BGRA.");
				else if (type == GL_UNSIGNED_INT_10F_11F_11F_REV && size == 3)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : size doesn't match the type GL_UNSIGNED_INT_10F_11F_11F_REV.");
				else if ((type == GL_INT_2_10_10_10_REV || type == GL_UNSIGNED_INT_2_10_10_10_REV) && (size == 4 || size == GL_BGRA))
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : size doesn't match the type.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLVertexAttribPointer : no vertex bound, or zero is bound to GL_ARRAY_BUFFER.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLVertexAttribPointer");
		}

		Error feBuffer::RHIGLEnableVertexAttribArray(GLuint idx)
		{
			glEnableVertexAttribArray(idx);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBuffer::RHIGLEnableVertexAttribArray : no vertex array bound.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLEnableVertexAttribArray : index is greater than or equal to GL_MAX_VERTEX_ATTRIBS.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLEnableVertexAttribArray");
		}

		Error feBuffer::RHIGLDeleteBuffers(GLsizei n, const GLuint* id)
		{
			if (!glIsBuffer(*id))
				return Error::RHI_SUCCESS;

			glDeleteBuffers(n, id);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLDeleteBuffers : n is negative.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLDeleteBuffers");
		}

		Error feBuffer::RHIGLDeleteVertexArrays(GLsizei n, const GLuint* id)
		{
			if (!glIsVertexArray(*id))
				return Error::RHI_SUCCESS;

			glDeleteVertexArrays(n, id);

			int error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feBuffer::RHIGLDeleteVertexArrays : n is negative.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBuffer::RHIGLDeleteVertexArrays");
		}

#pragma endregion


	} // namespace OPENGL
} //namespace FrogEngine