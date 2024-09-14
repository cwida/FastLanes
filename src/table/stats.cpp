#include "fls/table/stats.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/utl/util.hpp"
#include <limits>

namespace fastlanes {

template <typename PT>
TypedStats<PT>::ValueMtd::ValueMtd(const n_t dict_code)
    : dict_code(dict_code)
    , repetition(1) {}

template <typename PT>
TypedStats<PT>::TypedStats()
    : t_stats {}
    , n_null {0}
    , n_run {1}                            // there is always one run.
    , is_constant {true}                   //
    , min {std::numeric_limits<PT>::max()} //
    , max {std::numeric_limits<PT>::min()} //
    {

    };

FLS_ALL_CTS(TypedStats)
} // namespace fastlanes
