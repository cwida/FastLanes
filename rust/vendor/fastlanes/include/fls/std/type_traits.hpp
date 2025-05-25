#ifndef FLS_STD_TYPE_TRAITS_HPP
#define FLS_STD_TYPE_TRAITS_HPP

#include <type_traits>

namespace fastlanes {
using std::is_same_v;
using std::make_signed_t;
using std::make_unsigned_t;

template <typename T>
struct make_fls_unsigned {
	using type = std::make_unsigned_t<T>;
};

// Specialization for double
template <>
struct make_fls_unsigned<double> {
	using type = uint64_t;
};

// Helper alias
template <typename T>
using make_fls_unsigned_t = typename make_fls_unsigned<T>::type;

static_assert(std::is_same_v<make_fls_unsigned_t<int>, unsigned int>, "int -> unsigned int");
static_assert(std::is_same_v<make_fls_unsigned_t<double>, uint64_t>, "double -> uint64_t");
static_assert(std::is_same_v<make_fls_unsigned_t<unsigned int>, unsigned int>, "unsigned int remains unsigned");

template <typename T>
struct make_fls_unsigned_back {
	using type = std::make_signed_t<T>;
};

// Specialization for double
template <>
struct make_fls_unsigned_back<double> {
	using type = uint64_t;
};

// Helper alias for make_fls_signed
template <typename PT>
using make_fls_unsigned_back_t = typename make_fls_unsigned_back<PT>::type;

// Static assertions for make_fls_signed
static_assert(std::is_same_v<make_fls_unsigned_back_t<unsigned int>, int>, "unsigned int -> int");
static_assert(std::is_same_v<make_fls_unsigned_back_t<int>, int>, "int remains signed");
static_assert(std::is_same_v<make_fls_unsigned_back_t<double>, uint64_t>, "double -> int64_t");

} // namespace fastlanes

#endif // FLS_STD_TYPE_TRAITS_HPP
