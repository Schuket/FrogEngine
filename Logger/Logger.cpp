#include "Logger.h"

#include <direct.h>
#include <time.h>
#include <iostream>

namespace Logging {

	Logger* Logger::log_instance = new Logger();

	Logger::Logger()
	{
		std::string working_dir = CreateLogRep();
		CreateLogFile(working_dir);
	}

	Logger::~Logger() 
	{
		delete(_file);
		_file = nullptr;
	}

	Logger& Logger::Instance()
	{
		if (log_instance == nullptr)
			log_instance = new Logger();
		return *log_instance;
	}

	std::string Logger::CreateLogRep()
	{
		char* cwd = _getcwd(0, 0);
		std::string working_directory(cwd);
		std::free(cwd);
		working_directory += "\\Log";
		_mkdir(working_directory.c_str());
		return working_directory;
	}
	void Logger::CreateLogFile(std::string working_dir)
	{
		working_dir += "\\" + GetDateFileName();
		std::string oldFile(working_dir.begin(), working_dir.end());
		_file = fopen(oldFile.c_str(), "a+");
		_fileName = working_dir.c_str();
	}

	std::string Logger::GetTime()
	{
		struct tm * timeinfo;
		time_t rawtime;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		std::string _time = asctime(timeinfo);
		std::size_t found = _time.find_last_of('\n');
		return _time.substr(0, found);
	}
	std::string Logger::GetDateFileName()
	{
		std::string DateTime = GetTime();

		std::size_t found = DateTime.find_first_of(':');
		DateTime.replace(found, 1, "h");

		found = DateTime.find_first_of(':');
		DateTime.replace(found, 1, "m");
		DateTime.insert(found + 1, "in");

		found = DateTime.find_last_of(' ');
		DateTime.insert(found, "s");

		DateTime += ".felog";
		return DateTime;
	}

	std::string Logger::GetPriorityString(Priority log_state)
	{
		switch (log_state)
		{
		case INFORMATION:
			return "INFORMATION";
		case WARNING:
			return "WARNING";
		case CRITICAL:
			return "CRITICAL";
		default:
			return "NONE";
		}
	}
	void Logger::Log(int t)
	{
		std::string toWrite = std::to_string(t);
		if (_isLogInOutput)
			std::cout << toWrite.c_str();
		fputs(toWrite.c_str(), _file);
	}
	void Logger::Log(double t)
	{
		std::string toWrite = std::to_string(t);
		if (_isLogInOutput)
			std::cout << toWrite.c_str();
		fputs(toWrite.c_str(), _file);
	}
	void Logger::Log(float t)
	{
		std::string toWrite = std::to_string(t);
		if (_isLogInOutput)
			std::cout << toWrite.c_str();
		fputs(toWrite.c_str(), _file);
	}
	void Logger::Log(std::string t)
	{
		if (_isLogInOutput)
			std::cout << t.c_str();
		fputs(t.c_str(), _file);
	}
	void Logger::Log(std::size_t t)
	{
		std::string toWrite = std::to_string(t);
		if (_isLogInOutput)
			std::cout << toWrite.c_str();
		fputs(toWrite.c_str(), _file);
	}
	void Logger::LogCarriageReturn()
	{
		fputs("\n", _file);
		if (_isLogInOutput)
			std::cout << std::endl;
	}

	void Logger::LogPriority(Priority state)
	{
		std::string priorityString = GetPriorityString(state);
		priorityString += " : ";
		if (_isLogInOutput)
			std::cout << priorityString.c_str();
		fputs(priorityString.c_str(), _file);
	}
	
} //namespace Logging