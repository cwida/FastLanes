#include "fls/primitive/patch/patch.hpp"
#include "fls/cuda/common.hpp"

namespace fastlanes {

template <typename PT>
void Patch<PT>::data_parallelize(const PT* __restrict in_exc_arr,
                                 const uint16_t* __restrict in_pos_arr,
                                 n_t n_exceptions,
                                 PT* __restrict out_exc_arr,
                                 uint16_t* __restrict out_offset,
                                 uint16_t* __restrict out_pos_arr,
                                 uint8_t* __restrict out_count) {
	//
	constexpr n_t N_LANES = cuda::get_n_lanes<PT>();
	static_assert((N_LANES & (N_LANES - 1)) == 0, "N_LANES must be a power of two");
	constexpr n_t MASK = N_LANES - 1;

	//
	for (n_t lane = 0; lane < N_LANES; ++lane) {
		out_count[lane] = 0;
	}

	for (n_t i = 0; i < n_exceptions; ++i) {
		++out_count[in_pos_arr[i] & MASK];
	}

	//
	uint16_t running = 0;
	for (n_t lane = 0; lane < N_LANES; ++lane) {
		out_offset[lane] = running;
		running += out_count[lane];
	}

	for (n_t i = 0; i < n_exceptions; ++i) {
		const n_t      lane = in_pos_arr[i] & MASK;
		const uint16_t dst  = out_offset[lane]++; // advance only the cursor
		out_exc_arr[dst]    = in_exc_arr[i];
		out_pos_arr[dst]    = in_pos_arr[i];
	}
}

template class Patch<flt_pt>;
template class Patch<dbl_pt>;

} // namespace fastlanes