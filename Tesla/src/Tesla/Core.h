#pragma once

#ifdef TL_PLATFORM_WINDOWS
	#ifdef TL_BUILD_DLL
		#define TL_API __declspec(dllexport)
	#else
		#define TL_API __declspec(dllimport)
	#endif
#else
	#error Tesla Engine only support windows!
#endif

#ifdef TL_ENABLE_ASSERTS
#define TL_ASSERT(x, ...) { if(!(x)) { TL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TL_CORE_ASSERT(x, ...) { if(!(x)) { TL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TL_ASSERT(x, ...)
#define TL_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define TL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)