#ifndef FLS_COMMON_STR_HPP
#define FLS_COMMON_STR_HPP

#include "fls/common/alias.hpp"         // for ofs_t, up, n_t, sz_t, len_t
#include "fls/expression/data_type.hpp" // for str_pt
#include "fls/std/vector.hpp"           // for bsz_vec_t, ofs_vec_t
#include <stdint.h>                     // for uint8_t
#include <string>                       // for string
#include <utility>                      // for pair
#include <vector>                       // for vector

namespace fastlanes {

using decoupled_str_vec = std::pair<std::vector<len_t>, std::vector<uint8_t*>>;

class Str {
public:
	static decoupled_str_vec         decouple(const std::vector<str_pt>& str_vec);      //
	static decoupled_str_vec         decouple(n_t n, std::string* str_arr);             //
	static up<bsz_vec_t>             get_bsz_vec(const ofs_t* ofs_arr, sz_t size);      //
	static up<ofs_vec_t>             to_normal_offset(const ofs_t* ofs_arr, sz_t size); //
	static up<std::vector<uint8_t*>> smart_offset_to_pointer(n_t c, ofs_t offset_arr[], uint8_t str_arr[]);
};
} // namespace fastlanes
#endif // FLS_COMMON_STR_HPP
