#pragma once

#include "Tesla/Core/Base.h"
#include "Tesla/Core/Log.h"

#ifdef TL_ENABLE_ASSERTS

namespace Tesla::Assert
{
	// Returns the simple file name rather than full path as suggested by LovelySanta
	constexpr const char* CurrentFileName(const char* path) {
		const char* file = path;
		while (*path)
		{
			if (*path == '/' || *path == '\\')
				file = ++path;
			else
				path++;
		}
		return file;
	}
}

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define TL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { TL##type##ERROR(msg, __VA_ARGS__); TL_DEBUGBREAK(); } }
#define TL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) TL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define TL_INTERNAL_ASSERT_NO_MSG(type, check) TL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", TL_STRINGIFY_MACRO(check), ::Tesla::Assert::CurrentFileName(__FILE__), __LINE__)

#define TL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define TL_INTERNAL_ASSERT_GET_MACRO(...) TL_EXPAND_MACRO( TL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, TL_INTERNAL_ASSERT_WITH_MSG, TL_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define TL_ASSERT(...) TL_EXPAND_MACRO( TL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define TL_CORE_ASSERT(...) TL_EXPAND_MACRO( TL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define TL_ASSERT(...)
#define TL_CORE_ASSERT(...)
#endif