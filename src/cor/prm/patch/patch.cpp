#include "fls/cor/prm/patch/patch.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/utl/bit_util.hpp"

#pragma clang diagnostic ignored "-Wconversion"

namespace fastlanes {
template <typename T>
bool typed_patch<T>::is_exception(T lower_bound, T upper_bound, T val) {
	if constexpr (std::is_same<T, uint64_t>() || std::is_same<T, uint32_t>() || std::is_same<T, uint16_t>() ||
	              std::is_same<T, uint8_t>()) {
		if (val <= upper_bound && val >= lower_bound) {
			return false;
		}
		return true;
	} else {
		FLS_ABORT("this is not supported!")
		return false;
	}
}

void patch::b_patch_compress(rle_idx_t arr[], rle_idx_t c, bitmap_t bitmap) {
	for (n_t i {0}; i < CFG::BitMap::UNIT_C; ++i) {
		bitmap[i] = 0;
	}

	for (auto i {0}; i < c; ++i) {
		rle_idx_t unit_num     = arr[i] / CFG::BitMap::UNIT_BIT; // Which unit?
		rle_idx_t relative_idx = arr[i] % CFG::BitMap::UNIT_BIT; // Where in the unit?
		bit::set(bitmap[unit_num], relative_idx);
	}
}

bool patch::is_compulsory_exc(rle_idx_t curr, rle_idx_t next, uint64_t range) {
	FLS_ASSERT_CORRECT_RANGE(range)

	return static_cast<uint64_t>(next - curr) > range;
}

template <typename T>
n_t typed_patch<T>::count_exceptions(const T                      lower_bound,
                                     const T                      upper_bound,
                                     const std::vector<T>&        val_vec,
                                     const std::vector<uint16_t>& rep_vec) {

	if constexpr (std::is_same<T, uint64_t>() || std::is_same<T, uint32_t>() || std::is_same<T, uint16_t>() ||
	              std::is_same<T, uint8_t>()) {
		FLS_ASSERT(!val_vec.empty(), "an empty vec", " ");
		FLS_ASSERT(!rep_vec.empty(), "an empty vec", " ");

		n_t  result {0};
		bool is_exc {false};

		for (n_t i = 0; i < val_vec.size(); ++i) {
			is_exc = is_exception(lower_bound, upper_bound, val_vec[i]);
			if (!is_exc) {
				continue;
			}
			/* It is an exception.
			 * Increase the number of exception by the repetition of this value.
			 */
			result += rep_vec[i];
		}

		return result;
	} else {
		FLS_ABORT("this is not supported!")
		return 0;
	}
}

template <typename T>
void typed_patch<T>::b_patch_decompress(T* out_p, uint64_t* bitmap, T* exc_p) {
	int    c {0};
	unit_t unit;
	for (size_t i {0}; i < CFG::BitMap::UNIT_C; ++i) {
		unit = bitmap[i];
		while (unit != 0) {
			uint64_t t        = unit & -unit;
			int      r        = __builtin_ctzll(unit);
			out_p[i * 64 + r] = exc_p[c++];
			unit ^= t;
		}
	}
}

template <typename T>
void typed_patch<T>::l_patch_decompress(T* in, rle_idx_t first, rle_idx_t c) {
}

template <typename T>
void typed_patch<T>::l_patch_compress(T* in, T* exc, rle_idx_t arr[], rle_idx_t c, n_t max_range) {
	//	if (stt.exc_c == 0) {
	//		/* push the pos of first exception */
	//		des_vec.arr_arr[stt.cur_des_arr + 1].UnsafeAppend(&stt.exc_c, sizeof(pos_t));
	//		/* push the number of exceptions */
	//		des_vec.arr_arr[stt.cur_des_arr + 1].UnsafeAppend(&stt.exc_c, sizeof(pos_t));
	//
	//		stt.cur_des_arr += 2;
	//
	//		return;
	//	}
	//
	//	if (stt.exc_c == 1) {
	//		/* push the pos of first exception */
	//		des_vec.arr_arr[stt.cur_des_arr + 1].UnsafeAppend(&stt.exc_pos_arr, sizeof(pos_t));
	//		/* push the number of exceptions */
	//		des_vec.arr_arr[stt.cur_des_arr + 1].UnsafeAppend(&stt.exc_c, sizeof(pos_t));
	//		/* push the first exception */
	//		des_vec.arr_arr[stt.cur_des_arr + 0].UnsafeAppend(exc_arr, sizeof(T));
	//		=
	//		    stt.cur_des_arr += 2;
	//
	//		return;
	//	}
	//
	//	/* push the pos of first exception */
	//	des_vec.arr_arr[stt.cur_des_arr + 1].UnsafeAppend(&stt.exc_pos_arr[0], sizeof(pos_t));
	//	/* push the first exception */
	//	des_vec.arr_arr[stt.cur_des_arr + 0].UnsafeAppend(exc_arr + 0, sizeof(T));
	//
	//	T     curr_pos  = stt.exc_pos_arr[0];
	//	T     next_pos  = stt.exc_pos_arr[1];
	//	T     max_range = 1 << stt.bw;
	//	pos_t new_c {0};
	//	for (c_t i {1}; i < stt.exc_c; ++i) {
	//		curr_pos = stt.exc_pos_arr[i - 1];
	//		next_pos = stt.exc_pos_arr[i];
	//		while (patch::is_compulsory_exc(curr_pos, next_pos, max_range)) {
	//			/* Insert. */
	//			in_arr[curr_pos] = max_range + (*base_p) - 1;
	//			curr_pos += max_range;
	//			des_vec.arr_arr[stt.cur_des_arr + 0].UnsafeAppend(in_arr + curr_pos, sizeof(T));
	//			new_c++;
	//		}
	//		in_arr[curr_pos] = (next_pos - curr_pos) + (*base_p) - 1;
	//		des_vec.arr_arr[stt.cur_des_arr + 0].UnsafeAppend(exc_arr + i, sizeof(T));
	//	}
	//	in_arr[next_pos] = *(base_p);
	//
	//	/* forth, push the number of exceptions */
	//	stt.exc_c += new_c;
	//	des_vec.arr_arr[stt.cur_des_arr + 1].UnsafeAppend(&stt.exc_c, sizeof(pos_t));
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(typed_patch)

} // namespace fastlanes
