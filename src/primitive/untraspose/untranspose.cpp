#include "fls/primitive/untranspose/untranspose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"

namespace fastlanes {
void untranspose_i(const int64_t* a_in, int64_t* a_out) {
	auto* in  = reinterpret_cast<const uint64_t*>(a_in);
	auto* out = reinterpret_cast<uint64_t*>(a_out);

	generated::untranspose::fallback::scalar::untranspose_i(in, out);
}

void untranspose_i(const double* a_in, double* a_out) {
	auto* in  = reinterpret_cast<const uint64_t*>(a_in);
	auto* out = reinterpret_cast<uint64_t*>(a_out);

	generated::untranspose::fallback::scalar::untranspose_i(in, out);
}

} // namespace fastlanes