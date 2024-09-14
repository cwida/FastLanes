#ifndef FLS_PRIMITIVE_UNTRANSPOSE_UNTRANSPOSE_HPP
#define FLS_PRIMITIVE_UNTRANSPOSE_UNTRANSPOSE_HPP

#include <cstdint>

namespace fastlanes {
void untranspose_i(const int64_t* __restrict in, int64_t* __restrict out);
}

#endif // FLS_PRIMITIVE_UNTRANSPOSE_UNTRANSPOSE_HPP
