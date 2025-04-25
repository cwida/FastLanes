#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/eng/hzl_cmp_fac.hpp"
#include "fls/cor/eng/hzl_de_cmp_fac.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/logger/logger.hpp"
#include <algorithm>
#include <vector>

#pragma clang diagnostic ignored "-Wconversion"

namespace fastlanes {
DictHdrT DictHdrT::load(const uint8_t* p) {
	DictHdrT dict_hdr;
	std::memcpy(&dict_hdr, p, sizeof(dict_hdr));
	return dict_hdr;
}

Dic::Dic(AnalyzeState& stt)
    : data_buf {stt.data_buf}
    , offs_buf {stt.offs_buf}
    , compressed_data_buf {stt.compressed_data_buf}
    , compressed_offs_buf {stt.compressed_offs_buf} {
}

Dic::Dic(DecompressState& stt)
    : data_buf {stt.data_buf}
    , offs_buf {stt.offs_buf}
    , compressed_data_buf {stt.decompressed_data_buf}
    , compressed_offs_buf {stt.decompressed_offs_buf} {
}

Dic::~Dic() = default;

template <typename PT>
TDic<PT>::TDic(AnalyzeState& stt)
    : Dic {stt} {
	hzl_cmp_sp = HzlCmpFac<PT>::Create(stt, PageT::DICT_PAGE);
	hzl_cmp_sp->Reset();
};

template <typename PT>
TDic<PT>::TDic(DecompressState& stt)
    : Dic {stt} {
	hzl_de_cmp_sp = HzlDeCmpFac<PT>::Create(stt.exp_t, 0, PageT::DICT_PAGE);
};

template <typename PT>
n_t TDic<PT>::size() {
	auto ttl_sz {sizeof(DictHdrT)};
	ttl_sz += compressed_offs_buf.length();

	if constexpr (std::is_same<PT, i64_pt>() || std::is_same_v<PT, dbl_pt>) {
		FLS_ASSERT_ZERO(offs_buf.length())
		// always compress
		ttl_sz += compressed_data_buf.length();
	} else if constexpr (std::is_same<PT, std::string>()) {
		ttl_sz += compressed_data_buf.length();
		ttl_sz += FSST_MAXHEADER;
	} else {
		FLS_ABORT("NOT SUPPORTED")
	}

	return ttl_sz;
}

template <typename PT>
void TDic<PT>::Compress(CompressState& stt) {
	stt.c = static_cast<uint32_t>(map.size() + exc_map.size());

	if constexpr (std::is_same_v<PT, i64_pt>) {
		serialize();
		hzl_cmp_sp->FFOR(data_buf, compressed_data_buf, stt);
	} else if constexpr (std::is_same_v<PT, dbl_pt>) {
		serialize();
		hzl_cmp_sp->ALP(data_buf, compressed_data_buf, stt);
	} else if constexpr (std::is_same_v<PT, str_pt>) {
		serialize();
		hzl_cmp_sp->FSST(data_buf, offs_buf, compressed_data_buf, compressed_offs_buf, stt);

	} else {
		FLS_ABORT("NOT SUPPORTED")
	}
}

template <typename PT>
void TDic<PT>::Write(Buf& buf, CompressState& stt) {
	/* HDR*/
	DictHdrT dict_hdr = {ExpT::DICT, 0, 0, 0, static_cast<uint32_t>(map.size() + exc_map.size())};

	buf.UnsafeAppend(&dict_hdr, sizeof(dict_hdr));

	if constexpr (std::is_same_v<PT, i64_pt> || std::is_same_v<PT, dbl_pt>) {
		FLS_ASSERT_ZERO(offs_buf.length())
		buf.UnsafeAppend(compressed_data_buf.data(), compressed_data_buf.length());

	} else if constexpr (std::is_same_v<PT, str_pt>) {
		/* FSST */
		fsst_export(static_cast<fsst_encoder_t*>(stt.fsst_encoder), buf.end());
		buf.Advance(FSST_MAXHEADER);

		/* Offsets */
		buf.UnsafeAppend(compressed_offs_buf.data(), compressed_offs_buf.length());

		/* Data */
		buf.UnsafeAppend(compressed_data_buf.data(), compressed_data_buf.length());
	} else {
		FLS_ABORT("NOT SUPPORTED")
	}
}

template <typename PT>
void TDic<PT>::repetition_to_index() {
	// [fixme]
	FLS_PLOG_KEY_VALUE("fixme", "unordered_map has been used")
	idx_t idx = 0;
	for (auto& it : map) {
		auto& c = it.second;
		c       = idx;
		idx += 1;
	}

	for (auto& it : exc_map) {
		auto& c = it.second;
		c       = idx;
		idx += 1;
	}
}

template <typename PT>
void TDic<PT>::Decompress(const uint8_t* a_src_p, DecompressState& stt) {

	auto* src_p = const_cast<uint8_t*>(a_src_p);
	/* HDR*/
	DictHdrT dict_hdr;
	std::memcpy(&dict_hdr, src_p, sizeof(dict_hdr));
	src_p += sizeof(dict_hdr);

	FLS_ASSERT_NOT_ZERO(dict_hdr.entry_c)

	if constexpr (std::is_same_v<PT, i64_pt>) {
		hzl_de_cmp_sp->UNFFOR(const_cast<uint8_t*>(src_p), data_buf);
	}
	/**/
	else if constexpr (std::is_same_v<PT, str_pt>) {
		hzl_de_cmp_sp->UNFSST(const_cast<uint8_t*>(src_p), offs_buf, data_buf, dict_hdr.entry_c);
	}
	/**/
	else if constexpr (std::is_same_v<PT, dbl_pt>) {
		std::memcpy(data_buf.mutable_data(), src_p, dict_hdr.entry_c * sizeof(PT));
		//		hzl_de_cmp_sp->UNALP(const_cast<uint8_t*>(src_p), data_buf); TODO
	}
	/**/
	else {
		FLS_ABORT("NOT IMPLEMENTED")
		throw std::runtime_error("NOT IMPLEMENTED!");
	}
}

template <typename PT>
up<idx_vec_t> TDic<PT>::get_idx_vec(const ofs_t* offset_arr, const void* a_byte_arr) {
	auto idx_res_vec = std::make_unique<std::vector<idx_t>>();
	auto last_idx    = map.size() + exc_map.size();

	if constexpr (std::is_same_v<PT, i64_pt> || std::is_same_v<PT, dbl_pt>) {
		const auto* in_arr = reinterpret_cast<const PT*>(a_byte_arr);
		for (n_t i {0}; i < vec_n_tup(); ++i) {
			auto val = in_arr[i];
			auto it  = map.find(val);
			if (it == map.end()) {
				auto sec_it = exc_map.find(val);
				if (sec_it == exc_map.end()) {
					exc_map.emplace(val, last_idx);
					idx_res_vec->push_back(last_idx);
					last_idx++;
				} else {
					idx_res_vec->push_back(sec_it->second);
				}
			} else {
				idx_res_vec->push_back(it->second);
			}
		}
		return idx_res_vec;
	} else if constexpr (std::is_same<PT, str_pt>()) {
		auto byte_arr = reinterpret_cast<const uint8_t*>(a_byte_arr);

		idx_t exc_idx = map.size();
		for (ofs_t i {0}, start_off {0}, end_off {0}; i < vec_n_tup(); ++i, start_off = end_off) {
			end_off = offset_arr[i];
			std::string next_string(&byte_arr[start_off], &byte_arr[end_off]);
			auto        it = map.find(next_string);
			if (it == map.end()) {
				idx_res_vec->push_back(exc_idx);
				exc_idx++;
			} else {
				idx_res_vec->push_back(it->second);
			}
		}
		return idx_res_vec;
	} else {
		FLS_ABORT("NOT SUPPORTED!")
		return nullptr;
	}
}

template <typename PT>
bool sort_val_ascending(std::pair<PT, n_t>& a, std::pair<PT, n_t>& b) {
	return a.second < b.second;
}

template <typename PT>
void TDic<PT>::serialize() {
	FLS_ASSERT_FALSE(map.empty())

	if constexpr (std::is_same_v<PT, i64_pt> || std::is_same_v<PT, dbl_pt>) {
		auto* val_arr {reinterpret_cast<PT*>(data_buf.mutable_data())};

		// primary map
		for (auto& it : map) {
			auto& val    = it.first;
			auto& key    = it.second;
			val_arr[key] = val;
		}

		// secondary map
		for (auto& it : exc_map) {
			auto& val    = it.first;
			auto& key    = it.second;
			val_arr[key] = val;
		}
		n_t ttl_sz = (map.size() + exc_map.size()) * sizeof(PT);
		data_buf.Advance(ttl_sz);
	}
	/**/
	else if constexpr (std::is_same<PT, std::string>()) {
		/* INDEX1_OFF_ARR*/
		uint32_t cur_ofs {0UL};

		// [fixme] not optimal
		// sort by index
		std::vector<std::pair<std::string, n_t>> elems(map.begin(), map.end());
		std::sort(elems.begin(), elems.end(), sort_val_ascending<PT>);

		for (auto& it : elems) {
			auto& str = it.first;
			FLS_ASSERT_LE(cur_ofs, data_buf.Capacity()) // todo [buf]

			offs_buf.UnsafeAppend(&cur_ofs, sizeof(ofs_t));
			data_buf.UnsafeAppend(str.data(), str.size());

			cur_ofs += str.size();
		}

		offs_buf.UnsafeAppend(&cur_ofs, sizeof(ofs_t));

		// [fixme] add exc_map
	}
	/**/
	else {
		FLS_ABORT("NOT SUPPORTED!")
	}
}

template <typename PT>
TDic<PT>::~TDic() = default;

/*--------------------------------------------------------------------------------------------------------------------*\
+ Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(TDic)

} // namespace fastlanes
