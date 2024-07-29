#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
	#define TL_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
	#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define TL_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define TL_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define TL_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define TL_PLATFORM_LINUX
	#error "Linux is not supported!
#else/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef TL_DEBUG
	#if defined(TL_PLATFORM_WINDOWS)
		#define TL_DEBUGBREAK() __debugbreak()
	#elif defined(TL_PLATFORM_LINUX)
		#include <signal.h>
		#define TL_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define TL_ENABLE_ASSERTS
#else
#define HZ_DEBUGBREAK()
#endif

#ifdef TL_ENABLE_ASSERTS
#define TL_ASSERT(x, ...) { if(!(x)) { TL_ERROR("Assertion Failed: {0}", __VA_ARGS__); TL_DEBUGBREAK(); } }
#define TL_CORE_ASSERT(x, ...) { if(!(x)) { TL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); TL_DEBUGBREAK(); } }
#else
#define TL_ASSERT(x, ...)
#define TL_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define TL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Tesla {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}