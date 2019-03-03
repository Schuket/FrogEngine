#include "GLShader.h"

#include <vector>
#include <fstream>

#include "../Error/RHIError.h"

#include "Logger/Logger.h"

namespace FrogEngine
{
	namespace OPENGL
	{
		//public:

		feShader::feShader()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader is creating. . .");
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader created !");
		}

		feShader::feShader(feShader const& copy)
		{
			_program = copy._program;
			_vertexShader = copy._vertexShader;
			_fragmentShader = copy._fragmentShader;
			_geometryShader = copy._geometryShader;
			_computeShader = copy._computeShader;
			_controlShader = copy._controlShader;
			_evaluationShader = copy._evaluationShader;
		}

		feShader::feShader(std::string name, int& error)
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + name + "] is creating. . .");
			error = Create(name);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + name + "] created !");
		}

		feShader::~feShader()
		{
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + _name + "] is deleting. . .");
			RHIGLDeleteShader(_computeShader);
			RHIGLDeleteShader(_geometryShader);
			RHIGLDeleteShader(_fragmentShader);
			RHIGLDeleteShader(_vertexShader);
			RHIGLDeleteShader(_controlShader);
			RHIGLDeleteShader(_evaluationShader);
			RHIGLDeleteProgram(_program);
			Logging::Logger::Instance().Log(Logging::Priority::INFORMATION, "feShader[" + _name + "] deleted !");
		}

		uint32_t feShader::GetProgram()
		{
			return _program;
		}

		int feShader::Create(std::string name)
		{
			_name = name;

			int error = LoadAllShaders(name);
			if (error)	return error;

			error = Link();
			if (error)	return error;

			error = BindUBOs();
			if (error) return error;

			Logging::Logger::Instance().Log(Logging::INFORMATION, "Shader [", _name, "] is created !");
			return Error::RHI_SUCCESS;
		}

		int feShader::Bind()
		{
			return RHIGLUseProgram(_program);
		}

		int feShader::Unbind()
		{
			return RHIGLUseProgram(0);
		}

		int feShader::BindTransform(Math::Matrix4 worldPos)
		{
			int worldMatLocation = 0;
			int error = RHIGLGetUniformLocation(worldMatLocation, _program, "worldMatrix");
			if (error) return error;

			error = RHIGLUniformMatrix4fv(worldMatLocation, 1, GL_FALSE, worldPos.DataVector());
			if (error) return error;

			return Error::RHI_SUCCESS;
		}

		feShader* feShader::Clone()
		{
			return new feShader(*this);
		}

		//private:

		int feShader::BindUBOs()
		{
			int error = BindUBO("Matrix", 1);
			if (error) 	return error;

			error = BindUBO("Light", 2);
			if (error) 	return error;

			error = BindUBO("Material", 3);
			if (error) 	return error;

			error = BindUBO("boundingSphere", 4);
			if (error) 	return error;

			return Error::RHI_SUCCESS;
		}

		int feShader::BindUBO(const GLchar* blockName, GLuint blockBinding)
		{
			GLint loc = -1;
			int error = RHIGLGetUniformBlockIndex(loc, _program, blockName);
			if (loc != -1)
				error = RHIGLUniformBlockBinding(_program, loc, blockBinding);
			if (error)
				return error;

			return RHI_SUCCESS;
		}

		int feShader::LoadAllShaders(std::string name)
		{
			std::string path = "../libs/FrogEngine/include/Core/Shader/" + name;

			int error = LoadShader(GL_VERTEX_SHADER, (path + ".vs.glsl").c_str());
			if (error)	return error;

			error = LoadShader(GL_FRAGMENT_SHADER, (path + ".fs.glsl").c_str());
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = LoadShader(GL_GEOMETRY_SHADER, (path + ".gs.glsl").c_str());
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = LoadShader(GL_COMPUTE_SHADER, (path + ".cs.glsl").c_str());
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = LoadShader(GL_TESS_CONTROL_SHADER, (path + ".tcs.glsl").c_str());
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = LoadShader(GL_TESS_EVALUATION_SHADER, (path + ".tes.glsl").c_str());
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			return Error::RHI_SUCCESS;
		}

		int feShader::LoadShader(GLuint type, const char* path)
		{
			std::string buffer;
			int error = ReadShaderFile(buffer, path);
			if (error)
				return error;

			GLuint shaderID;
			error = AssignID(shaderID, type);
			if (error)
				return error;

			return CompileShader(shaderID, buffer);
		}

		int feShader::ReadShaderFile(std::string& buffer, const char* path)
		{
			std::ifstream file;
			file.open(path, std::ios::binary);

			if (!file.good())
			{
				Logging::Logger::Instance().Log(Logging::INFORMATION, "RHI_FILE_NOT_FOUND : there is no file : ", std::string(path), " to open.");
				return RHI_FILE_NOT_FOUND;
			}

			buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
			file.close();

			return RHI_SUCCESS;
		}

		int feShader::AssignID(GLuint& shader, GLuint type)
		{
			Error error = RHIGLCreateShader(shader, type);
			if (error)
				return error;

			switch (type)
			{
			case GL_VERTEX_SHADER: _vertexShader = shader;
				break;
			case GL_FRAGMENT_SHADER: _fragmentShader = shader;
				break;
			case GL_GEOMETRY_SHADER: _geometryShader = shader;
				break;
			case GL_COMPUTE_SHADER:	_computeShader = shader;
				break;
			case GL_TESS_CONTROL_SHADER: _controlShader = shader;
				break;
			case GL_TESS_EVALUATION_SHADER:	_evaluationShader = shader;
				break;
			default:
				break;
			}
			return RHI_SUCCESS;
		}

		int feShader::CompileShader(GLuint shader, std::string buffer)
		{
			const char* c_buffer = buffer.c_str();

			int error = RHIGLShaderSource(shader, 1, &c_buffer, nullptr);
			if (error) return error;

			error = RHIGLCompileShader(shader);
			if (error) return error;

			GLint log_size = 0;
			RHIGLGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);

			if (log_size > 0)
			{
				std::vector<GLchar> log(log_size);
				error = RHIGLGetShaderInfoLog(shader, log_size, &log_size, &log[0]);
				if (error) 
					return error;
				return RHIError::CastError(RHI_SHADER_ERROR, CRITICAL, "Shader [" + _name + "] Compile Error :" + log.data());
			}

			return Error::RHI_SUCCESS;
		}

		int feShader::Link()
		{
			int error = RHIGLCreateProgram(_program);
			if (error)	return error;

			error = RHIGLAttachShader(_program, _vertexShader);
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = RHIGLAttachShader(_program, _fragmentShader);
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = RHIGLAttachShader(_program, _geometryShader);
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = RHIGLAttachShader(_program, _computeShader);
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			/*error = RHIGLAttachShader(_program, _controlShader);
			if (error && !RHI_FILE_NOT_FOUND)	return error;

			error = RHIGLAttachShader(_program, _evaluationShader);
			if (error && !RHI_FILE_NOT_FOUND)	return error;*/

			error = RHIGLLinkProgram(_program);
			if (error) return error;

			GLint log_size = 0;
			error = RHIGLGetProgramiv(_program, GL_INFO_LOG_LENGTH, &log_size);
			if (error) return error;

			if (log_size > 0)
			{
				std::vector<GLchar> log(log_size);
				error = RHIGLGetProgramInfoLog(_program, log_size, &log_size, &log[0]);
				if (error)
					return error;
				return RHIError::CastError(RHI_SHADER_ERROR, CRITICAL, "Shader [" + _name + "] Program link Error :" + log.data());
			}

			return Error::RHI_SUCCESS;
		}

		// OpenGL Encapsulation -> Use to Manage Error Easily
