#ifndef FLS_PRINTER_COLOR_HPP
#define FLS_PRINTER_COLOR_HPP

#include <cstdint>

namespace fastlanes::debug {
enum Code : uint32_t {
	FG_BLACK   = 30,
	FG_RED     = 31,
	FG_GREEN   = 32,
	FG_YELLOW  = 33,
	FG_BLUE    = 34,
	FG_MAGENTA = 35,
	FG_CYAN    = 36,
	FG_WHITE   = 37,
	FG_DEFAULT = 39,
	BG_RED     = 41,
	BG_GREEN   = 42,
	BG_BLUE    = 44,
	BG_DEFAULT = 49

};

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& reset(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_BLACK << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& black(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_BLACK << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& bold_black(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[1m\033[" << FG_BLACK << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& bold_blue(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[1m\033[" << FG_BLUE << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& red(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_RED << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& magenta(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_MAGENTA << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& yellow(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_YELLOW << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& def(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_DEFAULT << "m";
}

template <class CHAR_T, class TRAITS>
constexpr std::basic_ostream<CHAR_T, TRAITS>& green(std::basic_ostream<CHAR_T, TRAITS>& os) {
	return os << "\033[" << FG_GREEN << "m";
}
} // namespace fastlanes::debug
#endif // FLS_PRINTER_COLOR_HPP
