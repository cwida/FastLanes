// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/generated-bindings/alp-double-query_multi_column-bindings.cu
// ────────────────────────────────────────────────────────
#include "engine/kernels.cuh"
#include "engine/multi-column-host-kernels.cuh"
#include "generated-bindings/kernel-bindings.cuh"
#include <stdexcept>

namespace bindings {

template <>
bool query_multi_column<double, flsgpu::host::ALPColumn<double>>(const flsgpu::host::ALPColumn<double> column,
                                                                 const unsigned                        unpack_n_vectors,
                                                                 const unsigned                        unpack_n_values,
                                                                 const enums::Unpacker                 unpacker,
                                                                 const enums::Patcher                  patcher,
                                                                 const double                          magic_value,
                                                                 const uint32_t                        n_samples) {

	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::Stateful) {
		return kernels::host::query_multi_column<
		    double,
		    1,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 1, 1, flsgpu::device::ALPFunctor<double, 1>>,
		        flsgpu::device::StatefulALPExceptionPatcher<double, 1, 1>,
		        flsgpu::device::ALPColumn<double>>,
		    flsgpu::host::ALPColumn<double>>(column, magic_value, n_samples);
	}

	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::Stateful) {
		return kernels::host::query_multi_column<
		    double,
		    4,
		    1,
		    flsgpu::device::ALPDecompressor<
		        double,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<double, 4, 1, flsgpu::device::ALPFunctor<double, 4>>,
		        flsgpu::device::StatefulALPExceptionPatcher<double, 4, 1>,
		        flsgpu::device::ALPColumn<double>>,
		    flsgpu::host::ALPColumn<double>>(column, magic_value, n_samples);
	}
	throw std::invalid_argument("Could not find correct binding in query_multi_column ALP<double>");
}

} // namespace bindings
