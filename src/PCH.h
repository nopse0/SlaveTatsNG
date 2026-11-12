#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <SimpleIni.h>
//#include <SKSEMenuFramework.h>
#include <spdlog/pattern_formatter.h>
//#ifndef _Windows_
//	#define _Windows_
//#endif
//#include "FrontierAPI.h"
#include <latch>
#include <gsl/util>

using namespace std::string_view_literals;

namespace slavetats_ng
{
	typedef bool fail_t;
}

// Set on fatal errors, e.g. if I can't load my Forms from the .esp
//inline bool ModDisabled = false;

//inline FrontierAPI::IFrontier1* Frontier1 = nullptr;

#define MAKE_DEFAULT_LOGGER(a_func, a_level_val)                                              \
                                                                                      \
	template <class... Args>                                                          \
	struct [[maybe_unused]] a_func                                                    \
	{                                                                                 \
		a_func() = delete;                                                            \
                                                                                      \
		explicit a_func(                                                              \
			/*spdlog::level::level_enum a_level,*/                                    \
			fmt::format_string<Args...> a_fmt,                                        \
			Args&&... a_args,                                                         \
			std::source_location a_loc = std::source_location::current()) \
		{                                                                             \
			auto logger = spdlog::default_logger();                                   \
			if (logger && logger->should_log(a_level_val)) {                          \
				spdlog::log(                                                          \
					spdlog::source_loc{                                               \
						a_loc.file_name(),                                            \
						static_cast<int>(a_loc.line()),                               \
						a_loc.function_name() },                                      \
					a_level_val,                                                      \
					a_fmt,                                                            \
					std::forward<Args>(a_args)...);                                   \
			}                                                                         \
		}                                                                             \
	};                                                                                \
                                                                                      \
	template <class... Args>                                                          \
	a_func(fmt::format_string<Args...>, Args&&...) -> a_func<Args...>;

namespace logger
{
	MAKE_DEFAULT_LOGGER(info, spdlog::level::info);
	MAKE_DEFAULT_LOGGER(error, spdlog::level::err);
	MAKE_DEFAULT_LOGGER(debug, spdlog::level::debug);
	MAKE_DEFAULT_LOGGER(trace, spdlog::level::trace);
	MAKE_DEFAULT_LOGGER(warn, spdlog::level::warn);
	MAKE_DEFAULT_LOGGER(critical, spdlog::level::critical);
}


#define MAKE_CUSTOM_LOGGER(a_func, a_logger_name, a_level_val)              \
                                                                                      \
	template <class... Args>                                                          \
	struct [[maybe_unused]] a_func                                                    \
	{                                                                                 \
		a_func() = delete;                                                            \
                                                                                      \
		explicit a_func(                                                              \
			fmt::format_string<Args...> a_fmt,                                        \
			Args&&... a_args,                                                         \
			std::source_location a_loc = std::source_location::current())             \
		{                                                                             \
			auto logger = spdlog::get(a_logger_name);                                 \
			if (logger && logger->should_log(a_level_val)) {                          \
				logger->log(                                                          \
					spdlog::source_loc{                                               \
						a_loc.file_name(),                                            \
						static_cast<int>(a_loc.line()),                               \
						a_loc.function_name() },                                      \
					a_level_val,                                                      \
					a_fmt,                                                            \
					std::forward<Args>(a_args)...);                                   \
			}                                                                         \
		}                                                                             \
	};                                                                                \
                                                                                      \
	template <class... Args>                                                          \
	a_func(fmt::format_string<Args...>, Args&&...) -> a_func<Args...>;


#define INIT_CUSTOM_LOGGER(a_logger_name)\
inline void init_logger() {\
	auto logger = spdlog::get(a_logger_name);\
	if (!logger) {\
		auto def_logger = spdlog::default_logger();                           \
		if (def_logger) {													  \
			logger = std::make_shared<spdlog::logger> (                       \
				a_logger_name,                                                \
				def_logger->sinks().begin(),                                  \
				def_logger->sinks().end());									  \
				spdlog::initialize_logger(logger); 							  \
				logger->flush_on(spdlog::level::debug);		                  \
		}\
	}\
}

