#include "fls/cor/eng/resolver.hpp"
#include "fls/api/prm.hpp"
#include "fls/cor/exp/exp_type.hpp"

namespace fastlanes {
template <typename T>
cmpr_fun_t resolver<T>::resolve_cmpr(prm_t pmr_type, fls_t fls_type, sp<TExp<T>> exp) {
	switch (pmr_type) {
	case prm_t::BITPACK:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return bitpack::GetCompress<uint8_t>();
		case fls_t::FLS16_T:
			return bitpack::GetCompress<uint16_t>();
		case fls_t::FLS32_T:
			return bitpack::GetCompress<uint32_t>();
		case fls_t::FLS64_T:
			return bitpack::GetCompress<uint64_t>();
		case fls_t::FLS_SMT:
			return bitpack::GetCompress<T>();
			// TODO [FIXME]
		default:
			return nullptr;
		}
	case prm_t::MEM_CPY:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return mem_cpy::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return mem_cpy::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return mem_cpy::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return mem_cpy::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return mem_cpy::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::ANALYZE:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return ffor_prm<uint8_t>::ResolveAnalyzeFunc();
		case fls_t::FLS16_T:
			return ffor_prm<uint16_t>::ResolveAnalyzeFunc();
		case fls_t::FLS32_T:
			return ffor_prm<uint32_t>::ResolveAnalyzeFunc();
		case fls_t::FLS64_T:
			return ffor_prm<uint64_t>::ResolveAnalyzeFunc();
		case fls_t::FLS_SMT:
			return ffor_prm<T>::ResolveAnalyzeFunc();
		default:
			return nullptr;
		}
	case prm_t::PA_ANALYZE:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return ffor_prm<uint8_t>::ResolvePatchAnalyzeFunc();
		case fls_t::FLS16_T:
			return ffor_prm<uint16_t>::ResolvePatchAnalyzeFunc();
		case fls_t::FLS32_T:
			return ffor_prm<uint32_t>::ResolvePatchAnalyzeFunc();
		case fls_t::FLS64_T:
			return ffor_prm<uint64_t>::ResolvePatchAnalyzeFunc();
		case fls_t::FLS_SMT:
			return ffor_prm<T>::ResolvePatchAnalyzeFunc();
		default:
			return nullptr;
		}
	case prm_t::FFOR:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return ffor_prm<uint8_t>::ResolveCompressFunc();
		case fls_t::FLS16_T:
			return ffor_prm<uint16_t>::ResolveCompressFunc();
		case fls_t::FLS32_T:
			return ffor_prm<uint32_t>::ResolveCompressFunc();
		case fls_t::FLS64_T:
			return ffor_prm<uint64_t>::ResolveCompressFunc();
		case fls_t::FLS_SMT:
			return ffor_prm<T>::ResolveCompressFunc();
		default:
			return nullptr;
		}
	case prm_t::MEM_TRS:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return mem_trs::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return mem_trs::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return mem_trs::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return mem_trs::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return mem_trs::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::LL_PATCH:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return ll_patch::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return ll_patch::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return ll_patch::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return ll_patch::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return ll_patch::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::S_PATCH:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return s_patch::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return s_patch::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return s_patch::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return s_patch::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return s_patch::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::B_PATCH:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return b_patch::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return b_patch::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return b_patch::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return b_patch::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return b_patch::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::RSUM:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return rsum::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return rsum::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return rsum::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return rsum::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return rsum::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::RLE:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return rle::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return rle::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return rle::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return rle::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return rle::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::TRS:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return trs::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return trs::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return trs::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return trs::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return trs::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::B_FFOR:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return b_ffor_prm::ResolveCompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return b_ffor_prm::ResolveCompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return b_ffor_prm::ResolveCompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return b_ffor_prm::ResolveCompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return b_ffor_prm::ResolveCompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::ALP: {
		switch (fls_type) {
		case fls_t::FLS08_T:
		case fls_t::FLS16_T:
		case fls_t::FLS32_T:
		case fls_t::FLS64_T:
		case fls_t::FLS_SMT:
			FLS_ABORT("NO")
		case fls_t::FLS_DBT:
			return alp_prm::ResolveCompressFunc<dbl_pt>();
		}
	}
	case prm_t::ZER_CPY:
	case prm_t::FACTOR:
	case prm_t::FSST:
	case prm_t::INVALID:
	default:
		FLS_ABORT("PRM NOT SUPPORTED")
		return nullptr;
	}
}

template <typename T>
de_cmpr_fun_t resolver<T>::resolve_de_cmpr(prm_t pmr_type, fls_t fls_type, sp<TExp<T>> exp) {
	switch (pmr_type) {
	case prm_t::MEM_TRS:
		return mem_trs::ResolveDecompressFunc<T>();
	case prm_t::MEM_CPY:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return mem_cpy::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return mem_cpy::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return mem_cpy::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return mem_cpy::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return mem_cpy::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::FFOR:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return ffor_prm<uint8_t>::ResolveDecompressFunc();
		case fls_t::FLS16_T:
			return ffor_prm<uint16_t>::ResolveDecompressFunc();
		case fls_t::FLS32_T:
			return ffor_prm<uint32_t>::ResolveDecompressFunc();
		case fls_t::FLS64_T:
			return ffor_prm<uint64_t>::ResolveDecompressFunc();
		case fls_t::FLS_SMT:
			return ffor_prm<T>::ResolveDecompressFunc();
		default:
			return nullptr;
		}
	case prm_t::LL_PATCH:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return ll_patch::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return ll_patch::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return ll_patch::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return ll_patch::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return ll_patch::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::S_PATCH:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return s_patch::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return s_patch::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return s_patch::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return s_patch::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return s_patch::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::B_PATCH:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return b_patch::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return b_patch::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return b_patch::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return b_patch::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return b_patch::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::RSUM:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return rsum::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return rsum::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return rsum::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return rsum::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return rsum::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::RLE:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return rle::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return rle::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return rle::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return rle::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return rle::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::TRS:
		switch (fls_type) {
		case fls_t::FLS08_T:
			return trs::ResolveDecompressFunc<uint8_t>();
		case fls_t::FLS16_T:
			return trs::ResolveDecompressFunc<uint16_t>();
		case fls_t::FLS32_T:
			return trs::ResolveDecompressFunc<uint32_t>();
		case fls_t::FLS64_T:
			return trs::ResolveDecompressFunc<uint64_t>();
		case fls_t::FLS_SMT:
			return trs::ResolveDecompressFunc<T>();
		default:
			return nullptr;
		}
	case prm_t::ALP: {
		switch (fls_type) {
		case fls_t::FLS08_T:
		case fls_t::FLS16_T:
		case fls_t::FLS32_T:
		case fls_t::FLS64_T:
		case fls_t::FLS_SMT:
			FLS_ABORT("NO")
		case fls_t::FLS_DBT:
			return alp_prm::ResolveDecompressFunc<dbl_pt>();
		}
	}
	case prm_t::BITPACK:
	case prm_t::ZER_CPY:
	case prm_t::FSST:
	case prm_t::FACTOR:
	case prm_t::INVALID:
	default:
		FLS_ABORT("NOT SUPPORTED")
	}

	FLS_ABORT("NOT SUPPORTED")
	return nullptr;
}

/*--------------------------------------------------------------------------------------------------------------------*\
+ Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(resolver)
} // namespace fastlanes