#ifndef FLS_COMMON_COMMON_HPP
#define FLS_COMMON_COMMON_HPP

#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/common/macros.hpp"

// #include "fls/debug/debug.hpp"  // TODO : include it.

namespace fastlanes {
/*---------------------------------------------------------------------------------------------------------------------\
 * VECTOR_SZ:
\---------------------------------------------------------------------------------------------------------------------*/
constexpr n_t vec_n_tup() { return 1024; }

template <typename T>
constexpr n_t vec_bsz() {
	return sizeof(T) * 1024;
}

constexpr n_t vec_sz() { return 1024; }
constexpr n_t vec_sz_1bit() { return 1024 / 8; }

static_assert(vec_sz_1bit() == 128);
static_assert(vec_bsz<int64_t>() == 8UL * 1024);
static_assert(vec_sz() == 1024);

/*---------------------------------------------------------------------------------------------------------------------\
 * runtime errors:
\---------------------------------------------------------------------------------------------------------------------*/
constexpr const auto* UNREACHABLE_MESSAGE = "UNREACHABLE";
#define FLS_UNREACHABLE()                                                                                              \
	do {                                                                                                               \
		FLS_ABORT(UNREACHABLE_MESSAGE)                                                                                 \
		throw std::runtime_error(UNREACHABLE_MESSAGE);                                                                 \
	} while (0);

constexpr const auto* IMPLEMENT_THIS_MESSAGE = "IMPLEMENT_THIS_MESSAGE";
#define FLS_IMPLEMENT_THIS()                                                                                           \
	do {                                                                                                               \
		FLS_ABORT(IMPLEMENT_THIS_MESSAGE)                                                                              \
		throw std::runtime_error(IMPLEMENT_THIS_MESSAGE);                                                              \
	} while (0);

} // namespace fastlanes
#endif // FLS_COMMON_COMMON_HPP