#pragma region OpenGl Encapsulation

		Error feShader::RHIGLCreateShader(GLuint& shader, GLuint type)
		{
			shader = glCreateShader(type);

			if (shader == 0)																			
				return RHIError::CastError(RHI_SHADER_ERROR, WARNING, "feShader::RHIGLCreateProgram : Cannot Create Program -> check compatibilities : computer, compiler, ...");

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error = GL_INVALID_ENUM)
				return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feShader::RHIGLCreateShader : feShader type not accepted. (NB: compute shader is OpenGL 4.3 or higher)");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLCreateShader");
		}

		Error feShader::RHIGLCreateProgram(GLuint& prg)
		{
			prg = glCreateProgram();

			if (prg == 0)
				return RHIError::CastError(RHI_PROGRAM_ERROR, WARNING, "feShader::RHIGLCreateProgram : Cannot Create Program -> check compatibilities : computer, compiler, ...");

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else
				return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLCreateProgram : RHIGLCreateProgram");
		}

		Error feShader::RHIGLUseProgram(GLuint prg)
		{
			glUseProgram(prg);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLUseProgram : program is not 0 nor created by API. Check his Initialization.");
			else if (error == GL_INVALID_OPERATION)
			{
				if (glIsProgram(prg) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLUseProgram : program is not valid. Check his Initialization.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLUseProgram : program could not be part of curr state / transform feedback mode is active.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLUseProgram");
		}

		Error feShader::RHIGLShaderSource(GLuint shader, GLsizei count, const GLchar** str, const GLint* len)
		{
			glShaderSource(shader, count, str, len);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLShaderSource : feShader not valid. Check his Initialization.");
			else if (error == GL_INVALID_VALUE)
			{
				if (count < 0)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLShaderSource : count is less than 0.");
				else if (glIsShader(shader) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLShaderSource : feShader not created by API. Check his Initialization.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLShaderSource");
		}

		Error feShader::RHIGLCompileShader(GLuint shader)
		{
			glCompileShader(shader);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLCompileShader : feShader not created by API. Check his Initialization");
			else if (error == GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLCompileShader : feShader not valid. Check his Initialization");
			else
				return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLCompileShader");
		}

		Error feShader::RHIGLGetShaderiv(GLuint shader, GLenum pname, GLint* params)
		{
			glGetShaderiv(shader, pname, params);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_ENUM)
				return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feShader::RHIGLGetShaderiv : pname is not valid.");
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feShader::RHIGLGetShaderiv : feShader is not created by API. Check his Initialize.");
			else if (error == GL_INVALID_OPERATION)
			{
				if (glIsShader(shader) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetShaderiv : feShader is not valid. Check his Initialize.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetShaderiv : pname is COMPILE_STATUS/INFO_LOG_LENGTH/SHADER_SOURCE_LENGTH, but shader compiler is not supported.");
			}
			else
				return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLGetShaderiv");
		}

		Error feShader::RHIGLGetShaderInfoLog(GLuint shader, GLsizei maxLen, GLsizei* len, GLchar* log)
		{
			glGetShaderInfoLog(shader, maxLen, len, log);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
			{
				if (maxLen < 0)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLGetShaderInfoLog : Max length is less than 0.");
				else
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLGetShaderInfoLog : feShader not created by API. Check his Initialization.");
			}
			else if (error == GL_INVALID_OPERATION)
			{
				if (glIsShader(shader) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetShaderInfoLog : feShader not valid. Check his Initialization.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetShaderInfoLog : function called between glBegin and glEnd. Not really possible with FrogEngine.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLGetShaderInfoLog");
		}

		Error feShader::RHIGLAttachShader(GLuint prg, GLuint shader)
		{
			if (!shader)
				return RHI_FILE_NOT_FOUND;

			glAttachShader(prg, shader);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLAttachShader : program or shader is not created by API. Check their Initialization.");
			else if (error == GL_INVALID_OPERATION)
			{
				if (glIsProgram(prg) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLAttachShader : program not valid. Check his Initialization.");
				else if (glIsShader(shader) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLAttachShader : shader not valid. Check his Initialization.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLAttachShader : shader already attached to program.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLAttachShader");
		}

		Error feShader::RHIGLLinkProgram(GLuint prg)
		{
			glLinkProgram(prg);

			GLint curPrg;
			glGetIntegerv(GL_CURRENT_PROGRAM, &curPrg);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader : program not generated by API. Check his Initialization.");
			else if (GL_INVALID_OPERATION)
			{
				if (glIsProgram(prg) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader : program not valid. Check his Initialization.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader : program is active and transform feedback is too. You may want to disable them for the moment.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader : RHIGLLinkProgram");
		}

		Error feShader::RHIGLGetProgramiv(GLuint prg, GLenum pname, GLint* params)
		{
			glGetProgramiv(prg, pname, params);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error = GL_INVALID_ENUM)
				return RHIError::CastError(RHI_INVALID_ENUM, CRITICAL, "feShader : pname is not valid. There is probably a problem with the FrogEngine.");
			else if (error = GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader : program is not created by the API. Check his Initialization.");
			else if (error = GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader : program is not valid. Check his Initialization.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader : RHIGLGetProgramiv");
		}

		Error feShader::RHIGLGetProgramInfoLog(GLuint prg, GLsizei maxlen, GLsizei* len, GLchar* log)
		{
			glGetProgramInfoLog(prg, maxlen, len, log);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetProgramInfoLog : program not valid. Check his Initialization.");
			else if (GL_INVALID_VALUE)
			{
				if (maxlen < 0)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLGetProgramInfoLog : maximum length is less than 0.");
				else
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLGetProgramInfoLog : program not generated by API. Check his Initialization.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLGetProgramInfoLog");
		}

		Error feShader::RHIGLDeleteShader(GLuint id)
		{
			if (!glIsShader(id))
				return Error::RHI_SUCCESS;

			glDeleteShader(id);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLDeleteShader : program not created by API. Check his Initialization.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLDeleteShader");
		}

		Error feShader::RHIGLDeleteProgram(GLuint id)
		{
			if (!glIsProgram(id))
				return Error::RHI_SUCCESS;

			glDeleteProgram(id);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error == GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLDeleteProgram : program not created by API. Check his Initialization.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader : RHIGLDeleteProgram");
		}

		Error feShader::RHIGLGetUniformLocation(GLint& loc, GLuint prg, const GLchar* name)
		{
			loc = glGetUniformLocation(prg, name);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (GL_INVALID_VALUE)
				RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLGetUniformLocation : program not generated by API. Check his Initialization.");
			else if (GL_INVALID_OPERATION)
			{
				if (glIsProgram(prg) == GL_FALSE)
					RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetUniformLocation : program not valid. Check his Initialization.");
				else
					RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetUniformLocation : program has not been link successfully. Check his Initialization or maybe your feShader's name.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLGetUniformLocation : RHIGLGetUniformLocation");
		}

		Error feShader::RHIGLUniformMatrix4fv(GLint loc, GLsizei count, GLboolean transpose, const std::vector<float> value)
		{
			glUniformMatrix4fv(loc, count, transpose, value.data());

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (GL_INVALID_VALUE)
				return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLUniformMatrix4fv : count is less than 0.");
			else if (GL_INVALID_OPERATION) //need Upgrade
			{
				int curShader = -1;
				glGetIntegerv(GL_CURRENT_PROGRAM, &curShader);
				if (curShader == 0)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLUniformMatrix4fv : no current program. Check that you have a program Bind.");
				else if (count > 1 && value.size() < 16)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLUniformMatrix4fv : size error. you must send multiple matrix4(16 floats), not less, or put count to 1.");
				else if (value.size() < 16 * count)
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLUniformMatrix4fv : size error. you must send matrix4(16) * count number of float.");
				else
					return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLUniformMatrix4fv : check the _data send and received between Application and feShader.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLUniformMatrix4fv : RHIGLUniformMatrix4fv");
		}

		Error feShader::RHIGLGetUniformBlockIndex(GLint& loc, GLuint prg, const GLchar* blockName)
		{
			loc = glGetUniformBlockIndex(prg, blockName);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;
			else if (error = GL_INVALID_OPERATION)
				return RHIError::CastError(RHI_INVALID_OPERATION, CRITICAL, "feShader::RHIGLGetUniformBlockIndex : program not valid. Check his Initialization.");

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLGetUniformBlockIndex : RHIGLGetUniformBlockIndex");
		}

		Error feShader::RHIGLUniformBlockBinding(GLuint prg, GLuint blockIndex, GLuint blockBinding)
		{
			glUniformBlockBinding(prg, blockIndex, blockBinding);

			GLenum error = glGetError();
			if (!error)
				return Error::RHI_SUCCESS;

			else if (GL_INVALID_VALUE)
			{
				if (blockBinding >= GL_MAX_UNIFORM_BUFFER_BINDINGS)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLUniformBlockBinding : UBO binding greater than maximal value ");
				else if (glIsProgram(prg) == GL_FALSE)
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLUniformBlockBinding : program not valid. Check his Initialization.");
				else
					return RHIError::CastError(RHI_INVALID_VALUE, CRITICAL, "feShader::RHIGLUniformBlockBinding : program not created by API. Check his Initialization.");
			}

			return RHIError::CastError(RHI_UNKNOWN_ERROR, CRITICAL, "feShader::RHIGLUniformBlockBinding");
		}

#pragma endregion



	} //namespace OPENGL
} //namespace FrogEngine