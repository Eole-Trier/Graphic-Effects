#pragma once

#include <string>
#include "core/debug/log_level.hpp"

struct LogData
{
	const LogLevel Level;
	const std::string Message;
	const char* const Function;
	const char* const File;
	const uint32_t Line;
	const std::string Date;

	LogData(const LogLevel _level,
		const std::string& _message,
		const char* const _function,
		const char* const _file,
		const uint32_t _line,
		const std::string& _date)
		: Level(_level), Message(_message), Function(_function), File(_file), Line(_line), Date(_date)
	{}
};
