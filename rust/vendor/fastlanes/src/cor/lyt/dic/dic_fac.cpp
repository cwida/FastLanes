#include "fls/cor/lyt/dic/dic_fac.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/utl/random.hpp"
#include "fls/utl/util.hpp"
#include <algorithm>
#include <set>

#pragma clang diagnostic ignored "-Wconversion"

namespace fastlanes {
enum class DictSortStrategy : uint8_t { // nolint
	SORT_BY_INSERTION_ORDER = 0,
	SORT_BY_FREQUENCY       = 1,
	SORT_BY_VALUE           = 2,
};

constexpr DictSortStrategy get_strategy(ExpT exp_t) {
	switch (exp_t) {
	case ExpT::INVALID:
	case ExpT::UNDECIDED:
	case ExpT::UNCOMPRESSED:
	case ExpT::BYTE_ARR:
	case ExpT::FFOR:
	case ExpT::DELTA:
	case ExpT::RLE:
	case ExpT::FSST:
	case ExpT::DICT:
		return DictSortStrategy::SORT_BY_INSERTION_ORDER;
	case ExpT::DICT_RLE:
		return DictSortStrategy::SORT_BY_INSERTION_ORDER;
	case ExpT::DICT_FRQ:
		return DictSortStrategy::SORT_BY_FREQUENCY;
	case ExpT::DICT_VAL:
		return DictSortStrategy::SORT_BY_VALUE;
		// TODO [FIXME]
	default:
		return DictSortStrategy::SORT_BY_INSERTION_ORDER;
	}
}

/* Flip a map*/
template <typename T>
static std::multimap<idx_t, T> invert(std::unordered_map<T, idx_t>& map) {
	if constexpr (std::is_same<T, int64_t>()) {
		std::multimap<idx_t, T> multi_map;

		std::unordered_map<int64_t, idx_t>::iterator it;
		for (it = map.begin(); it != map.end(); it++) {
			multi_map.insert(std::make_pair(it->second, it->first));
		}

		return multi_map;
	} else if constexpr (std::is_same<T, std::string>()) {
		std::multimap<idx_t, std::string> multi_map;

		std::unordered_map<std::string, idx_t>::iterator it;
		for (it = map.begin(); it != map.end(); it++) {
			multi_map.insert(std::make_pair(it->second, it->first));
		}

		return multi_map;
	}
}

template <typename PT>
up<TDic<PT>> dict_fac<PT>::adaptive_create(const PT* data_p, n_t n, AnalyzeState& stt) {
	FLS_ASSERT_CORRECT_N(n)

	const n_t vec_c {n / CFG::VEC_TUP_C};
	n_t       analyzed_vec_c {0};
	if (vec_c == 0) {
		return nullptr;
	}; /* No dict for tuple-c < 1024 */

	/* Init. */
	//[fixme] move to stt
	vector<bool> is_processed;
	is_processed.reserve(vec_c);

	n_t result {0};

	/* base. */
	auto base_dict = dict_fac::m_create_from(data_p, 0, stt);
	analyzed_vec_c++;
	if (vec_c == 1) {
		base_dict->repetition_to_index();
		return base_dict;
	}

	/* next. */
	auto next_dict = dict_fac::m_create_random(data_p, vec_c, is_processed, stt);
	analyzed_vec_c++;

	result = dict_fac::m_compare(base_dict->map, next_dict->map);
	dict_fac::m_combine(base_dict->map, next_dict->map);

	/* Adaptive analyzing*/
	while (result < CFG::DIC::THRESHOLD) {
		FLS_ASSERT_LE(analyzed_vec_c, vec_c)

		if (analyzed_vec_c == vec_c) {
			break;
		}
		next_dict = dict_fac::m_create_random(data_p, vec_c, is_processed, stt);

		/* Check the dic_page limit. */
		if (base_dict->size() + next_dict->size() > CFG::DIC::DIC_PAGE_SZ) {
			break;
		}

		result = dict_fac::m_compare(base_dict->map, next_dict->map);
		dict_fac::m_combine(base_dict->map, next_dict->map);
	}

	base_dict->repetition_to_index();
	return base_dict;
}

template <typename PT>
up<TDic<PT>>
dict_fac<PT>::m_create_random(const PT* data_p, n_t possible_sample_c, vector<bool>& is_processed, AnalyzeState& stt) {
	auto next_batch_num = random::next_vec_num(possible_sample_c, is_processed);
	return m_create_from(data_p, next_batch_num, stt);
}

template <typename PT>
n_t dict_fac<PT>::m_compare(dic_t<PT>& r, dic_t<PT>& l) {
	if constexpr (std::is_same<PT, int64_t>()) {
		n_t total {0};

		std::unordered_map<int64_t, idx_t>::iterator r_it;

		/* How many tuples are covered by r dic?*/
		for (r_it = r.begin(); r_it != r.end(); r_it++) {
			auto l_it = l.find(r_it->first);

			if (l_it != l.end()) {
				total += l_it->second;
			}
		}

		return total;
	} else if constexpr (std::is_same<PT, std::string>()) {
		n_t total {0};

		std::unordered_map<std::string, idx_t>::iterator r_it;

		/* How many tuples are covered by r dic?*/
		for (r_it = r.begin(); r_it != r.end(); r_it++) {
			auto l_it = l.find(r_it->first);

			if (l_it != l.end()) {
				total += l_it->second;
			}
		}

		return total;
	} else {
		FLS_ABORT("NOT SUPPORTED!")
		return 0;
	}
}

template <typename PT>
up<TDic<PT>> dict_fac<PT>::m_create_from(const PT* data_p, n_t sample_num, AnalyzeState& stt) {
	if constexpr (std::is_same<PT, i64_pt>()) {
		auto dic = std::make_unique<TDic<i64_pt>>(stt);

		/* Create Dic */
		for (size_t i = 0; i < CFG::VEC_TUP_C; ++i) {
			auto next_val = data_p[i];
			if (dic->map.find(next_val) == dic->map.end()) {
				dic->map.emplace(next_val, 1);
			} else {
				dic->map[next_val]++;
			}
		}

		/* Prune the 10 percent undesired part. */
		std::multimap<idx_t, PT> flipped_map = invert(dic->map);
		n_t                      sum {0};

		auto it = flipped_map.end();
		it--;
		for (; it != flipped_map.begin();) {
			sum += it->first;
			--it;
			if (sum >= CFG::DIC::THRESHOLD) {
				/* Remove elements from now on. */
				dic->map.erase(dic->map.find(it->second));
			}
		}

		return dic;

	} else if constexpr (std::is_same<PT, std::string>()) {
		auto dic_up = std::make_unique<TDic<PT>>(stt);

		/* Create Dic */
		for (size_t i = 0; i < CFG::VEC_TUP_C; ++i) {
			auto next_val = data_p[i];
			if (dic_up->map.find(next_val) == dic_up->map.end()) {
				dic_up->map.emplace(next_val, 1);
			} else {
				dic_up->map[next_val]++;
			}
		}

		/* Prune the 10 percent undesired part. */
		std::multimap<idx_t, PT> flipped_map = invert(dic_up->map);
		n_t                      visited {0};

		for (auto it = flipped_map.end(); it != flipped_map.begin(); --it) {
			visited += it->first;
			if (visited >= CFG::DIC::THRESHOLD) {
				/* Remove element from now on. */
				dic_up->map.erase(dic_up->map.find(it->second));
			}
		}

		return dic_up;
	} else {
		FLS_ABORT("NOT SUPPORTED!")
		return nullptr;
	}
}

template <typename PT>
void dict_fac<PT>::m_combine(dic_t<PT>& left, dic_t<PT>& right) {
	if constexpr (std::is_same<PT, int64_t>()) {
		for (auto& r_it : right) {
			auto l_it = left.find(r_it.first);
			if (l_it != left.end()) {
				left.emplace(r_it.first, r_it.second);
			} else {
				left[r_it.first] += r_it.second;
			}
		}
	}

	else {
		FLS_ABORT("NOT SUPPORTED!")
	}
}

template <typename T>
bool sort_val_ascending(std::pair<T, n_t>& a, std::pair<T, n_t>& b) {
	return a.second < b.second;
}

template <typename T>
bool sort_val_descending(std::pair<T, n_t>& a, std::pair<T, n_t>& b) {
	return a.second > b.second;
}

template <typename T>
bool sort_key_ascending(std::pair<T, n_t>& a, std::pair<T, n_t>& b) {
	return a.first < b.first;
}

template <typename T>
bool sort_key_descending(std::pair<T, n_t>& a, std::pair<T, n_t>& b) {
	return a.first > b.first;
}

template <typename PT>
up<TDic<PT>> dict_fac<PT>::perfect_create(const PT* data_p, n_t n, AnalyzeState& stt) {
	if constexpr (std::is_same_v<PT, i64_pt> || std::is_same_v<PT, dbl_pt>) {
		auto                            dic_up = std::make_unique<TDic<PT>>(stt);
		std::vector<std::pair<PT, n_t>> elems;
		auto                            strategy = get_strategy(stt.m_exp_t);

		switch (strategy) {
		case DictSortStrategy::SORT_BY_INSERTION_ORDER: {
			/* Create Dic */
			auto idx = 0;
			for (size_t i = 0; i < n; ++i) {
				auto next_val = data_p[i];
				if (dic_up->map.find(next_val) == dic_up->map.end()) {
					dic_up->map.emplace(next_val, idx++);
				}
			};

			// pair of value - idx
			elems = {dic_up->map.begin(), dic_up->map.end()};

			// sort based on frequency!
			std::sort(elems.begin(), elems.end(), sort_val_ascending<PT>);
		} break;
		case DictSortStrategy::SORT_BY_FREQUENCY: {
			/* Create Dic */
			for (size_t i = 0; i < n; ++i) {
				auto next_val = data_p[i];
				if (dic_up->map.find(next_val) == dic_up->map.end()) {
					dic_up->map.emplace(next_val, 1);
				} else {
					dic_up->map[next_val]++;
				}
			};

			// pair of value - frequency
			elems = {dic_up->map.begin(), dic_up->map.end()};

			// sort based on frequency!
			std::sort(elems.begin(), elems.end(), sort_val_descending<PT>);

		} break;
		case DictSortStrategy::SORT_BY_VALUE: {
			/* Create Dic */
			for (size_t i = 0; i < n; ++i) {
				auto next_val = data_p[i];
				if (dic_up->map.find(next_val) == dic_up->map.end()) {
					dic_up->map.emplace(next_val, 1);
				} else {
					dic_up->map[next_val]++;
				}
			};

			// pair of value - frequency
			elems = {dic_up->map.begin(), dic_up->map.end()};

			// sort based on frequency!
			std::sort(elems.begin(), elems.end(), sort_key_ascending<PT>);
		}
		}

		dic_up->map.clear();

		n_t idx {0};
		for (auto& pair : elems) {
			dic_up->map.emplace(pair.first, idx);
			idx++;
		}

		return dic_up;
	} else if constexpr (std::is_same<PT, std::string>()) {
		auto                            dic_up   = std::make_unique<TDic<PT>>(stt);
		auto                            strategy = get_strategy(stt.m_exp_t);
		std::vector<std::pair<PT, n_t>> elems;

		switch (strategy) {
		case DictSortStrategy::SORT_BY_INSERTION_ORDER: {
			/* Create Dic */
			auto idx = 0;
			for (size_t i = 0; i < n; ++i) {
				auto next_val = data_p[i];
				if (dic_up->map.find(next_val) == dic_up->map.end()) {
					dic_up->map.emplace(next_val, idx++);
				}
			};

			elems = {dic_up->map.begin(), dic_up->map.end()};
			std::sort(elems.begin(), elems.end(), sort_val_descending<PT>);
		} break;
		case DictSortStrategy::SORT_BY_FREQUENCY: {
			/* Create Dic */
			for (size_t i = 0; i < n; ++i) {
				auto next_val = data_p[i];
				if (dic_up->map.find(next_val) == dic_up->map.end()) {
					dic_up->map.emplace(next_val, 1);
				} else {
					dic_up->map[next_val]++;
				}
			}

			elems = {dic_up->map.begin(), dic_up->map.end()};
			std::sort(elems.begin(), elems.end(), sort_val_descending<PT>);

		} break;
		case DictSortStrategy::SORT_BY_VALUE: {
			/* Create Dic */
			for (size_t i = 0; i < n; ++i) {
				auto next_val = data_p[i];
				if (dic_up->map.find(next_val) == dic_up->map.end()) {
					dic_up->map.emplace(next_val, 1);
				} else {
					dic_up->map[next_val]++;
				}
			};

			elems = {dic_up->map.begin(), dic_up->map.end()};

			std::sort(elems.begin(), elems.end(), sort_key_ascending<PT>);
		}
		}

		dic_up->map.clear();

		n_t idx {0};
		for (auto& pair : elems) {
			dic_up->map.emplace(pair.first, idx);
			idx++;
		}

		return dic_up;
	} else {
		FLS_ABORT("NOT SUPPORTED!")
		return nullptr;
	}
}

template <typename PT>
bsz_t dict_fac<PT>::multi_dic_create(const std::vector<PT>&     src_col,
                                     AnalyzeState&              src_stt,
                                     const std::vector<str_pt>& tgt_col,
                                     AnalyzeState&              tgt_stt) {
	bsz_t ttl_sz {0};

	if constexpr (std::is_same_v<PT, str_pt>) {
		auto src_dic = *dynamic_cast<TDic<PT>*>(src_stt.dic_up.get());
		auto tgt_dic = *dynamic_cast<TDic<str_pt>*>(tgt_stt.dic_up.get());

		FLS_ABORT("HERE")

	} else if constexpr (std::is_same_v<PT, i64_pt>) {
	} else {
	}

	return ttl_sz;
}

template <typename PT>
bsz_t dict_fac<PT>::multi_dic_create(const std::vector<PT>&     src_col,
                                     AnalyzeState&              src_stt,
                                     const std::vector<i64_pt>& tgt_col,
                                     AnalyzeState&              tgt_stt) {
	bsz_t ttl_sz {0};

	FLS_ABORT("HERE")
	if constexpr (std::is_same_v<PT, str_pt>) {

	} else if constexpr (std::is_same_v<PT, i64_pt>) {
	} else {
	}

	return ttl_sz;
}

template <typename PT>
bsz_t dict_fac<PT>::exp_multi_dic_create(const std::vector<PT>& src_col, const std::vector<str_pt>& tgt_col) {
	FLS_ASSERT_EQUALITY(src_col.size(), tgt_col.size())

	bsz_t ttl_size {0};

	std::unordered_map<PT, std::set<str_pt>> new_dic;

	for (n_t idx {0}; idx < src_col.size(); ++idx) {
		const auto& src_val = src_col[idx];
		const auto& tgt_val = tgt_col[idx];

		if (new_dic.find(src_val) == new_dic.end()) {
			new_dic.insert({src_val, {}});
		} else {
			new_dic[src_val].insert(tgt_val);
		}
	}

	sz_t max_sz {0};

	for (const auto& map : new_dic) {
		auto map_size = map.second.size();
		if (max_sz < map.second.size()) {
			max_sz = map_size;
		}

		for (const auto& val : map.second) {
			ttl_size += val.size() + sizeof(ofs_t);
		}
	}

	auto bits_per_value = RANGE_BIT<uint64_t>(max_sz);
	auto ttl_bytes      = src_col.size() * bits_per_value / 8;
	return ttl_size + ttl_bytes;
}

template <typename PT>
bsz_t dict_fac<PT>::exp_multi_dic_create(const std::vector<PT>& src_col) {

	bsz_t ttl_size {0};

	std::set<PT> dic;

	if constexpr (!std::is_same_v<PT, bol_pt>) {
		for (n_t idx {0}; idx < src_col.size(); ++idx) {
			const auto& src_val = src_col[idx];
			if (dic.find(src_val) == dic.end()) {
				dic.insert(src_val);
			}
		}
	} else {
		FLS_ABORT("NOT IMPLEMENTED TYPE")
	}

	if constexpr (std::is_same_v<PT, i64_pt>) {
		ttl_size += dic.size() * (sizeof(PT) + sizeof(ofs_t));
	} else if constexpr (std::is_same_v<PT, str_pt>) {
		for (const auto& val : dic) {
			ttl_size += val.size() + sizeof(ofs_t);
		}
	} else {
		FLS_ABORT("NOT IMPLEMENTED TYPE")
	}

	return ttl_size;
}

template <typename PT>
bsz_t dict_fac<PT>::exp_multi_dic_create(const std::vector<PT>& src_col, const std::vector<i64_pt>& tgt_col) {
	FLS_ASSERT_EQUALITY(src_col.size(), tgt_col.size())

	bsz_t ttl_size {0};

	std::unordered_map<PT, std::set<i64_pt>> new_dic;

	for (n_t idx {0}; idx < src_col.size(); ++idx) {
		const auto& src_val = src_col[idx];
		const auto& tgt_val = tgt_col[idx];

		if (new_dic.find(src_val) == new_dic.end()) {
			new_dic.insert({src_val, {}});
		} else {
			new_dic[src_val].insert(tgt_val);
		}
	}

	sz_t max_sz {0};
	for (const auto& map : new_dic) {
		auto map_size = map.second.size();
		if (max_sz < map.second.size()) {
			max_sz = map_size;
		}

		ttl_size += map.second.size() * (sizeof(PT) + sizeof(ofs_t));
	}

	auto bits_per_value = RANGE_BIT<uint64_t>(max_sz);
	auto ttl_bytes      = (src_col.size() * bits_per_value / 8);
	return ttl_size + ttl_bytes;
}

template <typename PT>
bsz_t dict_fac<PT>::exp_multi_dic_create(const std::vector<PT>& src_col, const std::vector<dbl_pt>& tgt_col) {
	FLS_ASSERT_EQUALITY(src_col.size(), tgt_col.size())

	bsz_t ttl_size {0};

	std::unordered_map<PT, std::set<dbl_pt>> new_dic;

	for (n_t idx {0}; idx < src_col.size(); ++idx) {
		const auto& src_val = src_col[idx];
		const auto& tgt_val = tgt_col[idx];

		if (new_dic.find(src_val) == new_dic.end()) {
			new_dic.insert({src_val, {}});
		} else {
			new_dic[src_val].insert(tgt_val);
		}
	}

	sz_t max_sz {0};
	for (const auto& map : new_dic) {
		auto map_size = map.second.size();
		if (max_sz < map.second.size()) {
			max_sz = map_size;
		}

		ttl_size += map.second.size() * (sizeof(PT) + sizeof(ofs_t));
	}

	auto bits_per_value = RANGE_BIT<uint64_t>(max_sz);
	auto ttl_bytes      = (src_col.size() * bits_per_value / 8);
	return ttl_size + ttl_bytes;
}

/*--------------------------------------------------------------------------------------------------------------------*\
+ Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(dict_fac)
} // namespace fastlanes