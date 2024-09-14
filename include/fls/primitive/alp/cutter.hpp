#ifndef FLS_PRIMITIVE_ALP_CUTTER_HPP
#define FLS_PRIMITIVE_ALP_CUTTER_HPP

// NOLINTBEGIN

#include "mtd.hpp"
#include <algorithm>
#include <bitset>

namespace alp {

inline double tmp_dbl[1024];

inline size_t unique(const uint64_t* arr, int n) {
	std::set<uint64_t> counter;
	for (int i = 0; i < n; i++) {
		counter.insert(arr[i]);
	}
	return counter.size();
}

struct result {
	uint64_t uniqe_val;
	size_t   freq;
};

inline result most_frequent(uint64_t* arr) {
	// Insert all elements in hash.
	std::unordered_map<uint64_t, int> hash;
	for (int i = 0; i < VEC_C; i++) {
		hash[arr[i]]++;
	}

	// find the max frequency
	size_t   max_count = 0;
	uint64_t res       = -1;
	for (auto i : hash) {
		if (max_count < i.second) {
			res       = i.first;
			max_count = i.second;
		}
	}

	return {res, max_count};
}

/*
 *
 *
bw: 53 ,exc_c: 44
bw: 56 ,exc_c: 23
bw: 59 ,exc_c: 10
bw: 54 ,exc_c: 0
bw: 54 ,exc_c: 0
bw: 59 ,exc_c: 0
bw: 48 ,exc_c: 0
bw: 49 ,exc_c: 0
 *
 */

inline uint64_t extract_first_i_bits(uint64_t i, uint64_t value) {
	uint64_t mask;
	mask = (1ULL << i) - 1;
	mask = mask << (64ULL - i);
	return value & mask;
}

inline void cut(double* in_p, uint64_t* cutted, size_t i) {
	auto* in = reinterpret_cast<uint64_t*>(in_p);

	for (size_t k {0}; k < SMP_C; ++k) {
		cutted[k] = extract_first_i_bits(i, in[k]);
	}

	/* Print */
	//	debug::print_binary(cutted, SMP_C, std::cout);
}

inline metadata analyze_constant(uint64_t* in_p, size_t i) {
	metadata result;

	/* CNST SIZE */
	auto res     = most_frequent(in_p);
	result.unq_c = res.uniqe_val;
	result.freq  = res.freq;
	result.l_bw  = i;
	result.exc_c = VEC_C - result.freq;

	return result;
}
inline metadata analyze_dict(uint64_t* in_p, size_t i) {
	metadata result;

	auto unq_c   = unique(in_p, 1024);
	result.unq_c = unq_c;
	result.l_bw  = i;

	return result;
}

inline bool srt_asc(const std::pair<uint16_t, uint64_t>& a, const std::pair<uint16_t, uint64_t>& b) {
	return (a.first > b.first);
}

/* very hacky*/
inline metadata skew(const double* in_p, state& stt) {
	metadata                              result;
	std::unordered_map<uint64_t, int>     hash;
	std::vector<std::pair<int, uint64_t>> repetition_vec;

	auto* in = reinterpret_cast<const uint64_t*>(in_p);
	for (int j = 0; j < SMP_C; j++) {
		auto tmp = in[j] >> stt.r_bw;
		hash[tmp]++;
	}

	repetition_vec.reserve(hash.size());
	for (auto& pair : hash) {
		repetition_vec.emplace_back(pair.second, pair.first);
	}

	std::sort(repetition_vec.begin(), repetition_vec.end(), srt_asc);

	auto exp_c {0ULL};
	for (size_t i {CUTTER_DICT_SZ}; i < repetition_vec.size(); ++i) {
		exp_c += repetition_vec[i].first;
	}

	result.r_bw  = stt.r_bw;
	result.l_bw  = CUTTER_DICT_BW;
	result.exc_c = exp_c;

	return result;
}

inline void get_dict(const double* in_p, state& stt, metadata& best) {
	std::unordered_map<uint64_t, uint16_t> hash;

	auto* in = reinterpret_cast<const uint64_t*>(in_p);
	for (int j = 0; j < SMP_C; j++) {
		auto tmp = in[j] >> stt.r_bw;
		hash[tmp]++;
	}

	best.repetition_vec.reserve(hash.size());
	for (auto& pair : hash) {
		best.repetition_vec.emplace_back(pair.second, pair.first);
	}

	std::sort(best.repetition_vec.begin(), best.repetition_vec.end(), srt_asc);

	size_t covered_c = 0;
	size_t c {0};
	for (; c < CUTTER_DICT_SZ; ++c) {
		covered_c   = covered_c + best.repetition_vec[c].first;
		stt.dict[c] = best.repetition_vec[c].second;
		stt.dict_map.insert({stt.dict[c], c});
	}

	for (size_t i {c + 1}; i < best.repetition_vec.size(); ++i) {
		stt.dict_map.insert({best.repetition_vec[i].second, i});
	}

	stt.dict_c = c;
	stt.l_bw   = CUTTER_DICT_BW;
}

/*dbl_arr, exc_arr, pos_arr, exc_c_arr, first_arr, second_arr, stt*/
inline void cutter(const double* dbl_arr,
                   double*       exc_arr,
                   uint16_t*     pos_arr,
                   uint16_t*     exc_c_arr,
                   uint64_t*     first_arr,
                   uint16_t*     second_arr,
                   alp::state&   stt) {
	const auto* in = reinterpret_cast<const uint64_t*>(dbl_arr);

	// cut
	for (size_t i {0}; i < VEC_C; ++i) {
		auto tmp      = in[i];
		first_arr[i]  = tmp & ((1ULL << stt.r_bw) - 1);
		second_arr[i] = (tmp >> stt.r_bw);
	}

	uint16_t exc_c {0};

	for (size_t i {0}; i < VEC_C; ++i) {
		uint16_t idx;
		auto     key = second_arr[i];
		if (stt.dict_map.find(key) == stt.dict_map.end()) {
			//
			idx = stt.dict_c;
		} else {
			idx = stt.dict_map[key];
		}
		second_arr[i] = idx;

		if (idx >= stt.dict_c) {
			exc_arr[exc_c] = dbl_arr[i];
			pos_arr[exc_c] = i;
			exc_c++;
		}
	}
	stt.exp_c    = exc_c;
	exc_c_arr[0] = exc_c;
}

/* glue_arr, unffor_first_arr, unffor_second_arr, stt.fac, stt.exp */
inline void glue(double* a_out, uint64_t* unffor_first_arr, uint16_t* unffor_second_arr, state& stt) {

	auto* out = reinterpret_cast<uint64_t*>(a_out);
	auto* r_p = unffor_first_arr;
	auto* l_p = unffor_second_arr;

	for (size_t i {0}; i < VEC_C; ++i) {
		uint16_t l = stt.dict[l_p[i]];
		uint64_t r = r_p[i];
		out[i]     = (static_cast<uint64_t>(l) << stt.r_bw) | r;
	}
}

} // namespace alp
#endif // FLS_PRIMITIVE_ALP_CUTTER_HPP

// NOLINTEND
