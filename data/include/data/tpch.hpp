// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// data/include/data/tpch.hpp
// ────────────────────────────────────────────────────────
#ifndef DATA_TPCH_HPP
#define DATA_TPCH_HPP

#include <array>
#include <string>

namespace fastlanes {

using tpch_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 5>;

class Tpch {
public:
	static constexpr std::string_view customer {FASTLANES_DATA_DIR "/tpch/tables/customer"}; // NOLINT
	static constexpr std::string_view lineitem {FASTLANES_DATA_DIR "/tpch/tables/lineitem"}; // NOLINT
	static constexpr std::string_view orders {FASTLANES_DATA_DIR "/tpch/tables/orders"};     // NOLINT
	static constexpr std::string_view part {FASTLANES_DATA_DIR "/tpch/tables/part"};         // NOLINT
	static constexpr std::string_view partsupp {FASTLANES_DATA_DIR "/tpch/tables/partsupp"}; // NOLINT

	static constexpr tpch_dataset_t dataset = {
	    {{"customer", customer}, {"lineitem", lineitem}, {"orders", orders}, {"part", part}, {"partsupp", partsupp}}};
};

} // namespace fastlanes

#endif // DATA_TPCH_HPP
