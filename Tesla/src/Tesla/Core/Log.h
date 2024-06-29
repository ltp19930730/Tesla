#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


namespace Tesla {

	class TL_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}


#define TL_CORE_TRACE(...)      ::Tesla::Log::getCoreLogger()->trace(__VA_ARGS__);
#define TL_CORE_INFO(...)       ::Tesla::Log::getCoreLogger()->info(__VA_ARGS__);
#define TL_CORE_WARN(...)       ::Tesla::Log::getCoreLogger()->warn(__VA_ARGS__);
#define TL_CORE_ERROR(...)      ::Tesla::Log::getCoreLogger()->error(__VA_ARGS__);
#define TL_CORE_CRITICAL(...)   ::Tesla::Log::getCoreLogger()->critical(__VA_ARGS__);

#define TL_TRACE(...)      ::Tesla::Log::getClientLogger()->trace(__VA_ARGS__);
#define TL_INFO(...)       ::Tesla::Log::getClientLogger()->info(__VA_ARGS__);
#define TL_WARN(...)       ::Tesla::Log::getClientLogger()->warn(__VA_ARGS__);
#define TL_ERROR(...)      ::Tesla::Log::getClientLogger()->error(__VA_ARGS__);
#define TL_CRITICAL(...)   ::Tesla::Log::getClientLogger()->critical(__VA_ARGS__);