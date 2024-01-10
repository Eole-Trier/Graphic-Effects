#include "core/debug/log.hpp"
#include "core/debug/assert.hpp"

#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>

std::vector<ILogger*> Log::m_Loggers;

std::thread Log::m_Thread;
std::condition_variable Log::m_CondVar;
TsQueue<LogData> Log::m_QueuedMessages;
std::mutex Log::m_Mutex;
bool Log::m_Running = true;

void Log::Init()
{
	// Start thread
	m_Thread = std::thread(Log::Run);
	m_Running = true;
}

void Log::Stop()
{
	// Set not running and wake up the thread one last time to fully stop it
	m_Running = false;
	m_CondVar.notify_one();

	// Cleanup loggers
	for (size_t i = 0; i < m_Loggers.size(); i++)
		delete m_Loggers[i];

	m_Loggers.clear();

	// Join with main thread
	if (m_Thread.joinable())
		m_Thread.join();
}

void Log::Run()
{
	std::unique_lock<std::mutex> lock(m_Mutex);
	
	// Allows for the thread to be stopped by setting m_Running to false and waking it up
	while (m_Running)
	{
		// Make the thread wait
		m_CondVar.wait(lock, [](){ return !m_QueuedMessages.Empty() || !m_Running; });
	
		// Process every message
		while (!m_QueuedMessages.Empty())
		{
			// Pop the message, which removes it from the queue
			const LogData data = m_QueuedMessages.PopFront();
			for (size_t i = 0; i < m_Loggers.size(); i++)
			{
				// Send to each logger
				m_Loggers[i]->Log(data);
			}
		}
	}
}

void Log::AddLogger(ILogger* const logger)
{
	Assert::IsTrue(logger != nullptr, "Can't add an empty logger");

	m_Loggers.push_back(logger);
}

void Log::RemoveLogger(ILogger* const logger, const bool freeMem)
{
	Assert::IsTrue(logger != nullptr, "Can't remove an empty logger");

	const std::vector<ILogger*>::iterator position = std::find(m_Loggers.begin(), m_Loggers.end(), logger);
	m_Loggers.erase(position);

	if (freeMem)
		delete logger;
}

void Log::LogInfo(const std::string& message, const char* funcName, const char* fileName, const int32_t line)
{
	ForwardLog(CreateLogData(LogLevel::INFO, message, funcName, fileName, line));
}

void Log::LogWarning(const std::string& message, const char* funcName, const char* fileName, const int32_t line)
{
	ForwardLog(CreateLogData(LogLevel::WARNING, message, funcName, fileName, line));
}

void Log::LogError(const std::string& message, const char* funcName, const char* fileName,	const int32_t line)
{
	ForwardLog(CreateLogData(LogLevel::ERROR, message, funcName, fileName, line));
}

void Log::LogFatal(const std::string& message, const char* funcName, const char* fileName, const int32_t line)
{
	ForwardLog(CreateLogData(LogLevel::FATAL, message, funcName, fileName, line));
}

inline LogData Log::CreateLogData(const LogLevel level, const std::string& message,
	const char* funcName, const char* fileName, const int32_t line)
{
	time_t t = std::time(nullptr);
	tm tm;
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d/%m/%Y %H-%M-%S");

	return LogData(level, message, funcName, fileName, line, oss.str());
}

void Log::ForwardLog(const LogData& data)
{
	m_QueuedMessages.Push(data);
	m_CondVar.notify_one();
}

std::string Log::FormatText(const LogData& data)
{
	const size_t offset = std::string(data.File).find_last_of('\\');
	const std::string shortFilename = std::string(data.File).substr(offset + 1);

	const std::string text = std::string("[").append(data.Date).append("] ")
		.append(Log::GetLogLevelString(data.Level)).append(" : ").append(shortFilename)
		.append(" (").append(std::to_string(data.Line)).append(")")
		.append(" in ").append(data.Function)
		.append(" : ").append(data.Message).append("\n");

	return text;
}

std::string Log::FormatText(const LogLevel level, const std::string& date, const std::string& message, const char* funcName, const char* fileName, const int32_t line)
{
	// {type} : {fileName} ({line}) in {funcName} : 

	// TODO relative path
	const size_t offset = std::string(fileName).find_last_of('\\');
	const std::string shortFilename = std::string(fileName).substr(offset + 1);

	const std::string text = std::string("[").append(date).append("] ")
		.append(GetLogLevelString(level)).append(" : ").append(shortFilename)
		.append(" (").append(std::to_string(line)).append(")")
		.append(" in ").append(funcName)
		.append(" : ").append(message);

	return text;
}

static const char* const sLogLevelsStr[] = {
	"Trace",
	"Debug",
	"Info",
	"Warning",
	"Error",
	"Fatal"
};

const char* const Log::GetLogLevelString(const LogLevel level)
{
	return sLogLevelsStr[static_cast<size_t>(level)];
}
