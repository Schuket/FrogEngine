#include "GLTexture.h"

#include "../Error/RHIError.h"

#include "Image/Image.h"
#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace OPENGL
	{
		feTexture::feTexture()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTexture is creating. . .");
			_tex = 0;
			_type = 0;
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTexture created !");
		}

		feTexture::~feTexture()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTexture is deleting. . .");
			RHIGLDeleteTextures(1);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTexture deleted !");
		}

		int feTexture::Load(std::string name, FrogEngine::TypeTexture type, FrogEngine::TypeTexture typeTex)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTexture[" + name + "] is loading. . .");
			_type = ConvertTypeTex(type);

			int error = Init();
			if (error) return error;

			FrogEngine::feImage image = LoaderImage::LoadImg(name);

			error = RHIGLTexImage2D(ConvertTypeTex(typeTex), 0, GL_SRGB_ALPHA, image._x, image._y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image._pixels);
			if (error)	return error;

			LoaderImage::FreeCache();

			error = SetParameterTexture();
			if (error)	return error;

			error = RHIGLBindTexture(_type, 0);
			if (error)	return error;
			
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTexture[" + name + "] loaded !");

			return Error::RHI_SUCCESS;
		}

		int feTexture::LoadSkybox(std::vector<std::string> names, FrogEngine::TypeTexture type)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTextureSkybox is loading. . .");
			_type = ConvertTypeTex(type);

			int error = Init();
			if (error) return error;

			for (int idx = 0; idx < names.size(); idx++)
			{
				FrogEngine::feImage image = LoaderImage::LoadImg(names[idx]);

				error = RHIGLTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + idx, 0, GL_SRGB_ALPHA, image._x, image._y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image._pixels);
				if (error)	return error;

				LoaderImage::FreeCache();
			}

			error = SetParameterCubeMap();
			if (error)	return error;

			error = RHIGLBindTexture(_type, 0);
			if (error)	return error;

			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "GLTextureSkybox loaded !");

			return Error::RHI_SUCCESS;
		}

		int feTexture::Bind(uint32_t const& prgID)
		{
			GLint location = -1;
			RHIGLGetUniformLocation(location, prgID, _samplerName.c_str());

			RHIGLUniform1i(location, _idx);
			RHIGLActiveTexture(GL_TEXTURE0 + _idx);

			Error error = RHIGLBindTexture(_type, _tex);
			if (error)	return error;


			return Error::RHI_SUCCESS;
		}

		int feTexture::Unbind()
		{
			Error error = RHIGLBindTexture(_type, 0);
			if (error)	return error;

			return Error::RHI_SUCCESS;
		}

		void feTexture::SetIdx(int const& idx)
		{
			_idx = idx;
		}

		void feTexture::SetSamplerName(std::string const& samplerName)
		{
			_samplerName = samplerName;
		}

		//private

		int feTexture::Init()
		{
			int error = RHIGLGenTextures(1);
			if (error)	return error;

			error = RHIGLBindTexture(_type, _tex);
			if (error)	return error;

			return RHI_SUCCESS;
		}

		int feTexture::SetParameterTexture()
		{
			int error = RHIGLTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			if (error)	return error;

			error = RHIGLTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			if (error)	return error;

			return RHI_SUCCESS;
		}

		int feTexture::SetParameterCubeMap()
		{
			int error = RHIGLTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (error)	return error;

			error = RHIGLTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			if (error)	return error;

			error = RHIGLTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			if (error)	return error;

			error = RHIGLTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			if (error)	return error;

			error = RHIGLTexParameteri(_type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			if (error)	return error;

			return RHI_SUCCESS;
		}

		GLenum feTexture::ConvertTypeTex(FrogEngine::TypeTexture typeTex)
		{
			switch (typeTex)
			{
			case FrogEngine::TypeTexture::TEXTURE_2D:
				return GL_TEXTURE_2D;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP:
				return GL_TEXTURE_CUBE_MAP;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP_POSITIVE_X:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP_NEGATIVE_X:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP_POSITIVE_Y:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP_NEGATIVE_Y:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP_POSITIVE_Z:
				return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
			case FrogEngine::TypeTexture::TEXTURE_CUBE_MAP_NEGATIVE_Z:
				return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
			default:
				return GL_NONE;
			}
		}

	#pragma region OpenGl Encapsulation

		Error feTexture::RHIGLUniform1i(GLint location, GLint v0)
		{
			glUniform1i(location, v0);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_OPERATION)
			{
				int curProg = -1;
				glGetIntegerv(GL_CURRENT_PROGRAM, &curProg);

				if (curProg == 0)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feTexture::RHIGLUniform1i : no current program. Check that you have a program Bind.");
				else if (location == -1)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feTexture::RHIGLUniform1i : location is an invalid uniform location.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feTexture::RHIGLUniform1i : check the _data send and received between Application and feShader.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLUniform1i");
		}

		Error feTexture::RHIGLGetUniformLocation(GLint& loc, GLuint prg, const GLchar* name)
		{
			loc = glGetUniformLocation(prg, name);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (GL_INVALID_VALUE)
				RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feTexture::RHIGLGetUniformLocation : program not generated by API. Check his Initialization.");
			else if (GL_INVALID_OPERATION)
			{
				if (glIsProgram(prg) == GL_FALSE)
					RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feTexture::RHIGLGetUniformLocation : program not valid. Check his Initialization.");
				else
					RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feTexture::RHIGLGetUniformLocation : program has not been link successfully. Check his Initialization or maybe your feShader's name.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLGetUniformLocation : RHIGLGetUniformLocation");
		}

		Error feTexture::RHIGLActiveTexture(GLenum texture)
		{
			glActiveTexture(texture);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;

			return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feTexture::RHIGLActiveTexture : texture is not one of GL_TEXTUREi, where i ranges from zero to the value of GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS minus one.");
		}

		Error feTexture::RHIGLGenTextures(GLsizei n)
		{
			glGenTextures(n, &_tex);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLGenTextures : N is a negative value.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLGenTextures");
		}

		Error feTexture::RHIGLBindTexture(GLenum target, GLuint texture)
		{
			glBindTexture(target, texture);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLBindTexture : Target is not one of the allowable values \n[GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BUFFER, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY]");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLBindTexture : feTexture is not a name returned from a previous call to glGenTextures.");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLBindTexture : feTexture was previously created with a target that doesn't match that of target.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLBindTexture");
		}

		Error feTexture::RHIGLTexParameteri(GLenum target, GLenum pname, GLint param)
		{
			glTexParameteri(target, pname, param);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
			{
				if (target != GL_TEXTURE_1D && target != GL_TEXTURE_1D_ARRAY && target != GL_TEXTURE_2D && target != GL_TEXTURE_2D_ARRAY && target != GL_TEXTURE_2D_MULTISAMPLE && target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY && target != GL_TEXTURE_3D && target != GL_TEXTURE_CUBE_MAP && target != GL_TEXTURE_CUBE_MAP_ARRAY && target != GL_TEXTURE_RECTANGLE)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : Target is not one of the accepted defined values");
				else if (param != GL_NEAREST && param != GL_LINEAR && param != GL_NEAREST_MIPMAP_NEAREST && param != GL_LINEAR_MIPMAP_NEAREST && param != GL_NEAREST_MIPMAP_LINEAR && param != GL_LINEAR_MIPMAP_LINEAR)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : Param should have a defined constant value and does not.");
				else if (pname != GL_DEPTH_STENCIL_TEXTURE_MODE && pname != GL_TEXTURE_BASE_LEVEL && pname != GL_TEXTURE_COMPARE_FUNC && pname != GL_TEXTURE_COMPARE_MODE && pname != GL_TEXTURE_LOD_BIAS && pname != GL_TEXTURE_MIN_FILTER && pname != GL_TEXTURE_MAG_FILTER && pname != GL_TEXTURE_MIN_LOD && pname != GL_TEXTURE_MAX_LOD && pname != GL_TEXTURE_MAX_LEVEL && pname != GL_TEXTURE_SWIZZLE_R && pname != GL_TEXTURE_SWIZZLE_G && pname != GL_TEXTURE_SWIZZLE_B && pname != GL_TEXTURE_SWIZZLE_A && pname != GL_TEXTURE_WRAP_S && pname != GL_TEXTURE_WRAP_T && pname != GL_TEXTURE_WRAP_R)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : Pname is not one of the accepted defined values");
				else if (pname == GL_TEXTURE_BORDER_COLOR || pname == GL_TEXTURE_SWIZZLE_RGBA)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : GlTexParameter is called for a non-scalar parameter (GL_TEXTURE_BORDER_COLOR or GL_TEXTURE_SWIZZLE_RGBA)");
				else if ((target == GL_TEXTURE_2D_MULTISAMPLE || target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY) && pname != GL_TEXTURE_BORDER_COLOR  && pname != GL_TEXTURE_COMPARE_FUNC && pname != GL_TEXTURE_COMPARE_MODE && pname != GL_TEXTURE_LOD_BIAS && pname != GL_TEXTURE_MAX_LOD && pname != GL_TEXTURE_MAG_FILTER && pname != GL_TEXTURE_MIN_FILTER && pname != GL_TEXTURE_MIN_LOD && pname != GL_TEXTURE_WRAP_S && pname != GL_TEXTURE_WRAP_T && pname != GL_TEXTURE_WRAP_R)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : Target is either GL_TEXTURE_2D_MULTISAMPLE or GL_TEXTURE_2D_MULTISAMPLE_ARRAY, and pname is any of the sampler states.");
				else if (target == GL_TEXTURE_RECTANGLE && pname != GL_TEXTURE_WRAP_S && pname != GL_TEXTURE_WRAP_T && (param == GL_MIRROR_CLAMP_TO_EDGE || param == GL_MIRRORED_REPEAT || param == GL_REPEAT))
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : Target is GL_TEXTURE_RECTANGLE and either of pnames GL_TEXTURE_WRAP_S or GL_TEXTURE_WRAP_T is set to either GL_MIRROR_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT or GL_REPEAT.");
				else if (target == GL_TEXTURE_RECTANGLE && pname == GL_TEXTURE_MIN_FILTER && (param == GL_NEAREST || param == GL_LINEAR))
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexParameteri : Target is GL_TEXTURE_RECTANGLE and pname GL_TEXTURE_MIN_FILTER is set to a value other than GL_NEAREST or GL_LINEAR");
				else
					return RHIError::CastError(Error::RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLTexParameteri : RHIGLTexParameteri(GLTexture): RHI_INVALID_ENUM");
			}
			else if (error == GL_INVALID_OPERATION)
			{
				if (target != GL_TEXTURE_2D_MULTISAMPLE && target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY && pname == GL_TEXTURE_BASE_LEVEL && param != 0)
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexParameteri : Target is either GL_TEXTURE_2D_MULTISAMPLE or GL_TEXTURE_2D_MULTISAMPLE_ARRAY, and pname GL_TEXTURE_BASE_LEVEL is set to a value other than zero.");
				else if (target == GL_TEXTURE_RECTANGLE && pname == GL_TEXTURE_BASE_LEVEL && param != 0)
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexParameteri : Target is GL_TEXTURE_RECTANGLE and pname GL_TEXTURE_BASE_LEVEL is set to any value other than zero.");
				else
					return RHIError::CastError(Error::RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLTexParameteri : RHIGLTexParameteri(GLTexture): RHI_INVALID_OPERATION");
			}
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexParameteri : Pname is GL_TEXTURE_BASE_LEVEL or GL_TEXTURE_MAX_LEVEL, and param or params is negative.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLTexParameteri");
		}

		Error feTexture::RHIGLTexImage2D(GLenum target, GLint level, GLint interFormat, GLsizei width, GLsizei height, GLint border, GLint format, GLenum type, const GLvoid* pixels)
		{
			glTexImage2D(target, level, interFormat, width, height, border, format, type, pixels);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
			{
				if (target != GL_TEXTURE_2D && target != GL_TEXTURE_1D_ARRAY && target != GL_TEXTURE_RECTANGLE && target != GL_PROXY_TEXTURE_2D && target != GL_PROXY_TEXTURE_1D_ARRAY && target != GL_PROXY_TEXTURE_RECTANGLE && target != GL_PROXY_TEXTURE_CUBE_MAP && target != GL_TEXTURE_CUBE_MAP_POSITIVE_X && target != GL_TEXTURE_CUBE_MAP_NEGATIVE_X && target != GL_TEXTURE_CUBE_MAP_POSITIVE_Y && target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Y && target != GL_TEXTURE_CUBE_MAP_POSITIVE_Z && target != GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexImage2D : Target is not GL_TEXTURE_2D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_2D, GL_PROXY_TEXTURE_1D_ARRAY, GL_PROXY_TEXTURE_RECTANGLE, GL_PROXY_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, or GL_TEXTURE_CUBE_MAP_NEGATIVE_Z.");
				else if (type != GL_UNSIGNED_BYTE && type != GL_BYTE  && type != GL_UNSIGNED_SHORT && type != GL_SHORT && type != GL_UNSIGNED_INT && type != GL_INT && type != GL_FLOAT && type != GL_UNSIGNED_BYTE_3_3_2 && type != GL_UNSIGNED_BYTE_2_3_3_REV && type != GL_UNSIGNED_SHORT_5_6_5 && type != GL_UNSIGNED_SHORT_5_6_5_REV && type != GL_UNSIGNED_SHORT_4_4_4_4 && type != GL_UNSIGNED_SHORT_4_4_4_4_REV && type != GL_UNSIGNED_SHORT_5_5_5_1 && type != GL_UNSIGNED_SHORT_1_5_5_5_REV && type != GL_UNSIGNED_INT_8_8_8_8 && type != GL_UNSIGNED_INT_8_8_8_8_REV && type != GL_UNSIGNED_INT_10_10_10_2 && type != GL_UNSIGNED_INT_2_10_10_10_REV)
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexImage2D : Type is not a type constant.");
				else 
					return RHIError::CastError(Error::RHI_INVALID_ENUM, WARNING, "feTexture::RHIGLTexImage2D : Target is one of the six cube map 2D image targets and the width and height parameters are not equal.");
			}
			else if (error == GL_INVALID_VALUE)
			{
				if (width < 0 || width > GL_MAX_TEXTURE_SIZE)
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Width is less than 0 or greater than GL_MAX_TEXTURE_SIZE.");
				else if (target != GL_TEXTURE_1D_ARRAY && target != GL_PROXY_TEXTURE_1D_ARRAY && (height < 0 || height > GL_MAX_TEXTURE_SIZE))
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Target is not GL_TEXTURE_1D_ARRAY or GL_PROXY_TEXTURE_1D_ARRAY and height is less than 0 or greater than GL_MAX_TEXTURE_SIZE.");
				else if ((target == GL_TEXTURE_1D_ARRAY || target == GL_PROXY_TEXTURE_1D_ARRAY) && (height < 0 || height > GL_MAX_ARRAY_TEXTURE_LAYERS))
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Target is GL_TEXTURE_1D_ARRAY or GL_PROXY_TEXTURE_1D_ARRAY and height is less than 0 or greater than GL_MAX_ARRAY_TEXTURE_LAYERS.");
				else if (level < 0)
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Level is less than 0.");
				else if (level > log2(GL_MAX_TEXTURE_SIZE))
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : If level is greater than log2(GL_MAX_TEXTURE_SIZE).");
				else if ((width < 0 || width > GL_MAX_TEXTURE_SIZE) || (height < 0 || height > GL_MAX_TEXTURE_SIZE))
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Width or height is less than 0 or greater than GL_MAX_TEXTURE_SIZE.");
				else if (border != 0)
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Border is not 0.");
				else if ((target == GL_TEXTURE_RECTANGLE || target == GL_PROXY_TEXTURE_RECTANGLE) && level != 0)
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : Target is GL_TEXTURE_RECTANGLE or GL_PROXY_TEXTURE_RECTANGLE and level is not 0.");
				else 
					return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLTexImage2D : InternalFormat is not one of the accepted resolution and format symbolic constants.");
			}
			else if (error == GL_INVALID_OPERATION)
			{
				if ((type == GL_UNSIGNED_BYTE_3_3_2 || type == GL_UNSIGNED_BYTE_2_3_3_REV || type == GL_UNSIGNED_SHORT_5_6_5 || type == GL_UNSIGNED_SHORT_5_6_5_REV || type == GL_UNSIGNED_INT_10F_11F_11F_REV) && format != GL_RGB)
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexImage2D : Type is one of GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV, or GL_UNSIGNED_INT_10F_11F_11F_REV, and format is not GL_RGB.");
				else if ((type == GL_UNSIGNED_SHORT_4_4_4_4 || type == GL_UNSIGNED_SHORT_4_4_4_4_REV || type == GL_UNSIGNED_SHORT_5_5_5_1 || type == GL_UNSIGNED_SHORT_1_5_5_5_REV || type == GL_UNSIGNED_INT_8_8_8_8 || type == GL_UNSIGNED_INT_8_8_8_8_REV || type == GL_UNSIGNED_INT_10_10_10_2 || type == GL_UNSIGNED_INT_2_10_10_10_REV || type == GL_UNSIGNED_INT_5_9_9_9_REV) && format != GL_RGBA && format != GL_BGRA)
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexImage2D : Type is one of GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2, GL_UNSIGNED_INT_2_10_10_10_REV, or GL_UNSIGNED_INT_5_9_9_9_REV, and format is neither GL_RGBA nor GL_BGRA.");
				else if (target != GL_TEXTURE_2D && target != GL_PROXY_TEXTURE_2D && target != GL_TEXTURE_RECTANGLE && target != GL_PROXY_TEXTURE_RECTANGLE && (interFormat == GL_DEPTH_COMPONENT || interFormat == GL_DEPTH_COMPONENT16 || interFormat == GL_DEPTH_COMPONENT24 || interFormat == GL_DEPTH_COMPONENT32F))
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexImage2D : Target is not GL_TEXTURE_2D, GL_PROXY_TEXTURE_2D, GL_TEXTURE_RECTANGLE, or GL_PROXY_TEXTURE_RECTANGLE, and internalFormat is GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, or GL_DEPTH_COMPONENT32F.");
				else if (format == GL_DEPTH_COMPONENT && interFormat != GL_DEPTH_COMPONENT && interFormat != GL_DEPTH_COMPONENT16 && interFormat != GL_DEPTH_COMPONENT24 && interFormat != GL_DEPTH_COMPONENT32F)
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexImage2D : Format is GL_DEPTH_COMPONENT and internalFormat is not GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, or GL_DEPTH_COMPONENT32F.");
				else if ((interFormat == GL_DEPTH_COMPONENT || interFormat == GL_DEPTH_COMPONENT16 || interFormat == GL_DEPTH_COMPONENT24 || interFormat == GL_DEPTH_COMPONENT32F) && format != GL_DEPTH_COMPONENT)
					return RHIError::CastError(Error::RHI_INVALID_OPERATION, WARNING, "feTexture::RHIGLTexImage2D : InternalFormat is GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT24, or GL_DEPTH_COMPONENT32F, and format is not GL_DEPTH_COMPONENT.");
				else
					return RHIError::CastError(Error::RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLTexImage2D : Maybe check if a non-zero buffer object name is bound to the GL_PIXEL_UNPACK_BUFFER target.");
			}
			
			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLTexImage2D");
		}

		Error feTexture::RHIGLDeleteTextures(GLsizei n)
		{
			if (!glIsTexture(_tex))
				return Error::RHI_SUCCESS;

			glDeleteTextures(n, &_tex);

			GLenum error = glGetError();

			if (!error)
				return Error::RHI_SUCCESS;
			else if (error = GL_INVALID_VALUE)
				return RHIError::CastError(Error::RHI_INVALID_VALUE, WARNING, "feTexture::RHIGLDeleteTextures : N is negative");
			
			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feTexture::RHIGLDeleteTextures");
		}

	#pragma endregion

	} // namespace OPENGL
} // namespace FrogEngine