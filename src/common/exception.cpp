// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/common/exception.cpp
// ────────────────────────────────────────────────────────
#include "fls/common/exception.hpp"
#include "fls/expression/rpn.hpp"
#include "fls/std/string.hpp"
#include <sstream>

namespace fastlanes {
DetailedException::DetailedException(const string& msg, const char* file, int line) {
	std::ostringstream oss;
	oss << msg << " (" << file << ":" << line << ")";
	message = oss.str();
}

const char* DetailedException::what() const noexcept {
	return message.c_str();
}

[[noreturn]] void throw_detailed_exception(const string& msg, const char* file, int line) {
	throw DetailedException(msg, file, line);
}

ExpressionException::ExpressionException(const string& operator_name, const char* file, int line) {
	std::ostringstream oss;
	oss << operator_name << " is not supported (" << file << ":" << line << ")";
	message = oss.str();
}

const char* ExpressionException::what() const noexcept {
	return message.c_str();
}

[[noreturn]] void throw_not_supported_exception(const OperatorToken& operator_token, const char* file, int line) {
	throw ExpressionException(token_to_string(operator_token), file, line);
}
} // namespace fastlanes
