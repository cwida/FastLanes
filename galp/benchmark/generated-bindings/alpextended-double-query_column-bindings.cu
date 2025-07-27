// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/generated-bindings/alpextended-double-query_column-bindings.cu
// ────────────────────────────────────────────────────────
#include "engine/kernels.cuh"
#include "engine/multi-column-host-kernels.cuh"
#include "generated-bindings/kernel-bindings.cuh"
#include <stdexcept>

namespace bindings {

template <>
bool query_column<double, flsgpu::device::ALPExtendedColumn<double>>(
    const flsgpu::device::ALPExtendedColumn<double> column,
    const unsigned                                  unpack_n_vectors,
    const unsigned                                  unpack_n_values,
    const enums::Unpacker                           unpacker,
    const enums::Patcher                            patcher,
    const double                                    magic_value,
    const uint32_t                                  n_samples) {

	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::Naive) {
		return kernels::host::query_column<
		    double,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 1, 1, flsgpu::device::ALPFunctor<double, 1>>,
		        flsgpu::device::NaiveALPExceptionPatcher<double, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::NaiveBranchless) {
		return kernels::host::query_column<
		    double,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 1, 1, flsgpu::device::ALPFunctor<double, 1>>,
		        flsgpu::device::NaiveBranchlessALPExceptionPatcher<double, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAll) {
		return kernels::host::query_column<
		    double,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 1, 1, flsgpu::device::ALPFunctor<double, 1>>,
		        flsgpu::device::PrefetchAllALPExceptionPatcher<double, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAllBranchless) {
		return kernels::host::query_column<
		    double,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 1, 1, flsgpu::device::ALPFunctor<double, 1>>,
		        flsgpu::device::PrefetchAllBranchlessALPExceptionPatcher<double, 1, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}

	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::Naive) {
		return kernels::host::query_column<
		    double,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 4, 1, flsgpu::device::ALPFunctor<double, 4>>,
		        flsgpu::device::NaiveALPExceptionPatcher<double, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::NaiveBranchless) {
		return kernels::host::query_column<
		    double,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 4, 1, flsgpu::device::ALPFunctor<double, 4>>,
		        flsgpu::device::NaiveBranchlessALPExceptionPatcher<double, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAll) {
		return kernels::host::query_column<
		    double,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 4, 1, flsgpu::device::ALPFunctor<double, 4>>,
		        flsgpu::device::PrefetchAllALPExceptionPatcher<double, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::PrefetchAllBranchless) {
		return kernels::host::query_column<
		    double,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 4, 1, flsgpu::device::ALPFunctor<double, 4>>,
		        flsgpu::device::PrefetchAllBranchlessALPExceptionPatcher<double, 4, 1>,
		        flsgpu::device::ALPExtendedColumn<double>>,
		    flsgpu::device::ALPExtendedColumn<double>>(column, magic_value, n_samples);
	}
	throw std::invalid_argument("Could not find correct binding in query_column ALPExtended<double>");
}

} // namespace bindings
