// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/printer/to_str.cpp
// ────────────────────────────────────────────────────────
#include "fls/utl/to_str.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/std/string.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <type_traits> // for std::is_same

namespace fastlanes {

template <typename T>
string print_arr(const T* p, n_t c) {
	if constexpr (std::is_same<T, bool>()) {
		FLS_ABORT("Not Supported")
	} else {
		std::stringstream ss;
		ss << "[";
		for (n_t i {0}; i < c; ++i) {
			ss << std::to_string(p[i]);
			if (i != c - 1) {
				ss << " ";
			};
		}
		ss << "]";
		return ss.str();
	}
	return {};
}

template <typename T>
string ToStr::to_str(T* p) {
	return print_arr<T>(reinterpret_cast<T*>(p), CFG::LOG::MAX);
}

template <typename T>
string ToStr::to_str(T* p, n_t c) {
	return print_arr<T>(reinterpret_cast<T*>(p), c);
}

template <>
string ToStr::to_str(void* p) {
	auto              typed_p = reinterpret_cast<uint64_t*>(p);
	std::stringstream ss;
	ss << "0x ";
	for (n_t i {0}; i < 16; ++i) {
		ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << typed_p[i] << " ";
	}
	return ss.str();
}

string ToStr::to_hex(uint8_t* p, n_t c) {
	std::stringstream ss;
	ss << "0x ";
	for (n_t i {0}; i < c; ++i) {
		ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << +p[i] << " ";
	}
	return ss.str();
}

template <typename T>
string ToStr::to_str(T val) {
	std::stringstream ss;
	ss << val;
	return ss.str();
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
// clang-format off
template string ToStr::to_str<uint8_t>(uint8_t *p);
template string ToStr::to_str<uint16_t>(uint16_t *p);
template string ToStr::to_str<uint32_t>(uint32_t *p);
template string ToStr::to_str<uint64_t>(uint64_t *p);
template string ToStr::to_str<int8_t>(int8_t *p);
template string ToStr::to_str<int16_t>(int16_t *p);
template string ToStr::to_str<int32_t>(int32_t *p);
template string ToStr::to_str<int64_t>(int64_t *p);
template string ToStr::to_str<float>(float *p);
template string ToStr::to_str<double>(double *p);
template string ToStr::to_str<bool>(bool *p);


template string ToStr::to_str<uint8_t>(uint8_t *p, n_t c);
template string ToStr::to_str<uint16_t>(uint16_t *p, n_t c);
template string ToStr::to_str<uint32_t>(uint32_t *p, n_t c);
template string ToStr::to_str<uint64_t>(uint64_t *p, n_t c);
template string ToStr::to_str<int8_t>(int8_t *p, n_t c);
template string ToStr::to_str<int16_t>(int16_t *p, n_t c);
template string ToStr::to_str<int32_t>(int32_t *p, n_t c);
template string ToStr::to_str<int64_t>(int64_t *p, n_t c);
template string ToStr::to_str<float>(float *p, n_t c);
template string ToStr::to_str<double>(double *p, n_t c);
template string ToStr::to_str<bool>(bool *p, n_t c);

template string ToStr::to_str<uint16_t>(uint16_t val);


} // namespace fastlanes
