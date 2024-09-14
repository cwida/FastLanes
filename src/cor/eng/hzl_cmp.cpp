#include "fls/cor/eng/hzl_cmp.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/exp_fac.hpp"
#include "fls/cor/exp/ffor/ffor_exp.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/rec_hdr.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls/cor/prm/fsst/fsst_prm.hpp"
#include "fls/cor/prm/patch/patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/stt/histogram.hpp"
#include "fls/stt/minmax.hpp"
#include "fls/utl/util.hpp"
#include "fls_gen/ffor/ffor.hpp"
#include <cmath>
#include <type_traits>

namespace fastlanes {
template <typename PT>
THzlCmp<PT>::THzlCmp() {
	for (auto& off : off_arr) {
		off = 0;
	}
};

template <typename PT>
n_t THzlCmp<PT>::Compress(const sp<Exp>& exp_sp, Page& a_page, CompressState& compress_state) {
	auto* rpn = exp_sp->cmpr_rpn();

	n_t ttl_sz {0};
	for (n_t i {0}; i < rpn->des_buf_c; ++i) {
		if (!rpn->is_compressed[i]) { continue; }
		ttl_sz += compress_buf(a_page.buf_arr[i], m_page.buf_arr[i], off_arr[i], compress_state);
	}

	return ttl_sz;
}

template <typename PT>
n_t THzlCmp<PT>::compress_buf(Buf& src_buf, Buf& des_buf, ofs_t& cur_src_off, CompressState& stt) {
	// TODO MOVE TO FFOR_STANDALONE
	if constexpr (std::is_same_v<PT, int16_t> || std::is_same_v<PT, bool> || std::is_same_v<PT, float>) {
		FLS_ABORT("Not Supported")
		return 0;
	}
	/**/
	else if constexpr (std::is_same_v<PT, uint64_t> || std::is_same_v<PT, idx_t>) {
		rec_hdr hdr {0, 0, 0, {0, 0, 0, 0, 0, 0, 0}};

		n_t before_sz = des_buf.length();

		// how many tuples remained?
		n_t tup_c = (src_buf.length() - cur_src_off) / sizeof(PT);
		// how many vec remained?
		n_t vec_c = tup_c / vec_n_tup();

		for (n_t i {0}; i < vec_c; ++i) {
			auto* in_p = reinterpret_cast<PT*>(src_buf.data_at(cur_src_off));
			/* copy data into stt_buf.*/
			Params<PT> best, next;
			memcpy(stt.tmp_vec, in_p, vec_bsz<PT>());

			/* [op]: the tmp buf is sorted already, the minmax is the first and last element.  */
			/* [op]: move to stt to reduce allocation. */
			auto histo   = Histogram<PT>::cal(reinterpret_cast<uint8_t*>(stt.tmp_vec));
			auto min_max = MinMax<PT>::cal(reinterpret_cast<uint8_t*>(stt.tmp_vec));
			n_t  base_c  = histo->rep_vec.size();

			best = ffor_prm<PT>::find_best_params(*histo, 0);

			/* Compute. */
			for (size_t j {1}; j < base_c; ++j) {
				next = ffor_prm<PT>::find_best_params(*histo, j);

				if (next.size() < best.size()) { best = next; }
			}

			// fallback to uncompressed uncompressed.
			if (best.bw == type_bit<PT>()) { return 0; }

			hdr.bw = best.bw;
			std::memset(hdr.base, 0, sizeof(base_t));
			std::memcpy(hdr.base, &best.base, sizeof(PT));
			FLS_ASSERT_CORRECT_BASE_UB(best.base, min_max->max)

			/* Add exception positions . */
			hdr.exc_c = 0;

			for (pos_t j {0}; j < static_cast<pos_t>(vec_n_tup()); ++j) {
				PT& val = reinterpret_cast<PT*>(in_p)[j];
				if (ffor_prm<PT>::is_exception(best, val)) { stt.exc_pos_arr[hdr.exc_c++] = j; }
			}
			des_buf.Append(&hdr, sizeof(hdr));

			auto* out_p = reinterpret_cast<PT*>(des_buf.end());
			generated::ffor::fallback::scalar::ffor(in_p, out_p, hdr.bw, reinterpret_cast<const PT*>(hdr.base));
			des_buf.Advance(ffor_prm<PT>::vec_sz(hdr.bw));

			// selection vector
			auto sel_vec_sz = hdr.exc_c * sizeof(pos_t);
			std::memcpy(des_buf.end(), stt.exc_pos_arr, sel_vec_sz);
			des_buf.Advance(sel_vec_sz);

			// exceptions
			for (pos_t j {0}; j < hdr.exc_c; ++j) {
				des_buf.Append(&in_p[stt.exc_pos_arr[j]], sizeof(PT));
			}
			cur_src_off += vec_bsz<PT>();

			FLS_LOG_TABLE_KEY_VALUE("rec_bw", std::to_string(hdr.bw))
			FLS_LOG_TABLE_KEY_VALUE("rec_exc_c", std::to_string(hdr.exc_c))
		}
		FLS_ASSERT_GE(vec_c * vec_bsz<PT>(), des_buf.length() - before_sz);
		auto improved_sz = (vec_c * vec_bsz<PT>()) - (des_buf.length() - before_sz);
		FLS_ASSERT_CORRECT_SZ(improved_sz)
		return improved_sz;

	}
	/**/
	else {
		FLS_ABORT("Not Supported")
		return 0;
	}
}

template <typename PT>
void THzlCmp<PT>::Swap(const sp<Exp>& exp_sp, Page& a_page) {
	auto* rpn = exp_sp->cmpr_rpn();

	for (n_t i {0}; i < rpn->des_buf_c; ++i) {
		if (!rpn->is_compressed[i]) { continue; }
		a_page.buf_arr[i].Swap(m_page.buf_arr[i]);
	}
}

template <typename PT>
void THzlCmp<PT>::Reset() {
	m_page.Reset();
	for (auto& off : off_arr) {
		off = 0;
	}
}

template <typename PT>
void THzlCmp<PT>::Finalize(const sp<Exp>& exp_sp, Page& a_page) {
	auto* rpn = exp_sp->cmpr_rpn();

	for (n_t i {0}; i < rpn->des_buf_c; ++i) {
		if (!rpn->is_compressed[i]) { continue; }
		finalize_buf(a_page.buf_arr[i], m_page.buf_arr[i], off_arr[i]);
	}
}

template <typename PT>
void THzlCmp<PT>::finalize_buf(Buf& src_buf, Buf& des_buf, ofs_t& cur_src_off) {
	if constexpr (std::is_same<PT, bool>()) {
		FLS_ABORT("Not Supported")
	} else if constexpr (std::is_same<PT, float>()) {
		FLS_ABORT("Not Supported")
	} else {
		n_t sz = src_buf.length() - cur_src_off;

		rec_hdr hdr {CFG::REC::SPECIAL_BW, 0, 0, {0, 0, 0, 0, 0, 0, 0}};

		// Store base
		std::memset(hdr.base, 0, sizeof(base_t));
		std::memcpy(hdr.base, &sz, sizeof(base_t));

		des_buf.UnsafeAppend(&hdr, sizeof(rec_hdr));
		des_buf.UnsafeAppend(src_buf.data_at(cur_src_off), sz);
	}
}

template <typename PT>
void THzlCmp<PT>::FFOR(Buf& src_buf, Buf& des_buf, CompressState& stt) {
	ofs_t tmp {0};
	this->compress_buf(src_buf, des_buf, tmp, stt);
	this->finalize_buf(src_buf, des_buf, tmp);
}

template <typename PT>
void THzlCmp<PT>::FSST(Buf& src_data_buf, Buf& src_ofs_buf, Buf& des_data_buf, Buf& des_ofs_buf, CompressState& stt) {
	auto* str_p = const_cast<uint8_t*>(src_data_buf.mutable_data());
	auto* ofs_p = reinterpret_cast<uint32_t*>(src_ofs_buf.mutable_data());

	stt.fsst_encoder = fsst::build_fsst_encoder(stt.c, ofs_p, str_p);

	auto* encoder = reinterpret_cast<fsst_encoder_t*>(stt.fsst_encoder);

	auto str_p_in   = fsst::offset_to_pointer(stt.c, ofs_p, str_p);
	auto str_len_in = fsst::offset_to_length(stt.c, ofs_p);

	auto* out_p = des_data_buf.mutable_data();

	auto* len_out = reinterpret_cast<uint32_t*>(des_ofs_buf.mutable_data());
	auto* off_out = reinterpret_cast<uint8_t**>(stt.tmp_buf.mutable_data());

	fsst_compress(
	    encoder, stt.c, str_len_in->data(), str_p_in->data(), des_ofs_buf.Capacity(), out_p, len_out, off_out);
	des_ofs_buf.Advance(stt.c * sizeof(ofs_t));

	const len_t compressed_data_sz = static_cast<len_t>(off_out[stt.c - 1] - out_p) + len_out[stt.c - 1];
	des_data_buf.Advance(compressed_data_sz);
}

template <typename PT>
void THzlCmp<PT>::ALP(Buf& src_buf, Buf& des_buf, CompressState& compress_state) {
	/* FOR NOW, ONLY COPY. */
	if constexpr (std::is_same_v<PT, dbl_pt>) {
		/**/
		des_buf.Clone(src_buf);
	} else {
		FLS_ABORT("ALP ONLY WORKS FOR DOUBLE")
		throw std::runtime_error("ALP ONLY WORKS FOR DOUBLE");
	}
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(THzlCmp)

} // namespace fastlanes