#ifndef FLS_PRIMITIVE_ALP_CONFIG_HPP
#define FLS_PRIMITIVE_ALP_CONFIG_HPP

// NOLINTBEGIN

#include <cstddef>

namespace alp {
enum SCHEME {
	ALP_CUTTER,
	ALP_PDE,
};
}

/*
2048

best : r_bw : 51| l_bw : 3| unq_c : 0| 0.382812 | 0.333008 | 0.156250 | 0.035156 | 0.025879 | 0.025391 | 0.013672 |
0.008301 | 0.008301 | 0.003906 | 0.003906 | 0.003418 | best : r_bw : 52| l_bw : 3| unq_c : 0| 0.778320 | 0.071289 |
0.033691 | 0.033203 | 0.029297 | 0.024414 | 0.008789 | 0.007324 | 0.006348 | 0.001953 | 0.001465 | 0.000977 | 0.000977 |
0.000977 | 0.000488 | 0.000488 | air_sensor_f : r_bw : 51| l_bw : 3| size : 54.7044| rg_c : 1| vec_c : 9| exc_c : 22.5
poi_lat : r_bw : 52| l_bw : 3| size : 55.4734| rg_c : 5| vec_c : 415| exc_c : 15.1087
best : r_bw : 53| l_bw : 3| unq_c : 0| 0.339844 | 0.270508 | 0.242188 | 0.050293 | 0.039062 | 0.022949 | 0.016113 |
0.005859 | 0.004883 | 0.003906 | 0.001953 | 0.000977 | 0.000488 | 0.000488 | 0.000488 | poi_lon : r_bw : 53| l_bw : 3|
size : 56.4044| rg_c : 5| vec_c : 415| exc_c : 12.901

 */

namespace alp::config {
constexpr size_t VEC_C          = 1024;
constexpr size_t RG_C           = 64UL * 1024;
constexpr size_t MAGIC_LIMIT    = 1536;
constexpr size_t CUT_LIMIT      = 16;
constexpr size_t SMP_C          = 256; // Total number of sampled values (expressed in vectors * values_per_vector)
constexpr size_t EXC_LIMIT      = SMP_C;
constexpr size_t SMP_R_C        = 32; // Values per vector
constexpr size_t RG_SMP_RUN_JMP = 32; // Jumps between each value taken inside a vector
constexpr size_t STEP_N         = SMP_C / SMP_R_C;
constexpr size_t RG_SMP_MICRO_RUN_SIZE = 1; // Consecutive runs in each jump inside a
constexpr size_t N_COMB                = 5; // Maximum number of combinations obtained from row group sampling
constexpr size_t CUTTER_DICT_BW        = 3;
constexpr size_t CUTTER_DICT_SZ        = (1 << CUTTER_DICT_BW);

} // namespace alp::config

// todo
using namespace alp::config;
#endif

// NOLINTEND
