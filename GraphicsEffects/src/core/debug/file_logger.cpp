#include "core/debug/file_logger.hpp"
#include "core/debug/log.hpp"

#include <iostream>

FileLogger::FileLogger(const std::filesystem::path& fileName)
{
	OpenFile(fileName);
}

FileLogger::~FileLogger()
{
	if (m_File.is_open())
	{
		// Just in case
		m_File.flush();
		m_File.close();
	}
}

void FileLogger::OpenFile(const std::filesystem::path& fileName)
{
	// Delete file
	std::remove(fileName.string().c_str());

	m_FileName = fileName;
	m_File = std::ofstream(m_FileName);

	if (m_File.bad())
	{
		// Yield error if file is bad, this should be printed in the console
		Log::LogError(std::string("Error while opening file for logging : ").append(m_FileName.string()));
		return;
	}

	if (!m_File.is_open())
	{
		// Yield error if file couldn't be opened
		// (which shouldn't happen because ofstream creates it if it doesn't exists)
		// this should be printed in the console
		Log::LogError(std::string("Couldn't open file for logging : ").append(m_FileName.string()));
		return;
	}
}

void FileLogger::Log(const LogData& data)
{
	const std::string text = Log::FormatText(data);

	m_File.write(text.c_str(), text.size());
	m_File.flush();
}
