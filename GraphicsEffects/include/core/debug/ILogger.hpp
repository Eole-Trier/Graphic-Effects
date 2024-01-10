#pragma once

#include "core/debug/log_data.hpp"

class ILogger
{
public:
	virtual ~ILogger() {};
	virtual void Log(const LogData& info) = 0;
};
