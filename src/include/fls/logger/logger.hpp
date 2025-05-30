#ifndef FLS_LOGGER_LOGGER_HPP
#define FLS_LOGGER_LOGGER_HPP

#include "fls/std/string.hpp"

#ifdef NDEBUG
#define FLS_LOG_INTERNAL(...)    ;
#define FLS_LOG_MEMORY_READ(...) ;
#else

#define FLS_LOG_INTERNAL(...)    fastlanes::Logger::log_key_value(__VA_ARGS__);
#define FLS_LOG_MEMORY_READ(...) fastlanes::Logger::log_memory_read(__VA_ARGS__);

#endif

#define FLS_PLOG_KEY_VALUE(...)   FLS_LOG_INTERNAL(__FILE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define FLS_PLOG_MEMORY_READ(...) FLS_LOG_MEMORY_READ(__FILE__, __PRETTY_FUNCTION__, __VA_ARGS__)

namespace fastlanes {

class Logger {
public:
	~Logger() = default;

public:
	static void
	log_key_value(const string& file_name, const string& pretty_function, const string& key, const string& val);

	static void log_memory_read(const string& file_name, const string& pretty_function, const void* arr);
};

} // namespace fastlanes
#endif