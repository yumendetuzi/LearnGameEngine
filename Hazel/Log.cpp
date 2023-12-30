#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

 std::shared_ptr<spdlog::logger> Hazel::Log::s_CoreLogger;
 std::shared_ptr<spdlog::logger> Hazel::Log::s_AppLogger;


namespace Hazel {

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T],%n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Hazel");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_AppLogger = spdlog::stdout_color_mt("App");
		s_AppLogger->set_level(spdlog::level::trace);
	}
}

