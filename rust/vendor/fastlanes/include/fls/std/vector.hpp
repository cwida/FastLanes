#ifndef FLS_STD_VECTOR_HPP
#define FLS_STD_VECTOR_HPP

#include "fls/common/alias.hpp"
#include <vector>

namespace fastlanes {
template <typename T>
using vector    = std::vector<T>;
using idx_vec_t = std::vector<idx_t>; //
using bsz_vec_t = std::vector<bsz_t>; //
using ofs_vec_t = std::vector<ofs_t>; //
} // namespace fastlanes

#endif // FLS_STD_VECTOR_HPP
