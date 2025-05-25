#ifndef FLS_COMMON_COMMON_HPP
#define FLS_COMMON_COMMON_HPP

#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/macros.hpp"
#include <string>
#include <typeinfo>

#ifdef __GNUG__
#include <cxxabi.h>
#endif

// todo {clang-tidy}
// NOLINTBEGIN

namespace fastlanes {
/*---------------------------------------------------------------------------------------------------------------------\
 * VECTOR_SZ:
\---------------------------------------------------------------------------------------------------------------------*/
constexpr n_t vec_n_tup() {
	return 1024;
}

template <typename T>
constexpr n_t vec_bsz() {
	return sizeof(T) * 1024;
}

constexpr n_t vec_sz() {
	return 1024;
}
constexpr n_t vec_sz_1bit() {
	return 1024 / 8;
}

static_assert(vec_sz_1bit() == 128);
static_assert(vec_bsz<int64_t>() == 8UL * 1024);
static_assert(vec_sz() == 1024);

/*---------------------------------------------------------------------------------------------------------------------\
 * runtime errors:
\---------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* UNREACHABLE_MESSAGE = "UNREACHABLE";
#define FLS_UNREACHABLE()                                                                                              \
	do {                                                                                                               \
		constexpr auto msg = UNREACHABLE_MESSAGE;                                                                      \
		FLS_ABORT(msg);                                                                                                \
		throw std::runtime_error(std::string(msg) + " at " + __FILE__ + ":" + std::to_string(__LINE__));               \
	} while (0);

constexpr const auto* IMPLEMENT_THIS_MESSAGE = "IMPLEMENT_THIS_MESSAGE";
#define FLS_IMPLEMENT_THIS()                                                                                           \
	do {                                                                                                               \
		constexpr auto msg = IMPLEMENT_THIS_MESSAGE;                                                                   \
		FLS_ABORT(msg)                                                                                                 \
		throw std::runtime_error(msg);                                                                                 \
	} while (0);

// Demangle for GCC/Clang; fallback to raw name otherwise.
inline std::string demangle(const char* name) {
#ifdef __GNUG__
	int   status    = 0;
	char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);
	if (status == 0 && demangled != nullptr) {
		std::string ret(demangled);
		std::free(demangled);
		return ret;
	}
#endif
	return name; // fallback if demangling not available
}

// Generic function to get a (demangled) type name
template <typename T>
inline std::string type_name() {
	return demangle(typeid(T).name());
}

#define FLS_UNREACHABLE_WITH_TYPE(arg)                                                                                 \
	do {                                                                                                               \
		using T  = std::decay_t<decltype(arg)>;                                                                        \
		auto msg = "[FLS] UNREACHABLE with unexpected type: " + type_name<T>() + " at " + __FILE__ + ":" +             \
		           std::to_string(__LINE__);                                                                           \
		FLS_ABORT(msg.c_str())                                                                                         \
		throw std::runtime_error(msg);                                                                                 \
	} while (0);

#define FLS_UNREACHABLE_WITH_TYPES(arg1, arg2)                                                                         \
	do {                                                                                                               \
		using T1 = std::decay_t<decltype(arg1)>;                                                                       \
		using T2 = std::decay_t<decltype(arg2)>;                                                                       \
		auto msg = "[FLS] UNREACHABLE with unexpected types: " + type_name<T1>() + " and " + type_name<T2>() +         \
		           " at " + __FILE__ + ":" + std::to_string(__LINE__);                                                 \
		FLS_ABORT(msg.c_str())                                                                                         \
		throw std::runtime_error(msg);                                                                                 \
	} while (0);

} // namespace fastlanes
#endif // FLS_COMMON_COMMON_HPP

// NOLINTEND