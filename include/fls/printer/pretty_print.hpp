#ifndef FLS_DEBUG_PRETTY_PRINT_HPP
#define FLS_DEBUG_PRETTY_PRINT_HPP

#include "fls/logger/str_table.hpp"
#include "fls/std/string.hpp"
#include "fls/std/vector.hpp"
#include <cstdint>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*
 * BLUE = GPU
 * ERROR = RED
 * SHOW, LOG YELLOW
 * */

#include "fls/debug/color.hpp"

namespace fastlanes::debug {

class log {
public:
	///!
	template <typename T>
	static void print_vertical_arr(const void* raw, uint64_t from, uint64_t till);
	///!
	template <typename T>
	static void print_horizontal_arr(const void* raw, uint64_t from, uint64_t till);
	///!
	template <typename T, uint64_t N_COL, uint64_t N_ROW>
	static void print_table(T* raw);
	///!
	template <typename T>
	static void print_table(const T* in, uint64_t n_col, uint64_t n_row);
	///!
	static void print_table(const vector<string>& str_vec, const vector<uint64_t>& data_vec);
	///!
	static void print_table(const vector<string>& str_vec, const uint64_t* raw);
};

inline void log::print_table(const vector<string>& str_vec, const uint64_t* raw) {
	/**/
	StrTable str_table {};
	auto     n_col = str_vec.size();

	for (auto& str : str_vec) {
		str_table.Add(str);
	}
	str_table.EndOfRow();

	for (uint64_t col_idx {0}; col_idx < n_col; ++col_idx) {
		str_table.Add(std::to_string(raw[col_idx]) + " ");
	}

	str_table.EndOfRow();
}

template <typename T>
inline void log::print_table(const T* in, uint64_t n_col, uint64_t n_row) {
	const auto table = TableFac::CreateTerminal();

	for (uint64_t col_idx {0}; col_idx < n_col; ++col_idx) {
		table->Add(std::to_string(col_idx) + " ");
	}

	table->EndOfRow();

	for (uint64_t row_idx {0}, idx {0}; row_idx < n_row; ++row_idx) {
		for (uint64_t col_idx {0}; col_idx < n_col; ++col_idx, ++idx) {
			table->Add(std::to_string(in[idx]) + " ");
		}
	}

	table->EndOfRow();
	table->Print(std::cout);
}

inline void log::print_table(const vector<string>& str_vec, const vector<uint64_t>& data_vec) {
	FLS_ASSERT_E(str_vec.size(), data_vec.size())
	print_table(str_vec, data_vec.data());
}

template <typename T>
inline void log::print_vertical_arr(const void* raw, uint64_t from, uint64_t till) {
	auto* data = reinterpret_cast<T*>(raw);

	for (uint64_t idx = from; idx < till; ++idx) {
		std::cout << idx << " : " << std::to_string(data[idx]) << "\n";
	}
}

template <typename T>
inline void log::print_horizontal_arr(const void* raw, uint64_t from, uint64_t till) {
	auto* data = reinterpret_cast<T*>(raw);

	for (uint64_t idx = from; idx < till; ++idx) {
		std::cout << magenta << " | " << reset << std::to_string(data[idx]);
	}
	std::cout << " | \n";
}

template <typename T, uint64_t N_COL, uint64_t N_ROW>
inline void log::print_table(T* raw) {
	log::print_table(reinterpret_cast<void*>(raw), N_COL, N_ROW);
}

} // namespace fastlanes::debug

#define FLS_SHOW(a)                                                                                                    \
	std::cout << fastlanes::debug::yellow << "-- " << #a << ": " << (a) << fastlanes::debug::def << '\n';
#define FLS_LOG(m)     std::cout << fastlanes::debug::yellow << "-- " << m << fastlanes::debug::def << '\n';
#define FLS_CERR(a)    std::cout << fastlanes::debug::red << "-- " << #a << ": " << (a) << fastlanes::debug::def << '\n';
#define FLS_SUCCESS(m) std::cout << fastlanes::debug::green << "-- " << m << fastlanes::debug::def << '\n';
#define FLS_RESULT(m)  std::cout << fastlanes::debug::bold_blue << "-- " << m << fastlanes::debug::def << '\n';

#endif // FLS_DEBUG_PRETTY_PRINT_HPP
