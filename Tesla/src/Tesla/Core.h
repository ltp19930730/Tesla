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
