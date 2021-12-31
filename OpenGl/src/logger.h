#pragma once
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class logger {
public:
	void static Init() {

		spdlog::set_pattern("%n%v%$");
		s_CoreLogger = spdlog::stdout_color_mt(" ");
		s_CoreLogger->set_level(spdlog::level::trace);

	}

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
		return s_CoreLogger;
	}

	~logger() {
		
	}
private:

	static std::shared_ptr< spdlog::logger> s_CoreLogger;

};

std::shared_ptr<spdlog::logger> logger::s_CoreLogger;

