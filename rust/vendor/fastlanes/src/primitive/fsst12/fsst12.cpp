#include "fls/primitive/fsst12/fsst12.hpp"
#include "fls/cor/prm/fsst12/libfsst12.hpp"
#include "fls/table/rowgroup.hpp"
#include <fls/cor/lyt/buf.hpp>

namespace fastlanes {

fsst12_encoder_t* fsst12_helper::make_fsst12(const FlsStrColumnView& col) {
	const auto n_vals = col.n_tuples;

	return fsst12_create(n_vals, col.fsst_length_ptr, col.fsst_string_p, CFG::FSST::NULL_TERMINATED);
}

fsst12_encoder_t* fsst12_helper::make_fsst12(n_t n_vals, Buf& length_buf, Buf& string_p_buf) {
	auto* lengths_p = reinterpret_cast<len_t*>(length_buf.data());
	auto* strings_p = reinterpret_cast<uint8_t**>(string_p_buf.data());

	return fsst12_create(n_vals, lengths_p, strings_p, CFG::FSST::NULL_TERMINATED);
}

// optimized adaptive *scalar* compression method
static inline ulong
compressBulk(Symbol12Map& symbolMap, ulong nlines, u32 lenIn[], u8* strIn[], ulong size, u8* out, u32 out_offsets[]) {
	u8* lim           = out + size;
	u8* start_pointer = out;

	ulong string_idx;
	for (string_idx = 0; string_idx < nlines; string_idx++) {
		u8* cur                 = strIn[string_idx];
		u8* end                 = cur + lenIn[string_idx];
		out_offsets[string_idx] = out - start_pointer;
		while (cur + 16 <= end && (lim - out) >= 8) {
			u64      word = fsst12_unaligned_load(cur);
			ulong    code = symbolMap.shortCodes[word & 0xFFFF];
			ulong    pos  = (u32)word; // key is first 4 bytes
			ulong    idx  = FSST12_HASH(pos) & (symbolMap.hashTabSize - 1);
			Symbol12 s    = symbolMap.hashTab[idx];
			word &= (0xFFFFFFFFFFFFFFFF >> (u8)s.gcl);
			if ((s.gcl < FSST12_GCL_FREE) && *(ulong*)s.symbol == word) {
				code = s.gcl >> 16;
			}
			cur += (code >> 12);
			u32 res = code & FSST12_CODE_MASK;
			word    = fsst12_unaligned_load(cur);
			code    = symbolMap.shortCodes[word & 0xFFFF];
			pos     = (u32)word; // key is first 4 bytes
			idx     = FSST12_HASH(pos) & (symbolMap.hashTabSize - 1);
			s       = symbolMap.hashTab[idx];
			word &= (0xFFFFFFFFFFFFFFFF >> (u8)s.gcl);
			if ((s.gcl < FSST12_GCL_FREE) && *(ulong*)s.symbol == word) {
				code = s.gcl >> 16;
			}
			cur += (code >> 12);
			res |= (code & FSST12_CODE_MASK) << 12;
			memcpy(out, &res, sizeof(u64));
			out += 3;
		}
		while (cur < end) {
			ulong code = symbolMap.findExpansion(Symbol12(cur, end));
			u32   res  = (code & FSST12_CODE_MASK);
			if (out + 8 > lim) {
				return string_idx; // u32 write would be out of bounds (out of output memory)
			}
			cur += code >> 12;
			if (cur >= end) {
				memcpy(out, &res, sizeof(u64));
				out += 2;
				break;
			}
			code = symbolMap.findExpansion(Symbol12(cur, end));
			res |= (code & FSST12_CODE_MASK) << 12;
			cur += code >> 12;
			memcpy(out, &res, sizeof(u64));
			out += 3;
		}
	}
	out_offsets[string_idx] = out - start_pointer;

	return string_idx;
}

inline ulong _compressImpl(Encoder12* e, ulong nlines, u32 lenIn[], u8* strIn[], ulong size, u8* output, u32* lenOut) {
	return compressBulk(*e->symbolMap, nlines, lenIn, strIn, size, output, lenOut);
}

inline ulong _compressAuto(Encoder12* e, ulong nlines, u32 lenIn[], u8* strIn[], ulong size, u8* output, u32* lenOut) {
	return _compressImpl(e, nlines, lenIn, strIn, size, output, lenOut);
}

size_t fsst12_helper::fsst12_compress(fsst12_encoder_t* encoder,
                                      size_t            nstrings,
                                      uint32_t          len_in[],
                                      unsigned char*    str_in[],
                                      size_t            out_size,
                                      unsigned char*    output,
                                      ofs_t*            out_offsets) {
	// to be faster than scalar, simd needs 64 lines or more of length >=12; or fewer lines, but big ones (totLen >
	// 32KB)
	return _compressAuto((Encoder12*)encoder, nstrings, len_in, str_in, out_size, output, out_offsets);
}

} // namespace fastlanes