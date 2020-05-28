#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"

namespace Axel {
	class AXEL_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLoggger() { return m_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLoggger() { return m_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> m_coreLogger;
		static std::shared_ptr<spdlog::logger> m_clientLogger;
	};
}

// Core log macros
#define AX_CORE_CRITICAL(...)  ::Axel::Log::getCoreLoggger()->critical(__VA_ARGS__)
#define AX_CORE_ERROR(...)     ::Axel::Log::getCoreLoggger()->error(__VA_ARGS__)
#define AX_CORE_WARN(...)      ::Axel::Log::getCoreLoggger()->warn(__VA_ARGS__)


// Client log macros
#define AX_CRITICAL(...)	   ::Axel::Log::getClientLoggger()->critical(__VA_ARGS__)
#define AX_ERROR(...)          ::Axel::Log::getClientLoggger()->error(__VA_ARGS__)
#define AX_WARN(...)           ::Axel::Log::getClientLoggger()->warn(__VA_ARGS__)

// Only available in debug mode
#ifdef AX_ENABLE_DEBUG_LOG
	#define AX_CORE_INFO(...)      ::Axel::Log::getCoreLoggger()->info(__VA_ARGS__)
	#define AX_CORE_TRACE(...)     ::Axel::Log::getCoreLoggger()->trace(__VA_ARGS__)

	#define AX_INFO(...)           ::Axel::Log::getClientLoggger()->info(__VA_ARGS__)
	#define AX_TRACE(...)          ::Axel::Log::getClientLoggger()->trace(__VA_ARGS__)
#else
	#define AX_CORE_INFO(...)
	#define AX_CORE_TRACE(...)
	
	#define AX_INFO(...)
	#define AX_TRACE(...)
#endif // AX_ENABLE_DEBUG_LOG