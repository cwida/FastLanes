// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/fls-switch-case.cuh
// ────────────────────────────────────────────────────────
#ifndef FLS_SWITCH_CASE_CUH
#define FLS_SWITCH_CASE_CUH

#include "fls.cuh"

namespace flsgpu { namespace device {

template <typename T,
          unsigned UNPACK_N_VECTORS,
          unsigned UNPACK_N_VALUES,
          typename processor_T,
          typename LoaderT,
          vbw_t    VALUE_BIT_WIDTH,
          unsigned START_INDEX>
__device__ void
switch_leaf(const typename utils::same_width_uint<T>::type* __restrict in, T* __restrict out, processor_T processor) {
	using UINT_T                      = typename utils::same_width_uint<T>::type;
	constexpr uint8_t  LANE_BIT_WIDTH = utils::get_lane_bitwidth<UINT_T>();
	constexpr uint32_t N_LANES        = utils::get_n_lanes<UINT_T>();
	constexpr uint16_t PRECEDING_BITS = (START_INDEX * VALUE_BIT_WIDTH);
	constexpr uint16_t BUFFER_OFFSET  = PRECEDING_BITS % LANE_BIT_WIDTH;
	constexpr uint16_t N_INPUT_LINE   = PRECEDING_BITS / LANE_BIT_WIDTH;

	LoaderT loader(in + N_INPUT_LINE * N_LANES, utils::get_compressed_vector_size<UINT_T>(VALUE_BIT_WIDTH));

	constexpr T VALUE_MASK = utils::h_set_first_n_bits<UINT_T>(VALUE_BIT_WIDTH);

	Masker<UINT_T, UNPACK_N_VECTORS> masker(BUFFER_OFFSET, VALUE_BIT_WIDTH);

	UINT_T values[UNPACK_N_VECTORS];

	// INFO Yes these lines contain if statements without constexpr
	// INFO No this is not a problem, as you can check with a profiler
	// whether the compiler is able to emit the right SASS, and the SASS
	// is correct, with no run time branches, only 5-8 instructions per case

#pragma unroll
	for (int i = 0; i < UNPACK_N_VALUES; ++i) {
		if (masker.is_buffer_empty()) {
			loader.next_line();
			masker.next_line();
		}

		UINT_T buffers[UNPACK_N_VECTORS];
		loader.load_next_into(buffers);
		masker.mask_and_increment(values, buffers);

		if (masker.continues_on_next_line()) {
			loader.next_line();
			masker.next_line();
			loader.load_next_into(buffers);
			masker.mask_and_insert_remaining_value(values, buffers);
		}

#pragma unroll
		for (int v = 0; v < UNPACK_N_VECTORS; ++v) {
			*(out + i + v * UNPACK_N_VALUES) = processor(values[v], v);
		}
	}
}

template <typename T,
          unsigned UNPACK_N_VECTORS,
          unsigned UNPACK_N_VALUES,
          typename processor_T,
          typename LoaderT,
          vbw_t VALUE_BIT_WIDTH>
__device__ void switch_start_index(const typename utils::same_width_uint<T>::type* __restrict in,
                                   T* __restrict out,
                                   processor_T processor,
                                   const si_t  start_index) {
	constexpr int N_VALUES_IN_LANE = utils::get_values_per_lane<T>();

	switch (start_index) {
	case 0:
		if constexpr (0 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 0>(
			    in, out, processor);
		}
		break;
	case 1:
		if constexpr (1 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 1>(
			    in, out, processor);
		}
		break;
	case 2:
		if constexpr (2 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 2>(
			    in, out, processor);
		}
		break;
	case 3:
		if constexpr (3 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 3>(
			    in, out, processor);
		}
		break;
	case 4:
		if constexpr (4 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 4>(
			    in, out, processor);
		}
		break;
	case 5:
		if constexpr (5 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 5>(
			    in, out, processor);
		}
		break;
	case 6:
		if constexpr (6 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 6>(
			    in, out, processor);
		}
		break;
	case 7:
		if constexpr (7 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 7>(
			    in, out, processor);
		}
		break;
	case 8:
		if constexpr (8 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 8>(
			    in, out, processor);
		}
		break;
	case 9:
		if constexpr (9 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 9>(
			    in, out, processor);
		}
		break;
	case 10:
		if constexpr (10 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 10>(
			    in, out, processor);
		}
		break;
	case 11:
		if constexpr (11 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 11>(
			    in, out, processor);
		}
		break;
	case 12:
		if constexpr (12 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 12>(
			    in, out, processor);
		}
		break;
	case 13:
		if constexpr (13 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 13>(
			    in, out, processor);
		}
		break;
	case 14:
		if constexpr (14 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 14>(
			    in, out, processor);
		}
		break;
	case 15:
		if constexpr (15 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 15>(
			    in, out, processor);
		}
		break;
	case 16:
		if constexpr (16 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 16>(
			    in, out, processor);
		}
		break;
	case 17:
		if constexpr (17 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 17>(
			    in, out, processor);
		}
		break;
	case 18:
		if constexpr (18 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 18>(
			    in, out, processor);
		}
		break;
	case 19:
		if constexpr (19 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 19>(
			    in, out, processor);
		}
		break;
	case 20:
		if constexpr (20 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 20>(
			    in, out, processor);
		}
		break;
	case 21:
		if constexpr (21 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 21>(
			    in, out, processor);
		}
		break;
	case 22:
		if constexpr (22 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 22>(
			    in, out, processor);
		}
		break;
	case 23:
		if constexpr (23 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 23>(
			    in, out, processor);
		}
		break;
	case 24:
		if constexpr (24 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 24>(
			    in, out, processor);
		}
		break;
	case 25:
		if constexpr (25 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 25>(
			    in, out, processor);
		}
		break;
	case 26:
		if constexpr (26 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 26>(
			    in, out, processor);
		}
		break;
	case 27:
		if constexpr (27 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 27>(
			    in, out, processor);
		}
		break;
	case 28:
		if constexpr (28 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 28>(
			    in, out, processor);
		}
		break;
	case 29:
		if constexpr (29 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 29>(
			    in, out, processor);
		}
		break;
	case 30:
		if constexpr (30 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 30>(
			    in, out, processor);
		}
		break;
	case 31:
		if constexpr (31 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 31>(
			    in, out, processor);
		}
		break;
	case 32:
		if constexpr (32 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 32>(
			    in, out, processor);
		}
		break;
	case 33:
		if constexpr (33 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 33>(
			    in, out, processor);
		}
		break;
	case 34:
		if constexpr (34 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 34>(
			    in, out, processor);
		}
		break;
	case 35:
		if constexpr (35 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 35>(
			    in, out, processor);
		}
		break;
	case 36:
		if constexpr (36 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 36>(
			    in, out, processor);
		}
		break;
	case 37:
		if constexpr (37 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 37>(
			    in, out, processor);
		}
		break;
	case 38:
		if constexpr (38 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 38>(
			    in, out, processor);
		}
		break;
	case 39:
		if constexpr (39 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 39>(
			    in, out, processor);
		}
		break;
	case 40:
		if constexpr (40 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 40>(
			    in, out, processor);
		}
		break;
	case 41:
		if constexpr (41 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 41>(
			    in, out, processor);
		}
		break;
	case 42:
		if constexpr (42 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 42>(
			    in, out, processor);
		}
		break;
	case 43:
		if constexpr (43 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 43>(
			    in, out, processor);
		}
		break;
	case 44:
		if constexpr (44 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 44>(
			    in, out, processor);
		}
		break;
	case 45:
		if constexpr (45 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 45>(
			    in, out, processor);
		}
		break;
	case 46:
		if constexpr (46 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 46>(
			    in, out, processor);
		}
		break;
	case 47:
		if constexpr (47 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 47>(
			    in, out, processor);
		}
		break;
	case 48:
		if constexpr (48 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 48>(
			    in, out, processor);
		}
		break;
	case 49:
		if constexpr (49 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 49>(
			    in, out, processor);
		}
		break;
	case 50:
		if constexpr (50 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 50>(
			    in, out, processor);
		}
		break;
	case 51:
		if constexpr (51 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 51>(
			    in, out, processor);
		}
		break;
	case 52:
		if constexpr (52 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 52>(
			    in, out, processor);
		}
		break;
	case 53:
		if constexpr (53 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 53>(
			    in, out, processor);
		}
		break;
	case 54:
		if constexpr (54 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 54>(
			    in, out, processor);
		}
		break;
	case 55:
		if constexpr (55 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 55>(
			    in, out, processor);
		}
		break;
	case 56:
		if constexpr (56 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 56>(
			    in, out, processor);
		}
		break;
	case 57:
		if constexpr (57 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 57>(
			    in, out, processor);
		}
		break;
	case 58:
		if constexpr (58 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 58>(
			    in, out, processor);
		}
		break;
	case 59:
		if constexpr (59 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 59>(
			    in, out, processor);
		}
		break;
	case 60:
		if constexpr (60 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 60>(
			    in, out, processor);
		}
		break;
	case 61:
		if constexpr (61 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 61>(
			    in, out, processor);
		}
		break;
	case 62:
		if constexpr (62 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 62>(
			    in, out, processor);
		}
		break;
	case 63:
		if constexpr (63 < N_VALUES_IN_LANE) {
			switch_leaf<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, VALUE_BIT_WIDTH, 63>(
			    in, out, processor);
		}
		break;
	}
}

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES, typename processor_T, typename LoaderT>
__device__ void switch_value_bit_width(const typename utils::same_width_uint<T>::type* __restrict in,
                                       T* __restrict out,
                                       processor_T processor,
                                       const vbw_t value_bit_width,
                                       const si_t  start_index) {
	constexpr int N_BITS = utils::sizeof_in_bits<T>();

	switch (value_bit_width) {
	case 0:
		if constexpr (0 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 0>(
			    in, out, processor, start_index);
		}
		break;
	case 1:
		if constexpr (1 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 1>(
			    in, out, processor, start_index);
		}
		break;
	case 2:
		if constexpr (2 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 2>(
			    in, out, processor, start_index);
		}
		break;
	case 3:
		if constexpr (3 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 3>(
			    in, out, processor, start_index);
		}
		break;
	case 4:
		if constexpr (4 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 4>(
			    in, out, processor, start_index);
		}
		break;
	case 5:
		if constexpr (5 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 5>(
			    in, out, processor, start_index);
		}
		break;
	case 6:
		if constexpr (6 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 6>(
			    in, out, processor, start_index);
		}
		break;
	case 7:
		if constexpr (7 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 7>(
			    in, out, processor, start_index);
		}
		break;
	case 8:
		if constexpr (8 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 8>(
			    in, out, processor, start_index);
		}
		break;
	case 9:
		if constexpr (9 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 9>(
			    in, out, processor, start_index);
		}
		break;
	case 10:
		if constexpr (10 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 10>(
			    in, out, processor, start_index);
		}
		break;
	case 11:
		if constexpr (11 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 11>(
			    in, out, processor, start_index);
		}
		break;
	case 12:
		if constexpr (12 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 12>(
			    in, out, processor, start_index);
		}
		break;
	case 13:
		if constexpr (13 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 13>(
			    in, out, processor, start_index);
		}
		break;
	case 14:
		if constexpr (14 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 14>(
			    in, out, processor, start_index);
		}
		break;
	case 15:
		if constexpr (15 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 15>(
			    in, out, processor, start_index);
		}
		break;
	case 16:
		if constexpr (16 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 16>(
			    in, out, processor, start_index);
		}
		break;
	case 17:
		if constexpr (17 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 17>(
			    in, out, processor, start_index);
		}
		break;
	case 18:
		if constexpr (18 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 18>(
			    in, out, processor, start_index);
		}
		break;
	case 19:
		if constexpr (19 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 19>(
			    in, out, processor, start_index);
		}
		break;
	case 20:
		if constexpr (20 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 20>(
			    in, out, processor, start_index);
		}
		break;
	case 21:
		if constexpr (21 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 21>(
			    in, out, processor, start_index);
		}
		break;
	case 22:
		if constexpr (22 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 22>(
			    in, out, processor, start_index);
		}
		break;
	case 23:
		if constexpr (23 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 23>(
			    in, out, processor, start_index);
		}
		break;
	case 24:
		if constexpr (24 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 24>(
			    in, out, processor, start_index);
		}
		break;
	case 25:
		if constexpr (25 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 25>(
			    in, out, processor, start_index);
		}
		break;
	case 26:
		if constexpr (26 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 26>(
			    in, out, processor, start_index);
		}
		break;
	case 27:
		if constexpr (27 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 27>(
			    in, out, processor, start_index);
		}
		break;
	case 28:
		if constexpr (28 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 28>(
			    in, out, processor, start_index);
		}
		break;
	case 29:
		if constexpr (29 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 29>(
			    in, out, processor, start_index);
		}
		break;
	case 30:
		if constexpr (30 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 30>(
			    in, out, processor, start_index);
		}
		break;
	case 31:
		if constexpr (31 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 31>(
			    in, out, processor, start_index);
		}
		break;
	case 32:
		if constexpr (32 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 32>(
			    in, out, processor, start_index);
		}
		break;
	case 33:
		if constexpr (33 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 33>(
			    in, out, processor, start_index);
		}
		break;
	case 34:
		if constexpr (34 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 34>(
			    in, out, processor, start_index);
		}
		break;
	case 35:
		if constexpr (35 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 35>(
			    in, out, processor, start_index);
		}
		break;
	case 36:
		if constexpr (36 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 36>(
			    in, out, processor, start_index);
		}
		break;
	case 37:
		if constexpr (37 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 37>(
			    in, out, processor, start_index);
		}
		break;
	case 38:
		if constexpr (38 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 38>(
			    in, out, processor, start_index);
		}
		break;
	case 39:
		if constexpr (39 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 39>(
			    in, out, processor, start_index);
		}
		break;
	case 40:
		if constexpr (40 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 40>(
			    in, out, processor, start_index);
		}
		break;
	case 41:
		if constexpr (41 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 41>(
			    in, out, processor, start_index);
		}
		break;
	case 42:
		if constexpr (42 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 42>(
			    in, out, processor, start_index);
		}
		break;
	case 43:
		if constexpr (43 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 43>(
			    in, out, processor, start_index);
		}
		break;
	case 44:
		if constexpr (44 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 44>(
			    in, out, processor, start_index);
		}
		break;
	case 45:
		if constexpr (45 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 45>(
			    in, out, processor, start_index);
		}
		break;
	case 46:
		if constexpr (46 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 46>(
			    in, out, processor, start_index);
		}
		break;
	case 47:
		if constexpr (47 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 47>(
			    in, out, processor, start_index);
		}
		break;
	case 48:
		if constexpr (48 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 48>(
			    in, out, processor, start_index);
		}
		break;
	case 49:
		if constexpr (49 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 49>(
			    in, out, processor, start_index);
		}
		break;
	case 50:
		if constexpr (50 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 50>(
			    in, out, processor, start_index);
		}
		break;
	case 51:
		if constexpr (51 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 51>(
			    in, out, processor, start_index);
		}
		break;
	case 52:
		if constexpr (52 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 52>(
			    in, out, processor, start_index);
		}
		break;
	case 53:
		if constexpr (53 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 53>(
			    in, out, processor, start_index);
		}
		break;
	case 54:
		if constexpr (54 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 54>(
			    in, out, processor, start_index);
		}
		break;
	case 55:
		if constexpr (55 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 55>(
			    in, out, processor, start_index);
		}
		break;
	case 56:
		if constexpr (56 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 56>(
			    in, out, processor, start_index);
		}
		break;
	case 57:
		if constexpr (57 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 57>(
			    in, out, processor, start_index);
		}
		break;
	case 58:
		if constexpr (58 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 58>(
			    in, out, processor, start_index);
		}
		break;
	case 59:
		if constexpr (59 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 59>(
			    in, out, processor, start_index);
		}
		break;
	case 60:
		if constexpr (60 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 60>(
			    in, out, processor, start_index);
		}
		break;
	case 61:
		if constexpr (61 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 61>(
			    in, out, processor, start_index);
		}
		break;
	case 62:
		if constexpr (62 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 62>(
			    in, out, processor, start_index);
		}
		break;
	case 63:
		if constexpr (63 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 63>(
			    in, out, processor, start_index);
		}
		break;
	case 64:
		if constexpr (64 <= N_BITS) {
			switch_start_index<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, processor_T, LoaderT, 64>(
			    in, out, processor, start_index);
		}
		break;
	}
}

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES, typename OutputProcessor>
struct BitUnpackerSwitchCase : BitUnpackerBase<T> {
	using UINT_T = typename utils::same_width_uint<T>::type;

	const UINT_T* __restrict in;
	const vbw_t     value_bit_width;
	OutputProcessor processor;
	si_t            start_index = 0;

	__device__ __forceinline__ BitUnpackerSwitchCase(const UINT_T* __restrict in,
	                                                 const lane_t    lane,
	                                                 const vbw_t     value_bit_width,
	                                                 OutputProcessor processor)
	    : in(in + lane)
	    , value_bit_width(value_bit_width)
	    , processor(processor) {
	}

	__device__ __forceinline__ void unpack_next_into(T* __restrict out) override {
		switch_value_bit_width<T, UNPACK_N_VECTORS, UNPACK_N_VALUES, OutputProcessor, CacheLoader<T, UNPACK_N_VECTORS>>(
		    in, out, processor, value_bit_width, start_index);
		start_index += UNPACK_N_VALUES;
	}
};

}} // namespace flsgpu::device

#endif // FLS_SWITCH_CASE_CUH
