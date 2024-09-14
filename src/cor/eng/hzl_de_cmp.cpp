#include "fls/cor/eng/hzl_de_cmp.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/ffor/ffor_exp.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/rec_hdr.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls_gen/unffor/unffor.hpp"
#include <fls/cor/prm/fsst/fsst.h>

namespace fastlanes {
template <typename T>
THzlDeCmp<T>::THzlDeCmp() = default;

template <typename T>
void THzlDeCmp<T>::Decompress(const sp<Exp>& exp_sp, Page& a_page) {
	auto* rpn = exp_sp->cmpr_rpn();

	for (n_t i {0}; i < rpn->des_buf_c; ++i) {
		if (!rpn->is_compressed[i]) { continue; }
		decompress_buf(a_page.params.arr[i], a_page.buf_arr[i]);
		a_page.params.arr[i] = a_page.buf_arr[i].mutable_data();
	}
}

template <typename T>
void THzlDeCmp<T>::decompress_buf(uint8_t* src_p, Buf& des_buf) {
	if constexpr (std::is_same_v<T, bool>) {
		FLS_ABORT("Not Supported")
	}
	/**/
	else if constexpr (std::is_same_v<T, float>) {
		FLS_ABORT("Not Supported")
	}
	/**/
	else if constexpr (std::is_same_v<T, double>) {
		FLS_ABORT("Not Supported")
	}
	/**/
	else if constexpr (std::is_same_v<T, uint64_t> || std::is_same_v<T, idx_t>) {
		rec_hdr hdr;
		while (true) {
			std::memcpy(&hdr, src_p, sizeof(rec_hdr));
			src_p += sizeof(rec_hdr);
			switch (hdr.bw) {
			case CFG::REC::SPECIAL_BW: {
				//	[fixme] push dw
				n_t sz = *reinterpret_cast<T*>(hdr.base);
				std::memcpy(des_buf.end(), src_p, sz);
				return;
			}
			default:
				generated::unffor::fallback::scalar::unffor(reinterpret_cast<T*>(src_p),
				                                            reinterpret_cast<T*>(des_buf.end()),
				                                            hdr.bw,
				                                            reinterpret_cast<T*>(hdr.base));
				src_p += ffor_prm<T>::vec_sz(hdr.bw);
				auto* exc_arr     = reinterpret_cast<T*>(src_p + hdr.exc_c * sizeof(pos_t));
				auto* exc_pos_arr = reinterpret_cast<uint16_t*>(src_p);
				auto* out_arr     = reinterpret_cast<T*>(des_buf.end());

				for (uint16_t i {0}; i < hdr.exc_c; ++i) {
					auto next_pos     = exc_pos_arr[i];
					out_arr[next_pos] = exc_arr[i];
				}

				des_buf.Advance(vec_bsz<T>());
				src_p += hdr.exc_c * (sizeof(pos_t) + sizeof(T));
			}
		}
	}
	/**/
	else {
		FLS_ABORT("Not Supported")
	}
}

template <typename T>
void THzlDeCmp<T>::UNFFOR(uint8_t* src_p, Buf& des_buf) {
	this->decompress_buf(const_cast<uint8_t*>(src_p), des_buf);
}

template <typename T>
void THzlDeCmp<T>::UNFSST(uint8_t* src_p, Buf& offs_buff, Buf& data_buffs, n_t tup_c) {
	fsst_decoder_t fsst_decoder;
	fsst_import(&fsst_decoder, src_p);
	src_p += FSST_MAXHEADER;

	auto* len_arr = reinterpret_cast<ofs_t*>(src_p);
	src_p += tup_c * sizeof(ofs_t);
	auto* str_p = src_p;

	auto* off_out_arr = reinterpret_cast<ofs_t*>(offs_buff.mutable_data());

	for (n_t i {0}; i < tup_c; ++i) {
		/* IN: use this symbol table for compression. */
		/* IN: byte-length of compressed string. */
		/* IN: compressed string. */
		/* IN: byte-length of output buffer. */
		/* OUT: memory buffer to put the decompressed string in. */

		len_t cur_len {0UL};

		// TODO[LONG_STRING]
		cur_len = static_cast<len_t>(
		    fsst_decompress(&fsst_decoder, len_arr[i], str_p, data_buffs.Capacity(), data_buffs.end()));

		str_p += len_arr[i];
		data_buffs.Advance(cur_len);
		if (i == 0) {
			off_out_arr[i] = cur_len;
		} else {
			off_out_arr[i] = cur_len + off_out_arr[i - 1];
		}
	}
}

template <typename T>
void THzlDeCmp<T>::UNALP(uint8_t* src_p, Buf& des_buf) {
	if constexpr (std::is_same_v<T, dbl_pt>) {
		//		alp_hdr hdr;
		//		std::memcpy(&hdr, src_p, sizeof(alp_hdr));
		//		std::memcpy(des_buf.mutable_data(), src_p + sizeof(alp_hdr), hdr.n_t * sizeof(dbl_pt));
	} else {
		FLS_ABORT("Not Supported")
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(THzlDeCmp)

} // namespace fastlanes