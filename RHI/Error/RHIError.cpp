#include "RHIError.h"
#include "Logger\Logger.h"

namespace FrogEngine {

	Error RHIError::CastError(Error error_type, RHIPriority state, std::string args)
	{
		std::string error_name = GetErrorName(error_type);
		Logging::Logger::Instance().Log((Logging::Priority)state, error_name.c_str(), args);

		return error_type;
	}

	std::string RHIError::GetErrorName(Error error_type)
	{
		switch (error_type)
		{
		case RHI_INVALID_ENUM:
			return "RHI_INVALID_ENUM : ";
		case RHI_INVALID_VALUE:
			return "RHI_INVALID_VALUE : ";
		case RHI_INVALID_OPERATION:
			return "RHI_INVALID_OPERATION : ";
		case RHI_INVALID_POINTER:
			return "RHI_INVALID_POINTER : ";
		case RHI_OUT_OF_MEMORY:
			return "RHI_OUT_OF_MEMORY : ";
		case RHI_FILE_NOT_FOUND:
			return "RHI_FILE_NOT_FOUND : ";
		case RHI_ACCESS_DENIED:
			return "RHI_ACCESS_DENIED : ";
		case RHI_STACK_UNDERFLOW:
			return "RHI_STACK_UNDERFLOW : ";
		case RHI_STACK_OVERFLOW:
			return "RHI_STACK_OVERFLOW : ";
		case RHI_SHADER_ERROR:
			return "RHI_SHADER_ERROR : ";
		case RHI_PROGRAM_ERROR:
			return "RHI_PROGRAM_ERROR : ";
		case RHI_BUFFER_ERROR:
			return "RHI_BUFFER_ERROR : ";
		case RHI_UNKNOWN_ERROR:
			return "RHI_UNKNOWN_ERROR : ";
		default:
			return "RHI_UNREGISTRED_ERROR : ";
		}
	}
} //namespace FrogEngine