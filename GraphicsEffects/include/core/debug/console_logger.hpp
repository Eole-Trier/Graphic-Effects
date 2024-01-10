#pragma once

#include "core/debug/ILogger.hpp"

class ConsoleLogger : public ILogger
{
public:
	void Log(const LogData& data) override;
};

