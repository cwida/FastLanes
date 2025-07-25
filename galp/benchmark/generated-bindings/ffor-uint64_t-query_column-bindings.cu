// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/generated-bindings/ffor-uint64_t-query_column-bindings.cu
// ────────────────────────────────────────────────────────
#include "engine/kernels.cuh"
#include "engine/multi-column-host-kernels.cuh"
#include "generated-bindings/kernel-bindings.cuh"
#include <stdexcept>
namespace bindings {

template <>
bool query_column<uint64_t, flsgpu::device::FFORColumn<uint64_t>>(const flsgpu::device::FFORColumn<uint64_t> column,
                                                                  const unsigned        unpack_n_vectors,
                                                                  const unsigned        unpack_n_values,
                                                                  const enums::Unpacker unpacker,
                                                                  const enums::Patcher  patcher,
                                                                  const uint64_t        magic_value,
                                                                  const uint32_t        n_samples) {
	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::Dummy &&
	    patcher == enums::Patcher::None) {
		return kernels::host::query_column<
		    uint64_t,
		    1,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint64_t,
		        1,
		        flsgpu::device::BitUnpackerDummy<uint64_t, 1, 1, flsgpu::device::FFORFunctor<uint64_t, 1>>,
		        flsgpu::device::FFORColumn<uint64_t>>,
		    flsgpu::device::FFORColumn<uint64_t>>(column, magic_value, n_samples);
	}

	if (unpack_n_vectors == 1 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::None) {
		return kernels::host::query_column<
		    uint64_t,
		    1,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint64_t,
		        1,
		        flsgpu::device::BitUnpackerStatefulBranchless<uint64_t, 1, 1, flsgpu::device::FFORFunctor<uint64_t, 1>>,
		        flsgpu::device::FFORColumn<uint64_t>>,
		    flsgpu::device::FFORColumn<uint64_t>>(column, magic_value, n_samples);
	}
	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::Dummy &&
	    patcher == enums::Patcher::None) {
		return kernels::host::query_column<
		    uint64_t,
		    4,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint64_t,
		        4,
		        flsgpu::device::BitUnpackerDummy<uint64_t, 4, 1, flsgpu::device::FFORFunctor<uint64_t, 4>>,
		        flsgpu::device::FFORColumn<uint64_t>>,
		    flsgpu::device::FFORColumn<uint64_t>>(column, magic_value, n_samples);
	}

	if (unpack_n_vectors == 4 && unpack_n_values == 1 && unpacker == enums::Unpacker::StatefulBranchless &&
	    patcher == enums::Patcher::None) {
		return kernels::host::query_column<
		    uint64_t,
		    4,
		    1,
		    flsgpu::device::FFORDecompressor<
		        uint64_t,
		        4,
		        flsgpu::device::BitUnpackerStatefulBranchless<uint64_t, 4, 1, flsgpu::device::FFORFunctor<uint64_t, 4>>,
		        flsgpu::device::FFORColumn<uint64_t>>,
		    flsgpu::device::FFORColumn<uint64_t>>(column, magic_value, n_samples);
	}
	throw std::invalid_argument("Could not find correct binding in query_column FFOR<uint64_t>");
}

} // namespace bindings
