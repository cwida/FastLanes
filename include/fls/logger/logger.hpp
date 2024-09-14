#ifndef FLS_LOGGER_LOGGER_HPP
#define FLS_LOGGER_LOGGER_HPP

#include <fstream>
#include <iostream>
#include <sstream>

#ifdef NDEBUG
#define FLS_LOG_TABLE(...) ;
#else
#define FLS_LOG_TABLE(...) fastlanes::Logger::log_table(__VA_ARGS__);
#endif

#define FLS_LOG_TABLE_KEY_VALUE(...) FLS_LOG_TABLE(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)

namespace fastlanes {

class Logger {
public:
	~Logger() = default;

public:
	static void log_table(const std::string& file_name,
	                      int                line,
	                      const std::string& pretty_function,
	                      const std::string& key,
	                      const std::string& val);
	explicit Logger(std::ostream& out)
	    : out(out) {}
	std::ostream& out;
	template <typename T>
	void Log(const T& obj) {
		out << obj << std::endl;
	}
};

} // namespace fastlanes
#endif