#include "GLBufferObject.h"

#include "../Error/RHIError.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace OPENGL
	{
		feBufferObject::feBufferObject()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBufferObject is creating. . .");
			RHIGLGenBuffers(1);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBufferObject created !");
		}

		feBufferObject::~feBufferObject()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBufferObject is deleting. . .");
			RHIGLDeleteBuffers(1);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLBufferObject deleted !");
		}

		int feBufferObject::Update(void* objectStruct, int size, int locationID)
		{
			Error error;

			error = RHIGLBindBuffer(GL_UNIFORM_BUFFER);
			if (error)	return error;

			error = RHIGLBufferData(GL_UNIFORM_BUFFER, size, objectStruct, GL_STREAM_DRAW);
			if (error)	return error;

			error = RHIGLUnbindBuffer(GL_UNIFORM_BUFFER);
			if (error)	return error;

			error = RHIGLBindBufferBase(GL_UNIFORM_BUFFER, locationID);
			if (error)	return error;

			return RHI_SUCCESS;
		}

		//private

		Error feBufferObject::RHIGLGenBuffers(GLsizei n)
		{
			glGenBuffers(n, &_UBO);

			GLenum error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLGenBuffers : N is a negative value.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBufferObject::RHIGLGenBuffers");
		}

		Error feBufferObject::RHIGLBindBuffer(GLenum target)
		{
			glBindBuffer(target, _UBO);

			GLenum error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feBufferObject::RHIGLBindBuffer : Target is not one of the allowable values.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLBindBuffer : feBuffer is not a name previously returned from a call to glGenBuffers.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBufferObject::RHIGLBindBuffer");
		}

		Error feBufferObject::RHIGLUnbindBuffer(GLenum target)
		{
			glBindBuffer(target, 0);

			GLenum error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feBufferObject::RHIGLUnbindBuffer : Target is not one of the allowable values.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLUnbindBuffer : feBuffer is not a name previously returned from a call to glGenBuffers.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBufferObject::RHIGLUnbindBuffer");
		}

		Error feBufferObject::RHIGLBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			glBufferData(target, size, data, usage);

			GLenum error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
			{
				if (target != GL_ARRAY_BUFFER && target != GL_ATOMIC_COUNTER_BUFFER && target != GL_COPY_READ_BUFFER && target != GL_COPY_WRITE_BUFFER && target != GL_DISPATCH_INDIRECT_BUFFER && target != GL_DRAW_INDIRECT_BUFFER && target != GL_ELEMENT_ARRAY_BUFFER && target != GL_PIXEL_PACK_BUFFER && target != GL_PIXEL_UNPACK_BUFFER && target != GL_QUERY_BUFFER && target != GL_SHADER_STORAGE_BUFFER && target != GL_TEXTURE_BUFFER && target != GL_TRANSFORM_FEEDBACK_BUFFER && target != GL_UNIFORM_BUFFER)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feBufferObject::RHIGLBufferData : Target is not one of the accepted buffer targets.");
				else if (usage != GL_STREAM_DRAW && usage != GL_STREAM_READ && usage != GL_STREAM_COPY && usage != GL_STATIC_DRAW && usage != GL_STATIC_READ && usage != GL_STATIC_COPY && usage != GL_DYNAMIC_DRAW && usage != GL_DYNAMIC_READ && usage != GL_DYNAMIC_COPY)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feBufferObject::RHIGLBufferData : Usage is not GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.");
			}
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLBufferData : Size is negative.");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feBufferObject::RHIGLBufferData : you may have bind the targeted buffer to 0. Otherwise, check the IMMUTABLE_FLAG of the buffer.");
			else if (error == GL_OUT_OF_MEMORY)
				return RHIError::CastError(Error::RHI_OUT_OF_MEMORY, WARNING, "feBufferObject::RHIGLBufferData : The GL is unable to create a _data store with the specified size.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBufferObject::RHIGLBufferData");
		}

		Error feBufferObject::RHIGLBindBufferBase(GLenum target, GLuint index)
		{
			glBindBufferBase(target, index, _UBO);

			GLenum error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feBufferObject::RHIGLBindBufferBase : Target is not GL_ATOMIC_COUNTER_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER or GL_SHADER_STORAGE_BUFFER.");
			else if (error == GL_INVALID_VALUE)
			{
				if (_UBO == 0)
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLBindBufferBase : feBuffer does not have an associated _data store, or if the size of that store is zero.");
				else
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLBindBufferBase : Index is greater than or equal to the number of target-specific indexed binding points.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBufferObject::RHIGLBindBufferBase");
		}

		Error feBufferObject::RHIGLDeleteBuffers(GLsizei n)
		{
			if (!glIsBuffer(_UBO))
				return Error::RHI_SUCCESS;

			glDeleteBuffers(n, &_UBO);

			GLenum error = glGetError();

			if (!error)
				return RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feBufferObject::RHIGLDeleteBuffers : N is negative.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feBufferObject::RHIGLDeleteBuffers");
		}
	} // namespace OPENGL
} // namespace FrogEngine