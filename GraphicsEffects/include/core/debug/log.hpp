#pragma once

#include <string>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>

#include "core/debug/ILogger.hpp"
#include "core/debug/log_data.hpp"

#include "core/data_structures/tsqueue.hpp"

// Constraint for a generic of type ILogger
template<class T>
concept LoggerClass = std::is_base_of<ILogger, T>::value;

/// <summary>
/// Generic static logger class, classes of type ILogger can be binded to it allowing for the creation of custom loggers.
/// The loggers bound are automatically free'd and their lifetime should be either the same as the application or for as long as they're bound.
/// </summary>
class Log
{
private:
	static std::vector<ILogger*> m_Loggers;

	// Thread variables
	static std::thread m_Thread;
	static std::condition_variable m_CondVar;
	static TsQueue<LogData> m_QueuedMessages;
	static std::mutex m_Mutex;
	static bool m_Running;

	static inline LogData CreateLogData(const LogLevel level, const std::string& message,
		const char* funcName, const char* fileName, const int32_t line);

	static void ForwardLog(const LogData& data);

	static void Run();

public:
	static void Init();
	static void Stop();

	/// <summary>
	/// Adds a logger to the internal logger list
	/// </summary>
	/// <param name="logger">Logger</param>
	static void AddLogger(ILogger* const logger);

	/// <summary>
	/// Adds a logger to the internal logger list
	/// </summary>
	/// <typeparam name="T">Logger type (must derive from ILogger)</typeparam>
	/// <returns>The created logger</returns>
	template<LoggerClass T>
	static ILogger* AddLogger()
	{
		ILogger* const logger = new T();
		m_Loggers.push_back(logger);

		return logger;
	}

	/// <summary>
	/// Removes a logger from the interal logger list
	/// </summary>
	/// <param name="logger">Logger to remove</param>
	/// <param name="freeMem">Whether delete should be called on the removed logger (true by default)</param>
	static void RemoveLogger(ILogger* const logger, const bool freeMem = true);

	/// <summary>
	/// Logs an info
	/// </summary>
	/// <param name="message">Message</param>
	/// <param name="funcName">Function name, LEAVE DEFAULT</param>
	/// <param name="fileName">File name, LEAVE DEFAULT</param>
	/// <param name="line">Line, LEAVE DEFAULT</param>
	static void LogInfo(const std::string& message,
		const char* funcName = __builtin_FUNCTION(),
		const char* fileName = __builtin_FILE(),
		const int32_t line = __builtin_LINE());

	/// <summary>
	/// Logs a warning
	/// </summary>
	/// <param name="message">Message</param>
	/// <param name="funcName">Function name, LEAVE DEFAULT</param>
	/// <param name="fileName">File name, LEAVE DEFAULT</param>
	/// <param name="line">Line, LEAVE DEFAULT</param>
	static void LogWarning(const std::string& message,
		const char* funcName = __builtin_FUNCTION(),
		const char* fileName = __builtin_FILE(),
		const int32_t line = __builtin_LINE());

	/// <summary>
	/// Logs an error
	/// </summary>
	/// <param name="message">Message</param>
	/// <param name="funcName">Function name, LEAVE DEFAULT</param>
	/// <param name="fileName">File name, LEAVE DEFAULT</param>
	/// <param name="line">Line, LEAVE DEFAULT</param>
	static void LogError(const std::string& message,
		const char* funcName = __builtin_FUNCTION(),
		const char* fileName = __builtin_FILE(),
		const int32_t line = __builtin_LINE());

	/// <summary>
	/// Logs a fatal error
	/// </summary>
	/// <param name="message">Message</param>
	/// <param name="funcName">Function name, LEAVE DEFAULT</param>
	/// <param name="fileName">File name, LEAVE DEFAULT</param>
	/// <param name="line">Line, LEAVE DEFAULT</param>
	static void LogFatal(const std::string& message,
		const char* funcName = __builtin_FUNCTION(),
		const char* fileName = __builtin_FILE(),
		const int32_t line = __builtin_LINE());

	/// <summary>
	/// Converts the log level enum to its string counterpart
	/// </summary>
	/// <param name="level">Log level</param>
	/// <returns>Strnig representation</returns>
	_NODISCARD static const char* const GetLogLevelString(const LogLevel level);
	
	/// <summary>
	/// Formats a log text
	/// </summary>
	/// <param name="level">Log level</param>
	/// <param name="message">Message</param>
	/// <param name="funcName">Function name</param>
	/// <param name="fileName">File name</param>
	/// <param name="line">Line</param>
	/// <returns>Formatted text</returns>
	_NODISCARD static std::string FormatText(const LogLevel level,
		const std::string& date,
		const std::string& message,
		const char* funcName,
		const char* fileName,
		const int32_t line);

	/// <summary>
	/// Formats a log text
	/// </summary>
	/// <param name="data">Log data</param>
	/// <returns></returns>
	_NODISCARD static std::string FormatText(const LogData& data);
};
