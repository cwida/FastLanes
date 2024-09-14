#include "fls/cor/exp/hdr.hpp"
#include "fls/common/assert.hpp" // for FLS_ASSERT
#include <cassert>
#include <cstddef> // for byte
#include <string>  // for basic_string

namespace fastlanes::exp {
std::string Hdr::ToString() const {
	return "[VAL_O: " + std::to_string(val_o) + "COL_O: {}, " + std::to_string(col_o) + "FUN_O: {}, " +
	       std::to_string(fun_o) + "FUN_C: {}]" + std::to_string(fun_c);
}
std::string& Hdr::operator<<(std::string& lhs) {
	std::string rhs = "{}{}{}{}";
	//	duckdb_fmt::format(rhs, val_o, col_o, fun_o, fun_c);
	return lhs += rhs;
}

Hdr Hdr::Load(std::byte* p) {
	FLS_ASSERT_NOT_NULL_POINTER(p);
	return *(reinterpret_cast<Hdr*>(p));
}
Hdr Hdr::Load(uint8_t* p) {
	FLS_ASSERT_NOT_NULL_POINTER(p);

	return *(reinterpret_cast<Hdr*>(p));
}
} // namespace fastlanes::exp
