#ifndef FLS_COR_PRM_BITPACK_HPP
#define FLS_COR_PRM_BITPACK_HPP

#include "fls/cor/fun.hpp"
#include "fls/utl/util.hpp"

// clang-format off
namespace fastlanes {
class Vec;
class Page;
class CompressState;
class DecompressState;
} // namespace fastlanes
// clang-format on

namespace fastlanes { namespace bitpack {
/*---------------------------------------------------------------------------------------------------------------------\
 * Compress
\---------------------------------------------------------------------------------------------------------------------*/
void Compress64(Vec& vec_src, Vec& vec_des, CompressState& cpmr_state);
void Compress32(Vec& vec_src, Vec& vec_des, CompressState& cpmr_state);
void Compress16(Vec& vec_src, Vec& vec_des, CompressState& cpmr_state);
void Compress08(Vec& vec_src, Vec& vec_des, CompressState& cpmr_state);

/*---------------------------------------------------------------------------------------------------------------------\
 * GetCompress
\---------------------------------------------------------------------------------------------------------------------*/
template <typename T>
cmpr_fun_t GetCompress() {
	if (std::is_same<T, uint64_t>()) {
		return Compress64;
	}
	if (std::is_same<T, uint32_t>()) {
		return Compress32;
	}
	if (std::is_same<T, uint16_t>()) {
		return Compress16;
	}
	if (std::is_same<T, uint8_t>()) {
		return Compress08;
	}
	if (std::is_same<T, int64_t>()) {
		return Compress64;
	}
	if (std::is_same<T, int32_t>()) {
		return Compress32;
	}
	if (std::is_same<T, int16_t>()) {
		return Compress16;
	}
	if (std::is_same<T, int8_t>()) {
		return Compress08;
	}
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Decompress
\---------------------------------------------------------------------------------------------------------------------*/
void Decompress64(Page&, Vec&, DecompressState&);
void Decompress32(Page&, Vec&, DecompressState&);
void Decompress16(Page&, Vec&, DecompressState&);
void Decompress08(Page&, Vec&, DecompressState&);

/*---------------------------------------------------------------------------------------------------------------------\
 * GetDecompress
\---------------------------------------------------------------------------------------------------------------------*/
// template <typename T>
// de_cmpr_fun_t GetDecompress() {
//	if (std::is_same<T, uint64_t>()) { return Decompress64; }
//	if (std::is_same<T, uint32_t>()) { return Decompress32; }
//	if (std::is_same<T, uint16_t>()) { return Decompress16; }
//	if (std::is_same<T, uint8_t>()) { return Decompress08; }
//	if (std::is_same<T, int64_t>()) { return Decompress64; }
//	if (std::is_same<T, int32_t>()) { return Decompress32; }
//	if (std::is_same<T, int16_t>()) { return Decompress16; }
//	if (std::is_same<T, int8_t>()) { return Decompress08; }
// }
}}     // namespace fastlanes::bitpack
#endif // FLS_COR_PRM_BITPACK_HPP
