#ifndef FLS_PRINTER_AZ_PRINTER_HPP
#define FLS_PRINTER_AZ_PRINTER_HPP

#include <cstdint>
#include <iostream>

namespace az_printer {
constexpr std::array<char32_t, 2> PRETTY_SYMBOL_TABLE {U'❌', U'✅'};
// Define ANSI escape codes for colors
namespace Color {
constexpr const char* RESET     = "\033[0m";
constexpr const char* BOLD      = "\033[1m";
constexpr const char* UNDERLINE = "\033[4m";

// Foreground colors
constexpr const char* BLACK   = "\033[30m";
constexpr const char* RED     = "\033[31m";
constexpr const char* GREEN   = "\033[32m";
constexpr const char* YELLOW  = "\033[33m";
constexpr const char* BLUE    = "\033[34m";
constexpr const char* MAGENTA = "\033[35m";
constexpr const char* CYAN    = "\033[36m";
constexpr const char* WHITE   = "\033[37m";
constexpr const char* DEFAULT = "\033[39m";

// Bold Foreground colors
constexpr const char* BOLD_BLACK   = "\033[1;30m";
constexpr const char* BOLD_RED     = "\033[1;31m";
constexpr const char* BOLD_GREEN   = "\033[1;32m";
constexpr const char* BOLD_YELLOW  = "\033[1;33m";
constexpr const char* BOLD_BLUE    = "\033[1;34m";
constexpr const char* BOLD_MAGENTA = "\033[1;35m";
constexpr const char* BOLD_CYAN    = "\033[1;36m";
constexpr const char* BOLD_WHITE   = "\033[1;37m";

// Background colors
constexpr const char* BG_RED     = "\033[41m";
constexpr const char* BG_GREEN   = "\033[42m";
constexpr const char* BG_YELLOW  = "\033[43m";
constexpr const char* BG_BLUE    = "\033[44m";
constexpr const char* BG_MAGENTA = "\033[45m";
constexpr const char* BG_CYAN    = "\033[46m";
constexpr const char* BG_WHITE   = "\033[47m";
constexpr const char* BG_DEFAULT = "\033[49m";

} // namespace Color

// Custom wrapper for colored output
class ColorStream {
public:
	explicit ColorStream(std::ostream& os, const char* color)
	    : m_os(os)
	    , m_color(color) {
	}

	template <typename T>
	ColorStream& operator<<(const T& value) {
		m_os << m_color << value << Color::RESET;
		return *this;
	}

	// Support manipulators (e.g., std::endl)
	ColorStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
		m_os << manip;
		return *this;
	}

private:
	std::ostream& m_os;
	const char*   m_color;
};

// Create instances for colored output streams
inline ColorStream green_cout(std::cout, Color::GREEN);
inline ColorStream yellow_cout(std::cout, Color::YELLOW);
inline ColorStream magenta_cout(std::cout, Color::MAGENTA);
inline ColorStream cyan_cout(std::cout, Color::CYAN);
inline ColorStream bold_red_cout(std::cout, Color::BOLD_RED);
inline ColorStream bold_blue_cout(std::cout, Color::BOLD_BLUE);
inline ColorStream bold_yellow_cout(std::cout, Color::BOLD_YELLOW);
inline ColorStream bold_magenta_cout(std::cout, Color::BOLD_MAGENTA);
inline ColorStream bold_cyan_cout(std::cout, Color::BOLD_CYAN);
inline ColorStream bold_green_cout(std::cout, Color::BOLD_GREEN);
//
inline ColorStream result_cout(std::cout, Color::BLUE);

// Colorizing functions
template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& magenta(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << Color::MAGENTA;
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& cyan(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << Color::CYAN;
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& bold_red(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << Color::BOLD_RED;
}
} // namespace az_printer

#endif // FLS_PRINTER_AZ_PRINTER_HPP
