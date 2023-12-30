#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>

namespace Hazel {
	class HAZEL_API Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};

}
// ...是接受函数参数包，__VA_ARGS__转发函数参数包
#define HZ_CORE_TRACE(...)    ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)     ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)     ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)    ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define HZ_CORE_FATAL(...)    ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__) 

// Client log macros
#define HZ_TRACE(...)	      ::Hazel::Log::GetAppLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)	      ::Hazel::Log::GetAppLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)	      ::Hazel::Log::GetAppLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)	      ::Hazel::Log::GetAppLogger()->error(__VA_ARGS__)
//#define HZ_FATAL(...)	      ::Hazel::Log::GetAppLogger()->fatal(__VA_ARGS__)
