#include "fls/primitive/fsst/fsst.hpp"
#include "fls/cor/prm/fsst/libfsst.hpp"
#include "fls/table/rowgroup.hpp"
#include <fls/cor/lyt/buf.hpp>

namespace fastlanes {

fsst_encoder_t* fsst_helper::make_fsst(const FlsStrColumnView& col) {
	const auto n_vals = col.n_tuples;

	return fsst_create(n_vals, col.fsst_length_ptr, col.fsst_string_p, CFG::FSST::NULL_TERMINATED);
}

fsst_encoder_t* fsst_helper::make_fsst(n_t n_vals, Buf& length_buf, Buf& string_p_buf) {
	auto* lengths_p = reinterpret_cast<len_t*>(length_buf.data());
	auto* strings_p = reinterpret_cast<uint8_t**>(string_p_buf.data());

	return fsst_create(n_vals, lengths_p, strings_p, CFG::FSST::NULL_TERMINATED);
}

inline uint64_t fsst_unaligned_load(u8 const* v) {
	uint64_t ret;
	memcpy(&ret, v, sizeof(uint64_t)); // compiler will generate efficient code (unaligned load, where possible)
	return ret;
}

// optimized adaptive *scalar* compression method
static inline size_t compressBulk(SymbolTable& symbolTable,
                                  size_t       n_strings,
                                  u32          lenIn[],
                                  u8*          strIn[],
                                  size_t       size,
                                  u8*          out,
                                  ofs_t*       out_offsets,
                                  bool         noSuffixOpt,
                                  bool         avoidBranch) {

	u8* start_pointer = out;

	u8     buf[512], *cur = nullptr, *end = NULL, *lim = out + size;
	size_t string_idx, suffixLim = symbolTable.suffixLim;
	u8     byteLim = symbolTable.nSymbols + symbolTable.zeroTerminated - symbolTable.lenHisto[0];

	// three variants are possible. dead code falls away since the bool arguments are constants
	auto compress_variant = [&](bool no_suffix_opt, bool avoid_branch) {
		while (cur < end) {
			u64    word = fsst_unaligned_load(cur);
			size_t code = symbolTable.shortCodes[word & 0xFFFF];
			if (no_suffix_opt && ((u8)code) < suffixLim) {
				// 2 byte code without having to worry about longer matches
				*out++ = (u8)code;
				cur += 2;
			} else {
				size_t pos = word & 0xFFFFFF;
				size_t idx = FSST_HASH(pos) & (symbolTable.hashTabSize - 1);
				Symbol s   = symbolTable.hashTab[idx];
				out[1]     = (u8)word; // speculatively write out escaped byte
				word &= (0xFFFFFFFFFFFFFFFF >> (u8)s.icl);
				if ((s.icl < FSST_ICL_FREE) && s.val.num == word) {
					*out++ = (u8)s.code();
					cur += s.length();
				} else if (avoid_branch) {
					// could be a 2-byte or 1-byte code, or miss
					// handle everything with predication
					*out = (u8)code;
					out += 1 + ((code & FSST_CODE_BASE) >> 8);
					cur += (code >> FSST_LEN_BITS);
				} else if ((u8)code < byteLim) {
					// 2 byte code after checking there is no longer pattern
					*out++ = (u8)code;
					cur += 2;
				} else {
					// 1 byte code or miss.
					*out = (u8)code;
					out +=
					    1 + ((code & FSST_CODE_BASE) >> 8); // predicated - tested with a branch, that was always worse
					cur++;
				}
			}
		}
	};

	for (string_idx = 0; string_idx < n_strings; string_idx++) {
		size_t chunk, cur_off = 0;
		out_offsets[string_idx] = out - start_pointer;
		do {
			bool skip_copy = symbolTable.zeroTerminated;
			cur            = strIn[string_idx] + cur_off;
			chunk          = lenIn[string_idx] - cur_off;
			if (chunk > 511) {
				chunk = 511; // we need to compress in chunks of 511 in order to be byte-compatible with simd-compressed
				             // FSST
				skip_copy = false; // need to put terminator, so no in place mem usage possible
			}
			if ((2 * chunk + 7) > (size_t)(lim - out)) {
				return string_idx; // out of memory
			}
			if (!skip_copy) { // only in case of short zero-terminated strings, we can avoid copying
				memcpy(buf, cur, chunk);
				cur        = buf;
				buf[chunk] = (u8)symbolTable.terminator;
			}
			end = cur + chunk;
			// based on symboltable stats, choose a variant that is nice to the branch predictor
			if (noSuffixOpt) {
				compress_variant(true, false);
			} else if (avoidBranch) {
				compress_variant(false, true);
			} else {
				compress_variant(false, false);
			}
		} while ((cur_off += chunk) < lenIn[string_idx]);
	}
	out_offsets[string_idx] = (size_t)(out - start_pointer);

	return string_idx;
}

// runtime check for simd
inline size_t _compressImpl(Encoder* e,
                            size_t   nlines,
                            u32      lenIn[],
                            u8*      strIn[],
                            size_t   size,
                            u8*      output,
                            ofs_t*   out_offsets,
                            bool     noSuffixOpt,
                            bool     avoidBranch) {
	return compressBulk(*e->symbolTable, nlines, lenIn, strIn, size, output, out_offsets, noSuffixOpt, avoidBranch);
}

// adaptive choosing of scalar compression method based on symbol length histogram
inline size_t
_compressAuto(Encoder* e, size_t nstrings, u32 lenIn[], u8* strIn[], size_t size, u8* output, ofs_t* out_offsets) {
	bool avoidBranch = false, noSuffixOpt = false;
	if (100 * e->symbolTable->lenHisto[1] > 65 * e->symbolTable->nSymbols &&
	    100 * e->symbolTable->suffixLim > 95 * e->symbolTable->lenHisto[1]) {
		noSuffixOpt = true;
	} else if ((e->symbolTable->lenHisto[0] > 24 && e->symbolTable->lenHisto[0] < 92) &&
	           (e->symbolTable->lenHisto[0] < 43 || e->symbolTable->lenHisto[6] + e->symbolTable->lenHisto[7] < 29) &&
	           (e->symbolTable->lenHisto[0] < 72 || e->symbolTable->lenHisto[2] < 72)) {
		avoidBranch = true;
	}
	return _compressImpl(e, nstrings, lenIn, strIn, size, output, out_offsets, noSuffixOpt, avoidBranch);
}

size_t fsst_helper::fsst_compress(fsst_encoder_t* encoder,
                                  size_t          nstrings,
                                  uint32_t        len_in[],
                                  unsigned char*  str_in[],
                                  size_t          out_size,
                                  unsigned char*  output,
                                  ofs_t*          out_offsets) {
	return _compressAuto(reinterpret_cast<Encoder*>(encoder), nstrings, len_in, str_in, out_size, output, out_offsets);
}

} // namespace fastlanes