#pragma once

#include <chrono>
#include <iostream>
#include <string>


namespace CourseraModernCPP{

	// Simple profiler for course purposes.

	class LogDuration
	{
	public:
		explicit LogDuration(const std::string& msg = "")
			: message(msg + ": ")
			, start(std::chrono::steady_clock::now())
		{}

		~LogDuration()
		{
			auto finish = std::chrono::steady_clock::now();
			auto dur = finish - start;
			std::cerr << message
				<< std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
				<< " ms" << std::endl;
		}
	private:
		std::string message;
		std::chrono::steady_clock::time_point start;
	};
}

#define _LOG_ID_IMPL(lineno) _log_var##lineno
#define _LOG_ID(lineno) _LOG_ID_IMPL(lineno)

#define LOG_DURATION(message) CourseraModernCPP::LogDuration _LOG_ID(__LINE__){message};