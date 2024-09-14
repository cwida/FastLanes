#ifndef FLS_COMMON_ALIAS_HPP
#define FLS_COMMON_ALIAS_HPP

#include <cstddef>
#include <cstdint>
#include <memory>

namespace fastlanes {
using n_t         = uint64_t; // For countable things
using bw_t        = uint8_t;
using pos_t       = uint16_t; // position of a tuple in a vec.
using base_t      = uint8_t[8];
using bitmap_t    = uint64_t[16];
using unit_t      = uint64_t;
using ep_t        = uint32_t;
using var_t       = uint8_t;
using idx_t       = uint32_t;
using ofs_t       = uint32_t; // todo
using bsz_t       = uint64_t; /* byte size. */
using sz_t        = uint64_t; /* size */
using hdr_field_t = uint64_t;
using len_t       = uint32_t;
using vec_idx_t   = uint16_t; // for indexes inside a vector

// clang-format off
template <typename T> using sp = std::shared_ptr<T>;
template <typename T> using up = std::unique_ptr<T>;

using std::make_unique;
}

#endif // FLS_COMMON_ALIAS_HPP
