#include "fls/logger/logger.hpp"
#include "fls/printer/output.hpp"
#include "fls/printer/output_factory.hpp"

namespace fastlanes {

std::string prettify_function_name(const std::string& before_str) {
	auto       pos       = before_str.find('(');
	const auto after_str = before_str.substr(0, pos);

	pos = after_str.find(' ') + 1;
	return after_str.substr(pos, after_str.length());
}

std::string linkify(const std::string& link) {
	std::stringstream ss;
	ss << "[link]"
	   << "(" << link << ")";
	return ss.str();
}

template <typename T>
void log(const T& obj) {
	std::string result_file_path = CMAKE_SOURCE_DIR + std::string("/log/log.csv");

	static std::ofstream FILE {result_file_path};
	static Logger        LOGGER {FILE};
	LOGGER.Log(obj);
}

template <typename T>
void show(const T& obj) {
	static Logger LOGGER {std::cout};
	LOGGER.Log(obj);
}

void Logger::log_table(const std::string& file_name,
                       int                line,
                       const std::string& pretty_function,
                       const std::string& key,
                       const std::string& val) {
	const std::string result_file_path = CMAKE_SOURCE_DIR + std::string("/log/log.csv");

	static std::ofstream FILE {result_file_path};
	static auto          TABLE = OutputFactory::CreateCSV(FILE);

	TABLE->Add(prettify_function_name(pretty_function));
	TABLE->Add(key);
	TABLE->Add(val);
	/* #L does not work in CLION*/
	//	TXT_TAB.Add(linkify(file_name + "#L" + std::to_string(line)));
	TABLE->Add(linkify(file_name));
	TABLE->EndOfRow();
}
} // namespace fastlanes