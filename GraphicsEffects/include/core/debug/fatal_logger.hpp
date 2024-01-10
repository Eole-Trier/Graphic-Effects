#pragma once

#include "core/debug/file_logger.hpp"

// Inheriting from file logger is kind of dirty but it works and i don't have to re-write the file code
class FatalLogger : public FileLogger
{
public:
	FatalLogger(const std::filesystem::path& fileName) : FileLogger(fileName) {}
	void Log(const LogData& data) override;
};

