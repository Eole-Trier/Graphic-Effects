#include "core/debug/fatal_logger.hpp"
#include "core/debug/log.hpp"
#include "core/debug/assert.hpp"

void FatalLogger::Log(const LogData& data)
{
	if (data.Level != LogLevel::FATAL)
		return;

	const std::string text = Log::FormatText(data);

	m_File.write(text.c_str(), text.size());
	m_File.flush();

	Assert::IsTrue(false, "A fatal log has occured");
}
