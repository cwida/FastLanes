#include "fls/common/assert.hpp"
#include <cassert>
#include <cstdlib>  // for abort
#include <iostream> // for operator<<, char_traits, basic_ostream, cerr

namespace fastlanes {

void FlsAssert(const char* expr_str, const char* str, bool expr, const char* file, int line, const char* msg) {
	if (expr) {
		return;
	}
	std::cerr << "Failed:\t\t" << msg << "\n"
	          << "Exprsn:\t\t" << expr_str << "\n"
	          << "Values:\t\t" << str << "\n"
	          << file << ":" << line << "\n";
	abort();
}

void DetailedFlsAssert(const char* expr_str, const char* str, bool expr, const char* file, int line, const char* msg) {
	if (expr) {
		return;
	}
	std::cerr << "Failed:\t\t" << msg << "\n"
	          << "Exprsn:\t\t" << expr_str
	          << "\n"
	          // << "Values:\t\t" << fmt::format("{}", str) << "\n" //TODO[FMT]
	          << file << ":" << line << "\n";
	abort();
}

void Assert::NotNullPointer(const void* p) {
	assert(p != nullptr && "Pointer must not be null");
}

void Assert::CorrectBW(uint64_t bw) {
	assert(bw <= 64 && "BW must be greater than zero");
}
} // namespace fastlanes
