#ifndef FLS_ENCODER_ASSERT_EQ_HPP
#define FLS_ENCODER_ASSERT_EQ_HPP

#pragma clang diagnostic ignored "-Wconversion"

#include "fls/common/string.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/variant.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/cor/prm/fsst12/fsst12.h"
#include "fls/encoder/col_encoder.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include <sstream>

namespace fastlanes {
template <typename PT>
std::string save_as_future_case(const PT* values, idx_t start_idx) {
	std::stringstream ss;
#ifndef NDEBUG
	if constexpr (std::is_same_v<PT, str_pt>) {
		for (uint32_t i {0}; i < vec_sz(); ++i) {
			const auto& val = values[start_idx + i];
			ss << "\"" << val << "\", ";
		}
	} else if constexpr (std::is_same_v<PT, i64_pt>) {
		for (auto i {0}; i < vec_sz(); ++i) {
			auto val = values[start_idx + i];
			ss << val << ", ";
		}
	}
#endif
	return ss.str();
}

template std::string save_as_future_case(const str_pt* values, idx_t start_idx);
template std::string save_as_future_case(const i64_pt* values, idx_t start_idx);
template std::string save_as_future_case(const dbl_pt* values, idx_t start_idx);

using generated::untranspose::fallback::scalar::untranspose_i;

template <typename PT>
using assert_fun_t = void (*)(Vec*, const PT* data_p, idx_t start_idx, ExpT exp); //

template <typename PT>
void assert_eq(Vec* vec, const PT* data_p, idx_t start_idx, ExpT exp) {
	switch (exp) {
	case ExpT::INVALID: {
		throw std::runtime_error("it is invalid");
	}
	case ExpT::UNDECIDED: {
		throw std::runtime_error("it is undecided");
	}
	case ExpT::UNCOMPRESSED:
	case ExpT::BYTE_ARR:
	case ExpT::FFOR:
	case ExpT::DELTA: {
		if constexpr (std::is_same<PT, str_pt>()) {
			uint32_t untransposed[1024] = {0};
			untranspose_i(vec->buf_arr[1].mutable_data<uint32_t>(), untransposed);

			auto bsz_vec_up        = Str::get_bsz_vec(untransposed, vec_sz());
			auto normal_ofs_vec_up = Str::to_normal_offset(untransposed, vec_sz());

			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				auto size = (*bsz_vec_up)[i];
				auto ofs  = (*normal_ofs_vec_up)[i];

				if (const bool equal = size == data_p[start_idx + i].size(); !equal) {
					throw std::runtime_error("does not match");
				}

				for (idx_t j {0}; j < size; ++j) {
					const bool equal = vec->buf_arr[0].data_at(ofs)[j] ==
					                   reinterpret_cast<const uint8_t*>(data_p[start_idx + i].data())[j];
					if (!equal) {
						string error_message = string(" Not Equal :") + string("value at position: ") +
						                       std::to_string(start_idx) + std::to_string(i) +
						                       " | byte at: " + std::to_string(j) + "\nVec:\n" +
						                       save_as_future_case<PT>(data_p, start_idx);

						throw std::runtime_error(error_message);
					}
				}
			}

			return;
		}
		/**/
		else if constexpr (std::is_same_v<PT, i64_pt>) {
			uint64_t untransposed[CFG::VEC_SZ] = {0};
			untranspose_i(reinterpret_cast<const uint64_t*>(vec->buf_arr[0].data()), untransposed);
			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				const bool equal = untransposed[i] == data_p[start_idx + i];
				if (!equal) {
					string error_message = "the arrow array offset is: " + std::to_string(start_idx) +
					                       std::to_string(i) + " vec:\n" +
					                       save_as_future_case<i64_pt>(data_p, start_idx);
					throw std::runtime_error(error_message);
				}
			}

			return;
		}
		/**/
		else if constexpr (std::is_same_v<PT, dbl_pt>) {
			dbl_pt untransposed[CFG::VEC_SZ] = {0};
			untranspose_i(reinterpret_cast<const dbl_pt*>(vec->buf_arr[0].data()), untransposed);
			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				const bool equal = untransposed[i] == data_p[start_idx + i];
				if (!equal) {
					string error_message = string("the arrow array offset is: ") + std::to_string(start_idx) +
					                       std::to_string(i) + " vec:\n" +
					                       save_as_future_case<dbl_pt>(data_p, start_idx);
				}
			}

			return;
		}
		/**/
		throw std::runtime_error("UNREACHABLE");
	}
	case ExpT::RLE: {
		if constexpr (std::is_same<PT, str_pt>()) {
			// ASSERT_EQ(0, 1);
		}
		/**/
		else if constexpr (std::is_same<PT, i64_pt>()) {
			uint64_t transposed[1024];
			uint64_t untransposed[1024];
			vec->flatten_to(transposed);
			untranspose_i(transposed, untransposed);
			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				const bool equal = untransposed[i] == data_p[start_idx + i];
				if (!equal) {
					string message = "the arrow array offset is: " + std::to_string(start_idx) + std::to_string(i) +
					                 " vec:\n" + save_as_future_case<PT>(data_p, start_idx);
					throw std::runtime_error(message);
				}
			}
			return;
		}
		/**/
		else if constexpr (std::is_same<PT, dbl_pt>()) {
			dbl_pt transposed[1024];
			dbl_pt untransposed[1024];
			vec->flatten_to(transposed);
			untranspose_i(transposed, untransposed);
			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				const bool equal = untransposed[i] == data_p[start_idx + i];
				if (!equal) {
					string error_message = "value at position: " + std::to_string(start_idx) + std::to_string(i) +
					                       " | byte at: " + std::to_string(i) + "\nVec:\n" +
					                       save_as_future_case<PT>(data_p, start_idx);
					throw std::runtime_error(error_message);
				}
			}
			return;
		}
		throw std::runtime_error("UNREACHABLE");
	}
	case ExpT::FSST: {
		if constexpr (std::is_same<PT, str_pt>()) {
			auto* str_p   = vec->buf_arr[vec->arr_c + 0].mutable_data();
			auto* off_arr = vec->buf_arr[vec->arr_c + 1].mutable_data<uint32_t>();

			FLS_ASSERT_NOT_NULL_POINTER(vec->fsst_decoder_up.get())

			uint32_t untransposed[1024] = {0};
			untranspose_i(off_arr, untransposed);

			auto bsz_vec_up        = Str::get_bsz_vec(untransposed, vec_sz());
			auto normal_ofs_vec_up = Str::to_normal_offset(untransposed, vec_sz());

			Buf      decompress_buf;
			uint8_t* out_p = decompress_buf.mutable_data();

			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				/* IN: use this symbol table for compression. */
				/* IN: byte-length of compressed string. */
				/* IN: compressed string. */
				/* IN: byte-length of output buffer. */
				/* OUT: memory buffer to put the decompressed string in. */

				auto size = data_p[start_idx + i].size();
				fsst_decompress(vec->fsst_decoder_up.get(),
				                (*bsz_vec_up)[i],
				                str_p + (*normal_ofs_vec_up)[i],
				                decompress_buf.Capacity(),
				                out_p);

				for (idx_t j {0}; j < size; ++j) {
					const bool equal = out_p[j] == reinterpret_cast<const uint8_t*>(data_p[start_idx + i].data())[j];
					if (!equal) {
						string error_message = "value at position: " + std::to_string(start_idx) + std::to_string(i) +
						                       " | byte at: " + std::to_string(j) + "\nVec:\n" +
						                       save_as_future_case<PT>(data_p, start_idx);
						throw std::runtime_error(error_message);
					}
				}
			}
			return;
		}
		/**/
		throw std::runtime_error("UNREACHABLE");
	}
	case ExpT::FSST12: {
		if constexpr (std::is_same<PT, str_pt>()) {
			auto* str_p   = vec->buf_arr[vec->arr_c + 0].mutable_data();
			auto* off_arr = vec->buf_arr[vec->arr_c + 1].mutable_data<uint32_t>();

			FLS_ASSERT_NOT_NULL_POINTER(vec->fsst12_decoder_up.get())

			uint32_t untransposed[1024] = {0};
			untranspose_i(off_arr, untransposed);

			auto bsz_vec_up        = Str::get_bsz_vec(untransposed, vec_sz());
			auto normal_ofs_vec_up = Str::to_normal_offset(untransposed, vec_sz());

			Buf      decompress_buf;
			uint8_t* out_p = decompress_buf.mutable_data();

			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				/* IN: use this symbol table for compression. */
				/* IN: byte-length of compressed string. */
				/* IN: compressed string. */
				/* IN: byte-length of output buffer. */
				/* OUT: memory buffer to put the decompressed string in. */

				auto decompresed_size = fsst12_decompress(vec->fsst12_decoder_up.get(),
				                                          (*bsz_vec_up)[i],
				                                          str_p + (*normal_ofs_vec_up)[i],
				                                          decompress_buf.Capacity(),
				                                          out_p);

				auto org_size = data_p[start_idx + i].size();
				if (org_size != decompresed_size) {
					throw std::runtime_error("size does not match");
				}

				for (idx_t j {0}; j < org_size; ++j) {
					const bool equal = out_p[j] == reinterpret_cast<const uint8_t*>(data_p[start_idx + i].data())[j];
					if (!equal) {
						string error_message = string("value at position: ") + std::to_string(start_idx) +
						                       std::to_string(i) + " | byte at: " + std::to_string(j) + "\nVec:\n" +
						                       save_as_future_case<PT>(data_p, start_idx);
					}
				}
			}
			return;
		}
		/**/
		throw std::runtime_error("UNREACHABLE");
	}
	case ExpT::DICT:
	case ExpT::DICT_FRQ:
	case ExpT::DICT_VAL: {
		if constexpr (std::is_same<PT, str_pt>()) {
			auto* idx_arr = reinterpret_cast<idx_t*>(vec->buf_arr[vec->arr_c + 0].mutable_data());

			auto* byte_arr = vec->dict_up->data_buf.mutable_data();
			auto* ofs_arr  = reinterpret_cast<ofs_t*>(vec->dict_up->offs_buf.mutable_data());

			auto bsz_vec_up = Str::get_bsz_vec(ofs_arr, vec->dict_up->dict_hdr.entry_c);

			uint32_t untransposed[1024] = {0};
			untranspose_i(idx_arr, untransposed);

			for (ofs_t i {0}; i < CFG::VEC_SZ; ++i) {
				auto idx   = untransposed[i];
				auto start = ofs_arr[idx];
				auto size  = bsz_vec_up->data()[idx];
				for (idx_t k {start}, j {0}; k < size; ++k, ++j) {
					const bool equal = byte_arr[k] == data_p[start_idx + i].data()[j];
					if (!equal) {
						string error_message = "the arrow array offset is: " + std::to_string(start_idx) +
						                       std::to_string(i) + " vec:\n" +
						                       save_as_future_case<PT>(data_p, start_idx);
						throw std::runtime_error(error_message);
					}
				}
			}
			return;
		}
		/**/
		else if constexpr (std::is_same_v<PT, dbl_pt>) {
			auto* idx_arr  = reinterpret_cast<idx_t*>(vec->buf_arr[vec->arr_c + 0].mutable_data());
			auto* dic_data = reinterpret_cast<dbl_pt*>(vec->dict_up->data_buf.mutable_data());

			idx_t untransposed[1024] = {0};
			untranspose_i(idx_arr, untransposed);
			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				auto idx = untransposed[i];

				const bool equal = dic_data[idx] == data_p[start_idx + i];
				if (!equal) {
					string error_message = "the arrow array offset is: " + std::to_string(start_idx) +
					                       std::to_string(i) + " vec:\n" + save_as_future_case<PT>(data_p, start_idx);
					throw std::runtime_error(error_message);
				}
			}

			return;
		}
		/**/
		else if constexpr (std::is_same_v<PT, i64_pt>) {
			auto* idx_arr  = reinterpret_cast<idx_t*>(vec->buf_arr[vec->arr_c + 0].mutable_data());
			auto* dic_data = reinterpret_cast<i64_pt*>(vec->dict_up->data_buf.mutable_data());

			idx_t untransposed[1024] = {0};
			untranspose_i(idx_arr, untransposed);
			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				auto       idx   = untransposed[i];
				const bool equal = dic_data[idx] == data_p[start_idx + i];
				if (!equal) {
					string error_message = "the arrow array offset is: " + std::to_string(start_idx) +
					                       std::to_string(i) + " vec:\n" + save_as_future_case<PT>(data_p, start_idx);
					throw std::runtime_error(error_message);
				}
			}

			return;
		}
		/**/
		throw std::runtime_error("UNREACHABLE");
	}
	case ExpT::DICT_RLE: {
		if constexpr (std::is_same<PT, str_pt>()) {
			auto* byte_arr   = vec->dict_up->data_buf.mutable_data();
			auto* ofs_arr    = reinterpret_cast<ofs_t*>(vec->dict_up->offs_buf.mutable_data());
			auto  bsz_vec_up = Str::get_bsz_vec(ofs_arr, vec->dict_up->dict_hdr.entry_c);

			uint32_t idx_arr[1024];
			uint32_t untransposed[1024];
			vec->flatten_to(idx_arr);
			untranspose_i(idx_arr, untransposed);

			for (ofs_t i {0}; i < CFG::VEC_SZ; ++i) {
				auto idx   = untransposed[i];
				auto start = ofs_arr[idx];
				auto size  = bsz_vec_up->data()[idx];
				for (idx_t k {start}, j {0}; k < size; ++k, ++j) {
					const bool equal = byte_arr[k] == data_p[start_idx + i].data()[j];
					if (!equal) {
						string error_message = "the arrow array offset is: " + std::to_string(start_idx) +
						                       std::to_string(i) + " vec:\n" +
						                       save_as_future_case<PT>(data_p, start_idx);
						throw std::runtime_error(error_message);
					}
				}
			}
			return;

		}
		/**/
		else if constexpr (std::is_same<PT, i64_pt>()) {
			uint32_t transposed[1024];
			uint32_t untransposed[1024];
			vec->flatten_to(transposed);
			untranspose_i(transposed, untransposed);

			auto* dic_data = reinterpret_cast<int64_t*>(vec->dict_up->data_buf.mutable_data());

			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				auto       idx   = untransposed[i];
				const bool equal = dic_data[idx] == data_p[start_idx + i];
				if (!equal) {
					string error_message = "the arrow array offset is: " + std::to_string(start_idx) +
					                       std::to_string(i) + " vec:\n" + save_as_future_case<PT>(data_p, start_idx);
					throw std::runtime_error(error_message);
				}
			}

			return;
		}
		/**/
		else if constexpr (std::is_same<PT, dbl_pt>()) {
			uint32_t transposed[1024];
			uint32_t untransposed[1024];
			vec->flatten_to(transposed);
			untranspose_i(transposed, untransposed);

			auto* dic_data = reinterpret_cast<dbl_pt*>(vec->dict_up->data_buf.mutable_data());

			for (auto i {0}; i < CFG::VEC_SZ; ++i) {
				auto       idx   = untransposed[i];
				const bool equal = dic_data[idx] == data_p[start_idx + i];
				if (!equal) {
					string string_message = "the arrow array offset is: " + std::to_string(start_idx) +
					                        std::to_string(i) + " vec:\n" + save_as_future_case<PT>(data_p, start_idx);
					throw std::runtime_error(string_message);
				}
			}

			return;
		}
		throw std::runtime_error("UNREACHABLE");
	}
	case ExpT::ALP: {
		// TODO [FIXME]
		return;
	}
		// TODO [FIXME]
	default:
		FLS_ABORT("IMPLEMENET ME")
		throw std::runtime_error("IMPLEMENT ME");
	}
}

template void assert_eq(Vec* vec, const dbl_pt* data_p, idx_t start_idx, ExpT exp);
void          assert_eq(Vec* vec, const i64_pt* data_p, idx_t start_idx, ExpT exp);
void          assert_eq(Vec* vec, const str_pt* data_p, idx_t start_idx, ExpT exp);
} // namespace fastlanes

#endif // FLS_ENCODER_ASSERT_EQ_HPP
