#ifndef FLS_STD_VARIANT_HPP
#define FLS_STD_VARIANT_HPP

#include <variant>

namespace fastlanes {

template <typename... TS>
struct overloaded : TS... {
	using TS::operator()...;
};

template <typename... TS>
overloaded(TS...) -> overloaded<TS...>;

using std::get;
using std::variant;
using std::visit;
} // namespace fastlanes

#endif // FLS_STD_VARIANT_HPP
