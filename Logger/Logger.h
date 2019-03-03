#pragma once

#include <string>

namespace Logging {
	
	enum Priority {
		INFORMATION = 0,
		WARNING,
		CRITICAL
	};

	class Logger 
	{
	public:
		// Ctor / Dtor
		Logger(Logger const&) = delete;

		static Logger& Instance();

		// Functions
		void operator=(Logger const&) = delete;

		template <typename ... T>
		void Log(Priority state, T&& ... args)
		{
			_file = fopen(_fileName.c_str(), "a");
			if (_file == nullptr)
			{
				CreateLogFile(CreateLogRep());
				_file = fopen(_fileName.c_str(), "a");
			}
			if (state == Priority::CRITICAL || state == Priority::WARNING)
				_isLogInOutput = true;
			LogPriority(state);
			int dummy[] = { 0, ((void)Log(std::forward<T>(args)), 0) ... };
			LogCarriageReturn();
			fclose(_file);
			_isLogInOutput = false;
		}
		
	private:
		// Ctor / Dtor
		Logger();
		~Logger();

		// Functions
		void Log(int t);
		void Log(double t);
		void Log(float t);
		void Log(std::string t);
		void Log(std::size_t t);
		void LogCarriageReturn();
		void LogPriority(Priority);

		std::string CreateLogRep();
		void CreateLogFile(std::string);

		std::string GetTime();
		std::string GetDateFileName();
		std::string GetPriorityString(Priority);
		
		// Variables
		FILE* _file;
		std::string _fileName;
		bool _isLogInOutput = false;

		static Logger* log_instance;

	};

} //namespace Logging