#include "fls/table/stats.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/utl/util.hpp"
#include <limits>

namespace fastlanes {
template <typename PT>
TypedStats<PT>::TypedStats()
    : min {std::numeric_limits<PT>::max()}    //
    , max {std::numeric_limits<PT>::lowest()} //
    , last_seen_val(0)
    , n_nulls(0)
    , is_double_castable(false) {
}

template <typename PT>
TypedStats<PT>::~TypedStats() = default;

template <typename PT>
bool TypedStats<PT>::IsConstant() {
	FLS_ASSERT_FALSE(bimap_frequency.empty())

	return bimap_frequency.size() == 1;
};

FLS_ALL_CTS(TypedStats)

FlsStringStats::FlsStringStats()
    : is_constant {true}
    , maximum_n_bytes_p_value(std::numeric_limits<n_t>::lowest())
    , is_numeric(false)
    , last_seen_val("NULL") {
}

} // namespace fastlanes
