#ifndef FLS_PRINTER_OUTPUT_FACTORY_HPP
#define FLS_PRINTER_OUTPUT_FACTORY_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
class TerminalOutput;
class CsvOutput;
class TerminalOutput;

enum class table_mode { // NOLINT
	CSV      = 0,
	MARKDOWN = 1,
};

class OutputFactory {
public:
	OutputFactory() = delete; //
public:
	static up<TerminalOutput> CreateMKD(std::ostream& file_out); //
	static up<CsvOutput>      CreateCSV(std::ostream& file_out); //
	static up<TerminalOutput> CreateTerminal();                  //
};

} // namespace fastlanes
#endif // FLS_PRINTER_OUTPUT_FACTORY_HPP
