#include "GLRenderer.h"
#include "RHI\Error\RHIError.h"

namespace FrogEngine
{
	namespace OPENGL
	{
		int feRenderer::ClearBuffers(Math::Vector4d color)
		{
			Error error;

			glClearColor(color.X(), color.Y(), color.Z(), color.W());

			std::vector<GLbitfield> masks;
			masks.push_back(GL_COLOR_BUFFER_BIT);
			masks.push_back(GL_DEPTH_BUFFER_BIT);

			error = RHIGLClear(masks);
			if (error)	return error;

			return Error::RHI_SUCCESS;
		}

		int feRenderer::InitViewport(Math::Vector2d sizeWindow)
		{
			Error error;

			error = RHIGLInitViewport(0, 0, (GLsizei)sizeWindow.X(), (GLsizei)sizeWindow.Y());
			if (error)	return error;

			error = RHIGLMatrixMode(GL_PROJECTION);
			if (error)	return error;

			GLfloat ratio = static_cast<float>(sizeWindow.X() / sizeWindow.Y());
			error = RHIGLFrustum(-ratio, ratio, -1.f, 1.f, 0.1f, 1000.f);
			if (error)	return error;

			error = RHIGLMatrixMode(GL_MODELVIEW);
			if (error)	return error;

			return Error::RHI_SUCCESS;
		}

		int feRenderer::InitDepthStencil()
		{
			Error error;

			error = RHIGlewInit();
			if (error)	return error;

			error = RHIGLEnable(GL_DEPTH_TEST);
			if (error)	return error;

			error = RHIGLEnable(GL_FRAMEBUFFER_SRGB);
			if (error)	return error;

			error = RHIGLDepthFunc(GL_LEQUAL);
			if (error)	return error;

			glClearDepth(1.f);

			return Error::RHI_SUCCESS;
		}

		int feRenderer::SetPolygonMode(PolygonMode mode)
		{
			int error = 0;

			switch (mode)
			{
			case PolygonMode::FILL:
				error = RHIGLPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				if (error) return error;
				break;

			case PolygonMode::LINE:
				error = RHIGLPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				if (error) return error;
				break;

			case PolygonMode::POINTS:
				error = RHIGLPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
				if (error) return error;
				break;

			default:
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::SetPolygonMode : Mode is not valid.");

			}
			return RHI_SUCCESS;
		}

		int feRenderer::SetDepthMode(DepthMode mode)
		{
			int error = 0;

			switch (mode)
			{
			case DepthMode::LESS:
				error = RHIGLDepthFunc(GL_LESS);
				if (error) return error;
				break;

			case DepthMode::LEQUAL:
				error = RHIGLDepthFunc(GL_LEQUAL);
				if (error) return error;
				break;


			default:
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::SetPolygonMode : Mode is not valid.");

			}
			return RHI_SUCCESS;
		}

		int feRenderer::Draw(size_t count, TypeDraw typeDraw)
		{
			Error error;

			if (typeDraw == TypeDraw::DRAW)
			{
				error = RHIGLDrawArrays(GL_TRIANGLES, 0, (GLsizei)count);
				if (error)	return error;
			}
			else if (typeDraw == TypeDraw::DRAW_INDEXED)
			{
				error = RHIGLDrawElementBaseVertex(GL_PATCHES, (GLsizei)count, GL_UNSIGNED_SHORT, nullptr, 0);
				if (error)	return error;
			}

			return Error::RHI_SUCCESS;
		}

		//private

		Error feRenderer::RHIGlewInit()
		{
			GLenum error = glewInit();

			if (error != GLEW_OK)
				return RHIError::CastError(Error::RHI_UNKNOWN_ERROR, WARNING, "feRenderer::RHIGlewInit : glewInit error");

			return RHI_SUCCESS;
		}


		Error feRenderer::RHIGLInitViewport(GLint x, GLint y, GLsizei width, GLsizei height)
		{
			glViewport(x, y, width, height);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feRenderer::RHIGLInitViewport : Either width or height is negative.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLInitViewport");;
		}

		Error feRenderer::RHIGLClear(std::vector<GLbitfield> masks)
		{
			for (int idx = 0; idx < masks.size(); ++idx)
			{
				glClear(masks[idx]);

				GLenum error = glGetError();

				if (error == GL_INVALID_VALUE)
					return RHIError::CastError(Error::RHI_INVALID_VALUE, RHIPriority::WARNING, "feRenderer::RHIGLClear : Any bit other than the three defined bits is set in mask.");
			}

			return Error::RHI_SUCCESS;
		}

		Error feRenderer::RHIGLMatrixMode(GLenum mode)
		{
			glMatrixMode(mode);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::RHIGLMatrixMode : Mode is not an accepted value.");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feRenderer::RHIGLMatrixMode : glMatrixMode is executed between the execution of glBegin and the corresponding execution of glEnd.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLMatrixMode");
		}

		Error feRenderer::RHIGLFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal)
		{
			glFrustum(left, right, bottom, top, nearVal, farVal);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feRenderer::RHIGLFrustum : nearVal or farVal is not positive, or if left = right, or bottom = top, or near = far.");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feRenderer::RHIGLFrustum : glFrustum is executed between the execution of glBegin and the corresponding execution of glEnd.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLFrustum");
		}

		Error feRenderer::RHIGLPolygonMode(GLenum face, GLenum mode)
		{
			glPolygonMode(face, mode);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::RHIGLPolygonMode : face or mode value are not accepted.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLPolygonMode");
		}


		Error feRenderer::RHIGLEnable(GLenum cap)
		{
			glEnable(cap);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::RHIGLEnable : cap is not one of the values listed previously.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLEnable");
		}

		Error feRenderer::RHIGLDepthFunc(GLenum func)
		{
			glDepthFunc(func);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::RHIGLDepthFunc : func is not an accepted value.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLDepthFunc");
		}

		Error feRenderer::RHIGLDrawArrays(GLenum mode, GLint first, GLsizei count)
		{
			glDrawArrays(mode, first, count);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::RHIGLDrawArrays : mode is not an accepted value.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feRenderer::RHIGLDrawArrays : count is negative.");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feRenderer::RHIGLDrawArrays : a non-zero buffer object name is bound to an enabled array and the buffer object's _data store is currently mapped or a geometry shader is active and mode is incompatible with the input primitive type of the geometry shader in the currently installed program object.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLDrawArrays");
		}

		Error feRenderer::RHIGLDrawElementBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid* indices, GLint baseVertex)
		{
			glDrawElementsBaseVertex(mode, count, type, indices, baseVertex);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feRenderer::RHIGLDrawElementBaseVertex : mode is not an accepted value.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feRenderer::RHIGLDrawElementBaseVertex : count is negative.");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feRenderer::RHIGLDrawElementBaseVertex : a geometry shader is active and mode is incompatible with the input primitive type of the geometry shader in the currently installed program object or a non-zero buffer object name is bound to an enabled array or the element array and the buffer object's _data store is currently mapped.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feRenderer::RHIGLDrawElementBaseVertex");
		}
	} // namespace OPENGL
} // namespace FrogEngine