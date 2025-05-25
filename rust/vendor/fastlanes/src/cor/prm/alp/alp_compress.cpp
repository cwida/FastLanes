#include "alp.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/alp_prm.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls/primitive/ffor/ffor.hpp"

namespace fastlanes {
static void alp_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {

	// auto* dbl_arr = reinterpret_cast<dbl_pt*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());
	auto& alp_stt = *stt.eng_state.analyze_state_up->alp_dbl_state_up;

	// auto* exc_arr   = reinterpret_cast<dbl_pt*>(des_vec.buf_arr[stt.cur_des_buff + 0].mutable_data());
	// auto* pos_arr   = reinterpret_cast<uint16_t*>(des_vec.buf_arr[stt.cur_des_buff + 1].mutable_data());
	auto* exc_c_arr = reinterpret_cast<uint16_t*>(des_vec.buf_arr[stt.cur_des_buff + 2].mutable_data());
	auto* base_arr  = reinterpret_cast<int64_t*>(des_vec.buf_arr[stt.cur_des_buff + 3].mutable_data());
	auto* ffor_arr  = reinterpret_cast<int64_t*>(des_vec.buf_arr[stt.cur_des_buff + 5].mutable_data());

	uint8_t bw = 0;
	int64_t tmp_dig_arr[vec_sz()]; // TODO BUFFER_POOl
	// alp::encoder<double>::encode(dbl_arr, exc_arr, pos_arr, exc_c_arr, tmp_dig_arr, alp_stt); TODO
	alp::encoder<double>::analyze_ffor(tmp_dig_arr, bw, base_arr);
	generated::ffor::fallback::scalar::ffor(tmp_dig_arr, ffor_arr, bw, base_arr);

	auto      exc_c = exc_c_arr[0];
	alp_mtd_t alp_mtd {bw, alp_stt.exp, alp_stt.fac};

	des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAdvance(exc_c * sizeof(uint16_t));
	des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAdvance(exc_c * sizeof(uint16_t));
	des_vec.buf_arr[stt.cur_des_buff + 2].UnsafeAdvance(sizeof(uint16_t));
	des_vec.buf_arr[stt.cur_des_buff + 3].UnsafeAdvance(sizeof(int64_t));
	des_vec.buf_arr[stt.cur_des_buff + 4].UnsafeAppend(&alp_mtd, sizeof(alp_mtd_t));
	des_vec.buf_arr[stt.cur_des_buff + 5].UnsafeAdvance(ffor_prm<dbl_pt>::vec_sz(bw));

	stt.cur_des_buff += 6;
}

template <typename PT>
cmpr_fun_t alp_prm::ResolveCompressFunc() {
	if constexpr (std::is_same_v<PT, dbl_pt>) {
		return alp_compress;
	} else {
		FLS_ABORT("ONLY WORKS FOR DOUBLE")
	}

	FLS_ABORT("THIS IS NOT SUPPORTED!")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, alp_prm::ResolveCompressFunc)

} // namespace fastlanes