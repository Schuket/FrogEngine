#ifdef RHI_EXPORTS
#define GL_CORE_RHI __declspec(dllexport)
#else
#define GL_CORE_RHI __declspec(dllimport)
#endif

#pragma once

#include "AbstractRenderer.h"
#include <vector>
#include <GL/glew.h>

namespace FrogEngine
{
	enum Error;

	namespace OPENGL
	{
		class feRenderer : public AbstractRenderer
		{
		public:
			// Functions
			GL_CORE_RHI static int ClearBuffers(Math::Vector4d color);
			
			GL_CORE_RHI static int InitViewport(Math::Vector2d sizeWindow);
			GL_CORE_RHI static int InitDepthStencil();
			GL_CORE_RHI static int SetPolygonMode(PolygonMode mode);
			GL_CORE_RHI static int SetDepthMode(DepthMode mode);
			
			GL_CORE_RHI static int Draw(size_t count, TypeDraw typeDraw, TypePolygon typePoly);

		private:
			// Functions
			static GLenum feRenderer::ConvertTypePolygon(TypePolygon typePoly);

			static Error RHIGlewInit();
			static Error RHIGLInitViewport(GLint x, GLint y, GLsizei width, GLsizei height);
				   
			static Error RHIGLClear(std::vector<GLbitfield> masks);
			static Error RHIGLMatrixMode(GLenum mode);
			static Error RHIGLFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
				   
			static Error RHIGLPolygonMode(GLenum face, GLenum mode);
			static Error RHIGLEnable(GLenum cap);
			static Error RHIGLDepthFunc(GLenum func);
				   
			static Error RHIGLDrawArrays(GLenum mode, GLint first, GLsizei count);
			static Error RHIGLDrawElements(GLenum mode, GLint first, GLsizei count, GLvoid* indices);
			static Error RHIGLDrawElementBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid* indices, GLint baseVertex);
		};
	} // namespace OPENGL
} // namespace FrogEngine