#include "core/debug/console_logger.hpp"
#include "core/debug/log.hpp"

#include <iostream>

#define COLOR_WHITE "\x1B[37m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_YELLOW "\x1B[33m"
#define COLOR_RED "\x1B[31m"

void ConsoleLogger::Log(const LogData& data)
{
	std::string text = Log::FormatText(data);

	switch (data.Level)
	{
		case LogLevel::TRACE:
			std::cout << COLOR_WHITE;
			break;

		case LogLevel::DEBUG:
			std::cout << COLOR_WHITE;
			break;

		case LogLevel::INFO:
			std::cout << COLOR_GREEN;
			break;

		case LogLevel::WARNING:
			std::cout << COLOR_YELLOW;
			break;

		case LogLevel::ERROR:
			std::cout << COLOR_RED;
			break;

		case LogLevel::FATAL:
			std::cout << COLOR_RED;
			break;
	}

	std::cout << text;
}
