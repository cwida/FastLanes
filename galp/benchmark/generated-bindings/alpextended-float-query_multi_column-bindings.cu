// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/generated-bindings/alpextended-float-query_multi_column-bindings.cu
// ────────────────────────────────────────────────────────
#include "engine/kernels.cuh"
#include "engine/multi-column-host-kernels.cuh"
#include "generated-bindings/kernel-bindings.cuh"
#include <stdexcept>

namespace bindings {

template <>
bool query_multi_column<float, flsgpu::host::ALPExtendedColumn<float>>(
    const flsgpu::host::ALPExtendedColumn<float> column,
    const unsigned                               unpack_n_vectors,
    const unsigned                               unpack_n_values,
    const enums::Unpacker                        unpacker,
    const enums::Patcher                         patcher,
    const float                                  magic_value,
    const uint32_t                               n_samples) {
	if (unpack_n_vectors == 1 && unpack_n_values == 32 && unpacker == enums::Unpacker::OldFls &&
	    patcher == enums::Patcher::Naive) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    32,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerOldFls<float, 1, 32, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::NaiveALPExceptionPatcher<float, 1, 32>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 32 && unpacker == enums::Unpacker::OldFls &&
	    patcher == enums::Patcher::NaiveBranchless) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    32,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerOldFls<float, 1, 32, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::NaiveBranchlessALPExceptionPatcher<float, 1, 32>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 32 && unpacker == enums::Unpacker::OldFls &&
	    patcher == enums::Patcher::PrefetchAll) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    32,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerOldFls<float, 1, 32, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::PrefetchAllALPExceptionPatcher<float, 1, 32>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 32 && unpacker == enums::Unpacker::OldFls &&
	    patcher == enums::Patcher::PrefetchAllBranchless) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    32,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerOldFls<float, 1, 32, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::PrefetchAllBranchlessALPExceptionPatcher<float, 1, 32>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::Naive) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 1, 1, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::NaiveALPExceptionPatcher<float, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::NaiveBranchless) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 1, 1, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::NaiveBranchlessALPExceptionPatcher<float, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAll) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 1, 1, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::PrefetchAllALPExceptionPatcher<float, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAllBranchless) {
		return kernels::host::query_multi_column<
		    float,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 1, 1, flsgpu::device::ALPFunctor<float, 1>>,
		        flsgpu::device::PrefetchAllBranchlessALPExceptionPatcher<float, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}

	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::Naive) {
		return kernels::host::query_multi_column<
		    float,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 4, 1, flsgpu::device::ALPFunctor<float, 4>>,
		        flsgpu::device::NaiveALPExceptionPatcher<float, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::NaiveBranchless) {
		return kernels::host::query_multi_column<
		    float,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 4, 1, flsgpu::device::ALPFunctor<float, 4>>,
		        flsgpu::device::NaiveBranchlessALPExceptionPatcher<float, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAll) {
		return kernels::host::query_multi_column<
		    float,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 4, 1, flsgpu::device::ALPFunctor<float, 4>>,
		        flsgpu::device::PrefetchAllALPExceptionPatcher<float, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAllBranchless) {
		return kernels::host::query_multi_column<
		    float,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        float,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<float, 4, 1, flsgpu::device::ALPFunctor<float, 4>>,
		        flsgpu::device::PrefetchAllBranchlessALPExceptionPatcher<float, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<float>>,
		    flsgpu::host::ALPExtendedColumn<float>>(column, magic_value, n_samples);
	}
	throw std::invalid_argument("Could not find correct binding in query_multi_column ALPExtended<float>");
}

} // namespace bindings
