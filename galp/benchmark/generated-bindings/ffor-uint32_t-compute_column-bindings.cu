// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/generated-bindings/ffor-uint32_t-compute_column-bindings.cu
// ────────────────────────────────────────────────────────
#include "engine/kernels.cuh"
#include "engine/multi-column-host-kernels.cuh"
#include "generated-bindings/kernel-bindings.cuh"
#include <stdexcept>

namespace bindings {

template <>
bool compute_column<uint32_t, flsgpu::device::FFORColumn<uint32_t>>(const flsgpu::device::FFORColumn<uint32_t> column,
                                                                    const unsigned        unpack_n_vectors,
                                                                    const unsigned        unpack_n_values,
                                                                    const enums::Unpacker unpacker,
                                                                    const enums::Patcher  patcher,
                                                                    const unsigned        n_repetitions,
                                                                    const uint32_t        n_samples) {
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::Dummy &&
	    patcher == enums::Patcher::None) {
		return kernels::host::compute_column<
		    uint32_t,
		    1,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint32_t,
		        1,
		        flsgpu::device::BitUnpackerDummy<uint32_t, 1, 1, flsgpu::device::FFORFunctor<uint32_t, 1>>,
		        flsgpu::device::FFORColumn<uint32_t>>,
		    flsgpu::device::FFORColumn<uint32_t>,
		    10>(column, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 32 && unpacker == enums::Unpacker::OldFls &&
	    patcher == enums::Patcher::None) {
		return kernels::host::compute_column<
		    uint32_t,
		    1,
		    32,
		    flsgpu::device::FFORDecompressor<
		        uint32_t,
		        1,
		        flsgpu::device::BitUnpackerOldFls<uint32_t, 1, 32, flsgpu::device::FFORFunctor<uint32_t, 1>>,
		        flsgpu::device::FFORColumn<uint32_t>>,
		    flsgpu::device::FFORColumn<uint32_t>,
		    10>(column, n_samples);
	}
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::None) {
		return kernels::host::compute_column<
		    uint32_t,
		    1,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint32_t,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<uint32_t, 1, 1, flsgpu::device::FFORFunctor<uint32_t, 1>>,
		        flsgpu::device::FFORColumn<uint32_t>>,
		    flsgpu::device::FFORColumn<uint32_t>,
		    10>(column, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::Dummy &&
	    patcher == enums::Patcher::None) {
		return kernels::host::compute_column<
		    uint32_t,
		    4,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint32_t,
		        4,
		        flsgpu::device::BitUnpackerDummy<uint32_t, 4, 1, flsgpu::device::FFORFunctor<uint32_t, 4>>,
		        flsgpu::device::FFORColumn<uint32_t>>,
		    flsgpu::device::FFORColumn<uint32_t>,
		    10>(column, n_samples);
	}

	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::None) {
		return kernels::host::compute_column<
		    uint32_t,
		    4,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint32_t,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<uint32_t, 4, 1, flsgpu::device::FFORFunctor<uint32_t, 4>>,
		        flsgpu::device::FFORColumn<uint32_t>>,
		    flsgpu::device::FFORColumn<uint32_t>,
		    10>(column, n_samples);
	}
	throw std::invalid_argument("Could not find correct binding in compute_column FFOR<uint32_t>");
}

} // namespace bindings
