#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include "core/debug/ILogger.hpp"

class FileLogger : public ILogger
{
protected:
	std::ofstream m_File;
	std::filesystem::path m_FileName;

public:
	FileLogger() {}
	virtual ~FileLogger();
	FileLogger(const std::filesystem::path& fileName);

	void OpenFile(const std::filesystem::path& fileName);

	void Log(const LogData& data) override;
};

