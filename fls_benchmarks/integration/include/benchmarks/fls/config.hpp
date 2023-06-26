#pragma once

#include "string"
#include <stdint.h>
#include <vector>

namespace cfg {
inline std::string options[] = {"data_32bit_c2684354560_bw1_val1",
                                "data_32bit_c268435456_bw1_val2",
                                "data_32bit_c5120_bw1_val2",
                                "data_32bit_c5120_bw1_val4",
                                "data_32bit_c268435456_bw1_val4",
                                "data_32bit_c536870912_bw1_val2",
                                "data_32bit_c2684354560_bw1_val1"};

inline int32_t answers[] = {1 * 256 * 1024 * 1024 * 2, //
                            5 * 1024 * 2,              //
                            5 * 1024 * 4,              //
                            1 * 256 * 1024 * 1024 * 4,
                            3 * 256 * 1024 * 1024 * 2,
                            -1609039872};

enum QueryT { BITPACKED, NORMAL, BITPACKED_OVERHEAD, NORMAL_OVERHEAD, NORMAL_DEBUG, BITPACKED_DEBUG, BITPACKED_NORMAL };

inline std::vector<std::string> schema        = {"first", "second"};
inline size_t                   tab_n         = 0;
inline int32_t                  answer        = answers[tab_n];
inline std::string              name          = options[tab_n];
inline uint8_t                  bw            = 2;
inline size_t                   r_c           = 10;
inline size_t                   t_max         = 8;
inline size_t                   vec_c         = 1024;
inline size_t                   scan_morsel_c = 1024 * 128;
inline bool                     is_bitpacked  = false;
inline QueryT                   query_t       = BITPACKED_NORMAL;

} // namespace cfg