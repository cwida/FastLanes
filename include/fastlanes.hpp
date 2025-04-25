#ifndef FASTLANES_HPP
#define FASTLANES_HPP

#include "fls/connection.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/expression/predicate_operator.hpp"
#include "fls/reader/reader.hpp"

namespace fastlanes {

class FastLanes {
public:
	static constexpr string_view get_version() {
		return version_0_0_2;
	}
	static constexpr string_view get_name() {
		return lib_name;
	}

private:
	static constexpr auto lib_name      = string_view("FastLanes");
	static constexpr auto version_0_0_2 = string_view("0.0.2"); // smart entry point
	static constexpr auto version_0_0_1 = string_view("0.0.1"); // starting version
};

} // namespace fastlanes

#endif