/*
#define MINIUTILS_CUSTOM_LOGGER_SHOULD_LOG(a_logger_name)\
inline bool should_log(spdlog::level::level_enum a_level_val) {\
	auto logger = spdlog::get(a_logger_name);\
	if (!logger) return false;\
	return logger->should_log(a_level_val);\
}

namespace event_chain {
	namespace logger_custom {
		MINIUTILS_INIT_CUSTOM_LOGGER("event_chain")
		MINIUTILS_MAKE_CUSTOM_LOGGER(error, "event_chain", spdlog::level::err);
		MINIUTILS_MAKE_CUSTOM_LOGGER(debug, "event_chain", spdlog::level::debug);
		MINIUTILS_CUSTOM_LOGGER_SHOULD_LOG("event_chain")
	}
}

namespace fsm {
	namespace logger_custom {
		MINIUTILS_INIT_CUSTOM_LOGGER("fsm")
		MINIUTILS_MAKE_CUSTOM_LOGGER(trace, "fsm", spdlog::level::trace);
		MINIUTILS_MAKE_CUSTOM_LOGGER(debug, "fsm", spdlog::level::debug);
		MINIUTILS_CUSTOM_LOGGER_SHOULD_LOG("fsm");
	}
}

namespace animation {
	namespace logger_custom {
		MINIUTILS_INIT_CUSTOM_LOGGER("animation")
		MINIUTILS_MAKE_CUSTOM_LOGGER(debug, "animation", spdlog::level::debug);
		MINIUTILS_MAKE_CUSTOM_LOGGER(trace, "animation", spdlog::level::trace);
	}
}

namespace controller {
	namespace logger_custom {
		MINIUTILS_INIT_CUSTOM_LOGGER("controller")
		MINIUTILS_MAKE_CUSTOM_LOGGER(debug, "controller", spdlog::level::debug);
		MINIUTILS_MAKE_CUSTOM_LOGGER(trace, "controller", spdlog::level::trace);
	}
}

namespace scanner {
	namespace logger_custom {
		MINIUTILS_INIT_CUSTOM_LOGGER("scanner")
		MINIUTILS_MAKE_CUSTOM_LOGGER(debug, "scanner", spdlog::level::debug);
		MINIUTILS_MAKE_CUSTOM_LOGGER(trace, "scanner", spdlog::level::trace);
	}
}
*/

namespace skse {
	using SKSE::stl::report_and_fail;
}

[[noreturn]] inline void FatalerAssertAbsturz(
	const char* expressionText,
	const std::source_location& loc = std::source_location::current()) // Holt die Position des Aufrufers [2]
{
	// 1. Wir bauen eine extrem detaillierte Fehlermeldung
	std::string crashMeldung = std::format(
		"Assertion failed: ({}) in File: {}:{} ({})",
		expressionText,
		loc.file_name(),
		loc.line(),
		loc.function_name()
	);

	// 2. Unbedingt ins eigene Plugin-Log spiegeln
	logger::critical("{}", crashMeldung);

	// 3. Übergabe an Windows SEH für den Crash Logger SSE
	// Wir kopieren den String in den Heap, damit der Zeiger im Dump garantiert gültig bleibt
	char* permanentMessage = _strdup(crashMeldung.c_str());

	ULONG_PTR args[2];
	args[0] = 0xDEADC0DE;                          // Unser Plugin-Marker
	args[1] = reinterpret_cast<ULONG_PTR>(permanentMessage); // Die detaillierte Nachricht

	RaiseException(
		0xE0000001,
		EXCEPTION_NONCONTINUABLE,
		2,
		args
	);
}

// Das Makro, das die Condition prüft und lesbar macht
#define release_assert(expression) \
    do { \
        if (!(expression)) { \
            FatalerAssertAbsturz(#expression); \
        } \
    } while (0)




template <typename T>
class singleton {
public:
	static T& get_instance() {
		static T instance;
		return instance;
	}

	// Kopieren und Zuweisen strikt verbieten
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;
	singleton(singleton&&) = delete;
	singleton& operator=(singleton&&) = delete;

protected:
	singleton() = default;
	virtual ~singleton() = default;
};
