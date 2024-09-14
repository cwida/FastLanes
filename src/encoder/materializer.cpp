#include "fls/encoder/materializer.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/primitive/untranspose/untranspose.hpp"

namespace fastlanes {
template <typename PT>
Materializer<PT>::Materializer(span<PT> output_span)
    : output_span(output_span) {}

template <typename PT>
void Materializer<PT>::Materialize(const Vec& vec) {

	auto in  = reinterpret_cast<PT*>(vec.buf_arr[0].data());
	auto out = output_span.data();

	untranspose_i(in, out);

	output_span = output_span.subspan(CFG::VEC_SZ);
}

template class Materializer<i64_pt>;
} // namespace fastlanes
