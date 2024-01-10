#include "core/debug/assert.hpp"
#include "core/debug/log.hpp"
#include <stdexcept>
#include <stacktrace>
#include <iostream>

void Assert::IsTrue(const bool condition, const char* const message,
	const char* funcName,
	const char* fileName,
	const int32_t line)
{
	if (condition)
		return;

#ifdef NDEBUG
	throw std::runtime_error("Assertion fail");
#else
	/*
	// Fire brk interrupt
	__asm {
		int 3
	};
	*/
	__debugbreak();
#endif

}
