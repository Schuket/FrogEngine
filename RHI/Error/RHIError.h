#ifdef RHI_EXPORTS
#define RHI_ERROR __declspec(dllexport)
#else
#define RHI_ERROR __declspec(dllimport)
#endif

#pragma once

#include <string>

namespace FrogEngine {

	enum Error {
		RHI_SUCCESS = 0,
		RHI_INVALID_ENUM = -1,
		RHI_INVALID_VALUE = -2,
		RHI_INVALID_OPERATION = -3,
		RHI_INVALID_POINTER = -4,
		RHI_OUT_OF_MEMORY = -5,
		RHI_FILE_NOT_FOUND = -6,
		RHI_ACCESS_DENIED = -7,
		RHI_STACK_UNDERFLOW = -8,
		RHI_STACK_OVERFLOW = -9,
		RHI_SHADER_ERROR = -10,
		RHI_PROGRAM_ERROR = -11,
		RHI_BUFFER_ERROR = -12,
		RHI_UNKNOWN_ERROR = -13
	};

	enum RHIPriority {
		INFORMATION = 0,
		WARNING,
		CRITICAL
	};

	class RHIError {
	public:
		// Functions
		RHI_ERROR static Error CastError(Error error_type, RHIPriority state, std::string args);

	private:
		// Functions
		static std::string GetErrorName(Error);

	};

} //namespace FrogEngine

