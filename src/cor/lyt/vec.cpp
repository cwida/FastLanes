#include "fls/cor/lyt/vec.hpp"
#include "fls/common/string.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/prm/fsst/fsst_prm.hpp"
#include "fls/cor/prm/fsst12/fsst12_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include <type_traits>

#pragma clang diagnostic ignored "-Wshorten-64-to-32"

namespace fastlanes {
static constexpr uint64_t VEC_SZ = 1024ULL * 1024;

Vec::Vec()
    : buf_arr {Buf(VEC_SZ), Buf(VEC_SZ), Buf(VEC_SZ), Buf(VEC_SZ), Buf(VEC_SZ), Buf(VEC_SZ)}
    , arr_c {0}
    , tup_c {0} {
}

void Vec::Reset() {
	for (auto& buff : buf_arr) {
		buff.Rewind(0);
	}

	arr_c = 0;
}

void Vec::FlushToPage(Page& page) {
	for (size_t i {0}; i < arr_c; ++i) {
		n_t sz = buf_arr[i].length();
		page.buf_arr[i].UnsafeAppend(buf_arr[i].data(), buf_arr[i].length());
		page.ep_arr_buf.UnsafeAppend(&sz, sizeof(uint16_t));
	}
}

template <typename T>
void Vec::Init(const T* in_arr, EngineState& stt) {
	if constexpr (std::is_arithmetic_v<T>) {
		FLS_ASSERT_NOT_NULL_POINTER(in_arr)

		auto exp_t = stt.analyze_state_up->m_exp_t;
		FLS_ASSERT_CORRECT_EXP_T(static_cast<uint8_t>(exp_t))

		if constexpr (std::is_same_v<T, int64_t> || std::is_same_v<T, dbl_pt>) {
			Reset();
			switch (exp_t) {
			case ExpT::RLE: {
				rle_idx_t pos_val;
				for (n_t i {0}; i < vec_n_tup(); ++i) {
					auto cur_val = in_arr[i];

					if (i == 0) {
						cur_val = in_arr[0];
						pos_val = 0;
						buf_arr[0].UnsafeAppend(&cur_val, sizeof(T));
						buf_arr[1].UnsafeAppend(&pos_val, sizeof(rle_idx_t));
						continue;
					}

					if (cur_val != in_arr[i - 1]) {
						buf_arr[0].UnsafeAppend(&cur_val, sizeof(T));
						pos_val += 1;
					}
					buf_arr[1].UnsafeAppend(&pos_val, sizeof(rle_idx_t));
				}

				return;
			}
			case ExpT::DICT_RLE: {
				auto idx_vec =
				    stt.analyze_state_up->dic_up->get_idx_vec(nullptr, reinterpret_cast<const uint8_t*>(in_arr));

				auto*     idx_arr = reinterpret_cast<idx_t*>(idx_vec->data());
				rle_idx_t pos_val;
				for (n_t i {0}; i < vec_n_tup(); ++i) {
					int64_t cur_val = idx_arr[i];

					if (i == 0) {
						cur_val = idx_arr[0];
						pos_val = 0;
						buf_arr[0].UnsafeAppend(&cur_val, sizeof(idx_t));
						buf_arr[1].UnsafeAppend(&pos_val, sizeof(rle_idx_t));
						continue;
					}

					if (cur_val != idx_arr[i - 1]) {
						buf_arr[0].UnsafeAppend(&cur_val, sizeof(idx_t));
						pos_val += 1;
					}
					buf_arr[1].UnsafeAppend(&pos_val, sizeof(rle_idx_t));
				}
				arr_c += 1;
			}
			case ExpT::DICT_VAL:
			case ExpT::DICT_FRQ:
			case ExpT::DICT: {
				auto idx_arr = stt.analyze_state_up->dic_up->get_idx_vec(nullptr, in_arr);

				buf_arr[arr_c + 0].UnsafeAppend(idx_arr->data(), vec_bsz<uint32_t>());

				arr_c += 1;
				return;
			}
			case ExpT::UNCOMPRESSED:
			case ExpT::BYTE_ARR:
			case ExpT::FFOR:
			case ExpT::ALP:
			case ExpT::DELTA: {
				[[maybe_unused]] auto* val_arr = reinterpret_cast<T*>(buf_arr[0].mutable_data());
				buf_arr[arr_c + 0].UnsafeAppend(in_arr, vec_bsz<T>());

				arr_c += 1;
				FLS_PLOG_KEY_VALUE("val_arr", ToStr::to_str<T>(val_arr));
				return;
			}
			case ExpT::TGT_EQUALITY:
			case ExpT::TGT_1T1:
			case ExpT::TGT_1TN:
			case ExpT::SRC_1T1:
			case ExpT::SRC_1TN:
			case ExpT::ALP_RD:
				break;
			case ExpT::INVALID:
			case ExpT::UNDECIDED:
			case ExpT::FSST:
			default: {
				FLS_ABORT("EXP IS NOT SUPPORTED!")
				return;
			}
			}
		}
	}
	/**/
	else if (std::is_same_v<T, str_pt>) {
		this->Reset();

		auto exp_t = stt.analyze_state_up->m_exp_t;
		FLS_ASSERT_CORRECT_EXP_T(static_cast<uint8_t>(exp_t))

		/*two buffs: hacky */
		Buf bytes;
		Buf smart_offsets;

		/*Extract bytes*/
		for (idx_t idx {0}; idx < vec_n_tup(); ++idx) {
			auto str = in_arr[idx];
			bytes.UnsafeAppend(str.data(), str.size());
		}

		/* Extract Offsets.
		 * Smart Offsets
		 */
		ofs_t cur_ofs {0};
		for (auto i {0ULL}; i < vec_n_tup(); ++i) {
			cur_ofs += static_cast<ofs_t>(in_arr[i].size());
			smart_offsets.UnsafeAppend(&cur_ofs, sizeof(ofs_t));
		}

		switch (exp_t) {
		case ExpT::FSST: {
			auto* encoder    = reinterpret_cast<fsst_encoder_t*>(stt.analyze_state_up->fsst_encoder);
			auto* str_arr    = bytes.mutable_data();
			auto* off_arr    = smart_offsets.mutable_data<ofs_t>();
			auto  str_p_in   = Str::smart_offset_to_pointer(vec_sz(), off_arr, str_arr);
			auto  str_len_in = fsst_wrapper::offset_to_length(vec_sz(), off_arr);

			auto* out_p   = buf_arr[arr_c + 0].mutable_data();
			auto* len_out = reinterpret_cast<uint32_t*>(buf_arr[arr_c + 3].mutable_data());
			auto* off_out = reinterpret_cast<uint8_t**>(buf_arr[arr_c + 2].mutable_data());
			/*
			    fsst_encoder_t *encoder,    IN: encoder obtained from fsst_create().
			    size_t          nstrings,   IN: number of strings in batch to compress.
			    size_t          len_in[],   IN: byte-lengths of the inputs
			    unsigned char  *str_in[],   IN: input string start pointers.
			    size_t          outsize,    IN: byte-length of output buffer.
			    unsigned char  *output,     OUT: memory buffer to put the compressed strings in (one after the other).
			    size_t          len_out[],  OUT: byte-lengths of the compressed strings.
			    unsigned char *str_out[] 	OUT: output string start pointers. Will all point into [output,output+size)
			   .*/

			fsst_compress(encoder, //
			              vec_n_tup(),
			              str_len_in->data(),
			              str_p_in->data(),
			              smart_offsets.Capacity(),
			              out_p,
			              len_out,
			              off_out);

			// smart-offsets.
			for (n_t i = 0; i < vec_n_tup() - 1; ++i) {
				len_out[i] = static_cast<uint32_t>(off_out[i + 1] - out_p);
				FLS_ASSERT_CORRECT_SMART_OFFSET(off_out[i + 1] - out_p)
			}
			len_out[1023] = len_out[1022] + len_out[1023];

			buf_arr[arr_c + 1].UnsafeAppend(len_out, vec_bsz<uint32_t>());

			arr_c += 2;

			FLS_PLOG_KEY_VALUE("byte_arr", ToStr::to_str<uint8_t>(buf_arr[0].mutable_data()));
			FLS_PLOG_KEY_VALUE("len_arr", ToStr::to_str<uint32_t>(buf_arr[1].mutable_data<uint32_t>()));
			FLS_PLOG_KEY_VALUE("str_pointer", ToStr::to_str<uint64_t>(buf_arr[2].mutable_data<uint64_t>()));
		} break;
		case ExpT::FSST12: {
			auto* encoder    = reinterpret_cast<fsst12_encoder_t*>(stt.analyze_state_up->fsst12_encoder);
			auto* str_arr    = bytes.mutable_data();
			auto* off_arr    = smart_offsets.mutable_data<ofs_t>();
			auto  str_p_in   = Str::smart_offset_to_pointer(vec_sz(), off_arr, str_arr);
			auto  str_len_in = fsst_wrapper::offset_to_length(vec_sz(), off_arr);

			auto* out_p   = buf_arr[arr_c + 0].mutable_data();
			auto* len_out = reinterpret_cast<uint32_t*>(buf_arr[arr_c + 3].mutable_data());
			auto* off_out = reinterpret_cast<uint8_t**>(buf_arr[arr_c + 2].mutable_data());

			/* Compress a batch of strings (on AVX512 machines best performance is obtained by compressing more than
			 * 32KB of string volume). */
			/* The output buffer must be large; at least "conservative space" (7+2*inputlength) for the first string for
			 * something to happen. */
			/* OUT: the number of compressed strings (<=n) that fit the output buffer. */
			/* IN: encoder obtained from fsst12_create(). */
			/* IN: number of strings in batch to compress. */
			/* IN: byte-lengths of the inputs */
			/* IN: input string start pointers. */
			/* IN: byte-length of output buffer. */
			/* OUT: memory buffer to put the compressed strings in (one after the other). */
			/* OUT: byte-lengths of the compressed strings. */
			/* OUT: output string start pointers. Will all point into [output,output+size). */

			fsst12_compress(encoder, //
			                vec_n_tup(),
			                str_len_in->data(),
			                str_p_in->data(),
			                smart_offsets.Capacity(),
			                out_p,
			                len_out,
			                off_out);

			// smart-offsets.
			for (n_t i = 0; i < vec_n_tup() - 1; ++i) {
				len_out[i] = static_cast<uint32_t>(off_out[i + 1] - out_p);
				FLS_ASSERT_CORRECT_SMART_OFFSET(off_out[i + 1] - out_p)
			}
			len_out[1023] = len_out[1022] + len_out[1023];

			buf_arr[arr_c + 1].UnsafeAppend(len_out, vec_bsz<uint32_t>());

			arr_c += 2;

			FLS_PLOG_KEY_VALUE("byte_arr", ToStr::to_str<uint8_t>(buf_arr[0].mutable_data()));
			FLS_PLOG_KEY_VALUE("len_arr", ToStr::to_str<uint32_t>(buf_arr[1].mutable_data<uint32_t>()));
			FLS_PLOG_KEY_VALUE("str_pointer", ToStr::to_str<uint64_t>(buf_arr[2].mutable_data<uint64_t>()));
		} break;
		case ExpT::DICT_VAL:
		case ExpT::DICT_FRQ:
		case ExpT::DICT: {
			auto idx_arr = stt.analyze_state_up->dic_up->get_idx_vec(smart_offsets.data<ofs_t>(), bytes.data());

			buf_arr[arr_c + 0].UnsafeAppend(idx_arr->data(), vec_bsz<uint32_t>());

			arr_c += 1;

			FLS_PLOG_KEY_VALUE("idx_arr",
			                   ToStr::to_str<uint32_t>(reinterpret_cast<uint32_t*>(buf_arr[0].mutable_data())));
		} break;
		case ExpT::DICT_RLE: {
			auto idx_vec = stt.analyze_state_up->dic_up->get_idx_vec(smart_offsets.data<ofs_t>(), bytes.data());

			auto*     idx_arr = reinterpret_cast<idx_t*>(idx_vec->data());
			rle_idx_t pos_val;
			for (n_t i {0}; i < vec_n_tup(); ++i) {
				int64_t cur_val = idx_arr[i];

				if (i == 0) {
					cur_val = idx_arr[0];
					pos_val = 0;
					buf_arr[0].UnsafeAppend(&cur_val, sizeof(idx_t));
					buf_arr[1].UnsafeAppend(&pos_val, sizeof(rle_idx_t));
					continue;
				}

				if (cur_val != idx_arr[i - 1]) {
					buf_arr[0].UnsafeAppend(&cur_val, sizeof(idx_t));
					pos_val += 1;
				}
				buf_arr[1].UnsafeAppend(&pos_val, sizeof(rle_idx_t));
			}
			arr_c += 2;
		} break;
		case ExpT::BYTE_ARR: {
			buf_arr[arr_c + 0].UnsafeAppend(bytes.data(), bytes.length());
			buf_arr[arr_c + 1].Clone(smart_offsets);
			arr_c += 2;

			FLS_PLOG_KEY_VALUE("byte_arr", ToStr::to_str<uint8_t>(buf_arr[0].mutable_data()));
			FLS_PLOG_KEY_VALUE("offset_arr", ToStr::to_str<uint32_t>(buf_arr[1].mutable_data<ofs_t>()));
		} break;
		default:
			FLS_ABORT("EXP IS NOT SUPPORTED!")
		}
	}
	/**/
	else {
		FLS_ABORT("NOT SUPPORTED TYPE")
	}
}

void Vec::Log() {
	// FLS_PRINT_4MSG("tup_c: ", std::to_string(tup_c), "arr_c", std::to_string(arr_c))
}

VecParam Vec::vec_param() {
	return {buf_arr[0].mutable_data(), buf_arr[1].mutable_data(), buf_arr[2].mutable_data()};
}

template <typename T>
void Vec::flatten_to(T* out_arr) {
	FLS_ASSERT_NOT_NULL_POINTER(out_arr)
	FLS_ASSERT_NOT_NULL_POINTER(buf_arr[0].data())
	FLS_ASSERT_NOT_NULL_POINTER(buf_arr[1].data())

	auto* val_arr = reinterpret_cast<T*>(buf_arr[0].mutable_data());
	auto* pos_arr = reinterpret_cast<rle_idx_t*>(buf_arr[1].mutable_data());

	for (n_t i {0}; i < vec_n_tup(); ++i) {
		out_arr[i] = val_arr[pos_arr[i]];
	}

	FLS_PLOG_KEY_VALUE("val_arr", ToStr::to_str<T>(val_arr));
	FLS_PLOG_KEY_VALUE("pos_arr", ToStr::to_str<rle_idx_t>(pos_arr));
}

Vec::~Vec() = default;

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
// clang-format off
template void Vec::Init<uint8_t>(const uint8_t *p,EngineState& stt);
template void Vec::Init<uint16_t>(const uint16_t *p,EngineState& stt);
template void Vec::Init<uint32_t>(const uint32_t *p,EngineState& stt);
template void Vec::Init<uint64_t>(const uint64_t *p,EngineState& stt);
template void Vec::Init<int8_t>(const int8_t *p,EngineState& stt);
template void Vec::Init<int16_t>(const int16_t *p,EngineState& stt);
template void Vec::Init<int32_t>(const int32_t *p,EngineState& stt);
template void Vec::Init<int64_t>(const int64_t *p,EngineState& stt);
template void Vec::Init<float>(const float *p,EngineState& stt);
template void Vec::Init<double>(const double *p,EngineState& stt);
template void Vec::Init<bool>(const bool *p,EngineState& stt);
template void Vec::Init<str_pt>(const str_pt *p,EngineState& stt);
/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
// clang-format off
template void Vec::flatten_to<dbl_pt>(dbl_pt *out_p);
template void Vec::flatten_to<uint64_t>(uint64_t *out_p);
template void Vec::flatten_to<uint32_t>(uint32_t *out_p);
template void Vec::flatten_to<uint16_t>(uint16_t *out_p);
template void Vec::flatten_to<uint8_t>(uint8_t *out_p);

} // namespace fastlanes