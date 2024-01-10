#pragma once

#include <stdint.h>

namespace Assert
{
	/// <summary>
	/// Asserts that a condition is true
	/// </summary>
	/// <param name="condition">Condition</param>
	/// <param name="message">Error message</param>
	/// <param name="funcName">Caller function name</param>
	/// <param name="fileName">Caller function file name</param>
	/// <param name="line">Caller function line</param>
	void IsTrue(const bool condition, const char* const message,
		const char* funcName = __builtin_FUNCTION(),
		const char* fileName = __builtin_FILE(),
		const int32_t line = __builtin_LINE());
};
