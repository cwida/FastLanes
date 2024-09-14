#ifndef ALP_DEBUG_HPP
#define ALP_DEBUG_HPP

#include "mtd.hpp"
#include <bitset>
#include <cstdint>

namespace alp_debug {

template <typename T>
inline void print_binary_arr(T* in, size_t c, std::ostream& stream) {
	for (size_t i {0}; i < c; ++i) {
		stream << std::bitset<sizeof(T) * 8>(in[i]) << " | " << i << std::endl;
	}
}

template <typename T>
inline void print_arr(T* in, size_t c, std::ostream& stream) {
	stream << " ------------------- " << std::endl;
	for (size_t i {0}; i < c; ++i) {
		stream << i << " | " << in[i] << std::endl;
	}
}

template <typename T>
inline void print_arr(std::string_view message, T* in, size_t c, std::ostream& stream) {
	stream << message << " : ------------------- " << std::endl;
	for (size_t i {0}; i < c; ++i) {
		stream << i << " | " << in[i] << std::endl;
	}
}

template <typename T>
inline void print_arr_(std::string_view message, T* in, size_t c, std::ostream& stream) {
	stream << message << " : ------------------- " << std::endl;
	for (size_t i {0}; i < c; ++i) {
		stream << in[i] << " , ";
	}

	stream << std::endl;
}

inline void print(const std::vector<alp::metadata>& info_vec) {
	for (auto vec : info_vec) {
		vec.print_dict();
	}
}

inline void print_binary(uint16_t in, std::ostream& stream) { stream << std::bitset<16>(in) << std::endl; }
} // namespace alp_debug

#endif