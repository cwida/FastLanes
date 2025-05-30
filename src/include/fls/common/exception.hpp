#ifndef FLS_COMMON_EXCEPTION_HPP
#define FLS_COMMON_EXCEPTION_HPP

#include "fls/std/string.hpp"
#include <cstdint>
#include <exception>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
enum class OperatorToken : uint16_t;
/*--------------------------------------------------------------------------------------------------------------------*/

class DetailedException final : public std::exception {
	std::string message;

public:
	DetailedException(const std::string& msg, const char* file, int line);

	[[nodiscard]] const char* what() const noexcept override;
};

// Function to throw a DetailedException
[[noreturn]] void
throw_detailed_exception(const std::string& msg, const char* file = __builtin_FILE(), int line = __builtin_LINE());

class ExpressionException final : public std::exception {
	std::string message;

public:
	ExpressionException(const std::string& operator_name, const char* file, int line);

	[[nodiscard]] const char* what() const noexcept override;
};

[[noreturn]] void throw_not_supported_exception(const OperatorToken& operator_token,
                                                const char*          file = __builtin_FILE(),
                                                int                  line = __builtin_LINE());

} // namespace fastlanes
#endif // FLS_COMMON_EXCEPTION_HPP
