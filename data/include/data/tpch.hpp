#ifndef DATA_TPCH_HPP
#define DATA_TPCH_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {

using tpch_dataset_t = std::array<std::pair<string_view, string_view>, 5>;

class Tpch {
public:
	static constexpr string_view customer {FASTLANES_DATA_DIR "/tpch/tables/customer"}; // NOLINT
	static constexpr string_view lineitem {FASTLANES_DATA_DIR "/tpch/tables/lineitem"}; // NOLINT
	static constexpr string_view orders {FASTLANES_DATA_DIR "/tpch/tables/orders"};     // NOLINT
	static constexpr string_view part {FASTLANES_DATA_DIR "/tpch/tables/part"};         // NOLINT
	static constexpr string_view partsupp {FASTLANES_DATA_DIR "/tpch/tables/partsupp"}; // NOLINT

	static constexpr tpch_dataset_t dataset = {
	    {{"customer", customer}, {"lineitem", lineitem}, {"orders", orders}, {"part", part}, {"partsupp", partsupp}}};
};

} // namespace fastlanes

#endif // DATA_TPCH_HPP
