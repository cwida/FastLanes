#ifndef FLS_COR_FUN_HPP
#define FLS_COR_FUN_HPP

namespace fastlanes {
// clang-format off
class CompressState;
class DecompressState;
class Vec;
class PageParam;
class VecParam;
// clang-format on
} // namespace fastlanes

namespace fastlanes {
using cmpr_fun_t    = void (*)(Vec&, Vec&, CompressState&);            //
using de_cmpr_fun_t = void (*)(PageParam, VecParam, DecompressState&); //
} // namespace fastlanes
#endif // FLS_COR_FUN_HPP
