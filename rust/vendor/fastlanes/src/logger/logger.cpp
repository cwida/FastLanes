#include "fls/logger/logger.hpp"
#include "fls/printer/output.hpp"
#include "fls/printer/output_factory.hpp"
#include <fstream>

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

TerminalOutput& init(const std::string& pretty_function) {
	const std::string result_file_path = FLS_CMAKE_SOURCE_DIR + std::string("/log/log.md");

	static std::ofstream FILE {result_file_path};
	static auto          TABLE = OutputFactory::CreateMKD(FILE);

	TABLE->Add(prettify_function_name(pretty_function));
	return *TABLE;
}

void finish(const std::string& file_name, TerminalOutput& table) {
	/* #L does not work in CLION*/
	//	TXT_TAB.Add(linkify(file_name + "#L" + std::to_string(line)));
	table.Add(linkify(file_name));
	table.EndOfRow();
}

void Logger::log_key_value(const std::string& file_name,
                           const std::string& pretty_function,
                           const std::string& key,
                           const std::string& val) {

	auto& table = init(pretty_function);

	table.Add(key);
	table.Add(val);
}

void Logger::log_memory_read(const string& file_name, const string& pretty_function, const void* arr) {

	auto& table = init(pretty_function);

	const auto* data = reinterpret_cast<const uint64_t*>(arr);

	table.Add(std::to_string(data[0]));
	table.Add(std::to_string(data[1]));

	finish(file_name, table);
}

} // namespace fastlanes