#pragma once

#include <memory>

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
//#define AX_CORE_FATAL(...) ::Axel::Log::getClientLoggger()->fatal(__VA_ARGS__)
#define AX_CORE_ERROR(...)     ::Axel::Log::getCoreLoggger()->error(__VA_ARGS__)
#define AX_CORE_WARN(...)      ::Axel::Log::getCoreLoggger()->warn(__VA_ARGS__)
#define AX_CORE_INFO(...)      ::Axel::Log::getCoreLoggger()->info(__VA_ARGS__)
#define AX_CORE_TRACE(...)     ::Axel::Log::getCoreLoggger()->trace(__VA_ARGS__)

// Client log macros
#define AX_ERROR(...)          ::Axel::Log::getClientLoggger()->error(__VA_ARGS__)
#define AX_WARN(...)           ::Axel::Log::getClientLoggger()->warn(__VA_ARGS__)
#define AX_INFO(...)           ::Axel::Log::getClientLoggger()->info(__VA_ARGS__)
#define AX_TRACE(...)          ::Axel::Log::getClientLoggger()->trace(__VA_ARGS__)
