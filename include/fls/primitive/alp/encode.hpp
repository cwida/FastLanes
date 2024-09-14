#ifndef FLS_PRIMITIVE_ALP_ENCODE_HPP
#define FLS_PRIMITIVE_ALP_ENCODE_HPP

// NOLINTBEGIN
#pragma clang diagnostic ignored "-Wconversion"

// clang-format off
#pragma once

#include "fls/primitive/alp/config.hpp"
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdint>
#include <list>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#ifdef __AVX2__

#include <immintrin.h>

#endif

/*
 * use magic_number .
 * in case of exception -> the prev digits.
 * rounding idea
 * new idea
 * */

namespace alp {

struct state {
	/* ALP */
	SCHEME scheme;

	/* PDE */
	uint16_t                         rg_n_comb {5};
	std::vector<std::pair<int, int>> cmb_arr;
	uint8_t                          exp;
	uint8_t                          fac;

	/* CUTTER */
	uint8_t                                r_bw;
	uint8_t                                l_bw;
	uint64_t                               r_base;
	uint16_t                               l_base;
	uint16_t*                              dict;
	size_t                                 dict_c;
	std::unordered_map<uint16_t, uint16_t> dict_map;

	/* Patch*/
	uint16_t exp_c;
};

/*
 * scalar version of double_to_int64
 */
inline int64_t double_to_int64(double x) {
	double magic_number = static_cast<double>(0x001800000000000);
	x                   = x + magic_number;
	return static_cast<int64_t>(x) - static_cast<int64_t>(magic_number);
}

inline static double frac_arr[] = {
    1.0,
    0.1,
    0.01,
    0.001,
    0.0001,
    0.00001,
    0.000001,
    0.0000001,
    0.00000001,
    0.000000001,
    0.0000000001,
    0.00000000001,
    0.000000000001,
    0.0000000000001,
    0.00000000000001,
    0.000000000000001,
    0.0000000000000001,
    0.00000000000000001,
    0.000000000000000001,
    0.0000000000000000001,
    0.00000000000000000001,
};

inline const int64_t fact_arr[] = {1,
                                   10,
                                   100,
                                   1000,
                                   10000,
                                   100000,
                                   1000000,
                                   10000000,
                                   100000000,
                                   1000000000,
                                   10000000000,
                                   100000000000,
                                   1000000000000,
                                   10000000000000,
                                   100000000000000,
                                   1000000000000000,
                                   10000000000000000,
                                   100000000000000000,
                                   1000000000000000000};

inline const int64_t u_fact_arr[] = {1,
                                     10,
                                     100,
                                     1000,
                                     10000,
                                     100000,
                                     1000000,
                                     10000000,
                                     100000000,
                                     1000000000,
                                     10000000000,
                                     100000000000,
                                     1000000000000,
                                     10000000000000,
                                     100000000000000,
                                     1000000000000000,
                                     10000000000000000,
                                     100000000000000000,
                                     1000000000000000000};

inline const double exp_arr[] = {
    1.0,
    10.0,
    100.0,
    1000.0,
    10000.0,
    100000.0,
    1000000.0,
    10000000.0,
    100000000.0,
    1000000000.0,
    10000000000.0,
    100000000000.0,
    1000000000000.0,
    10000000000000.0,
    100000000000000.0,
    1000000000000000.0,
    10000000000000000.0,
    100000000000000000.0,
    1000000000000000000.0,
    10000000000000000000.0,
    100000000000000000000.0,
    1000000000000000000000.0,
    10000000000000000000000.0,
    100000000000000000000000.0,
};

inline void patch(double* out, const double* exp_p, const uint16_t* pos_p, const uint16_t* exp_c_p) {
	auto exp_c = exp_c_p[0];

	for (uint16_t i {0}; i < exp_c; ++i) {
		out[pos_p[i]] = exp_p[i];
	}
}

inline void analyze_ffor(int64_t* in_p, uint8_t* bw_p, int64_t* base_p) {

	auto min = std::numeric_limits<int64_t>::max();
	auto max = std::numeric_limits<int64_t>::min();

	for (size_t i {0}; i < 1024; ++i) {
		if (in_p[i] < min) { min = in_p[i]; }
		if (in_p[i] > max) { max = in_p[i]; }
	}

	uint64_t delta          = (static_cast<uint64_t>(max) - static_cast<uint64_t>(min));
	auto     bits_per_digit = ceil(log2(delta + 1));
	bw_p[0]                 = bits_per_digit;
	base_p[0]               = min;
}

inline double*   tmp_dbl_arr = new (std::align_val_t {64}) double[1024];
inline uint64_t* index_arr   = new (std::align_val_t {64}) uint64_t[1024] {
    0,    1,    2,    3,    4,    5,    6,    7,    8,    9,    10,   11,   12,   13,   14,   15,   16,   17,   18,
    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
    38,   39,   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,   91,   92,   93,   94,
    95,   96,   97,   98,   99,   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,  110,  111,  112,  113,
    114,  115,  116,  117,  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,  128,  129,  130,  131,  132,
    133,  134,  135,  136,  137,  138,  139,  140,  141,  142,  143,  144,  145,  146,  147,  148,  149,  150,  151,
    152,  153,  154,  155,  156,  157,  158,  159,  160,  161,  162,  163,  164,  165,  166,  167,  168,  169,  170,
    171,  172,  173,  174,  175,  176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  186,  187,  188,  189,
    190,  191,  192,  193,  194,  195,  196,  197,  198,  199,  200,  201,  202,  203,  204,  205,  206,  207,  208,
    209,  210,  211,  212,  213,  214,  215,  216,  217,  218,  219,  220,  221,  222,  223,  224,  225,  226,  227,
    228,  229,  230,  231,  232,  233,  234,  235,  236,  237,  238,  239,  240,  241,  242,  243,  244,  245,  246,
    247,  248,  249,  250,  251,  252,  253,  254,  255,  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,
    266,  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
    285,  286,  287,  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,
    304,  305,  306,  307,  308,  309,  310,  311,  312,  313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
    323,  324,  325,  326,  327,  328,  329,  330,  331,  332,  333,  334,  335,  336,  337,  338,  339,  340,  341,
    342,  343,  344,  345,  346,  347,  348,  349,  350,  351,  352,  353,  354,  355,  356,  357,  358,  359,  360,
    361,  362,  363,  364,  365,  366,  367,  368,  369,  370,  371,  372,  373,  374,  375,  376,  377,  378,  379,
    380,  381,  382,  383,  384,  385,  386,  387,  388,  389,  390,  391,  392,  393,  394,  395,  396,  397,  398,
    399,  400,  401,  402,  403,  404,  405,  406,  407,  408,  409,  410,  411,  412,  413,  414,  415,  416,  417,
    418,  419,  420,  421,  422,  423,  424,  425,  426,  427,  428,  429,  430,  431,  432,  433,  434,  435,  436,
    437,  438,  439,  440,  441,  442,  443,  444,  445,  446,  447,  448,  449,  450,  451,  452,  453,  454,  455,
    456,  457,  458,  459,  460,  461,  462,  463,  464,  465,  466,  467,  468,  469,  470,  471,  472,  473,  474,
    475,  476,  477,  478,  479,  480,  481,  482,  483,  484,  485,  486,  487,  488,  489,  490,  491,  492,  493,
    494,  495,  496,  497,  498,  499,  500,  501,  502,  503,  504,  505,  506,  507,  508,  509,  510,  511,  512,
    513,  514,  515,  516,  517,  518,  519,  520,  521,  522,  523,  524,  525,  526,  527,  528,  529,  530,  531,
    532,  533,  534,  535,  536,  537,  538,  539,  540,  541,  542,  543,  544,  545,  546,  547,  548,  549,  550,
    551,  552,  553,  554,  555,  556,  557,  558,  559,  560,  561,  562,  563,  564,  565,  566,  567,  568,  569,
    570,  571,  572,  573,  574,  575,  576,  577,  578,  579,  580,  581,  582,  583,  584,  585,  586,  587,  588,
    589,  590,  591,  592,  593,  594,  595,  596,  597,  598,  599,  600,  601,  602,  603,  604,  605,  606,  607,
    608,  609,  610,  611,  612,  613,  614,  615,  616,  617,  618,  619,  620,  621,  622,  623,  624,  625,  626,
    627,  628,  629,  630,  631,  632,  633,  634,  635,  636,  637,  638,  639,  640,  641,  642,  643,  644,  645,
    646,  647,  648,  649,  650,  651,  652,  653,  654,  655,  656,  657,  658,  659,  660,  661,  662,  663,  664,
    665,  666,  667,  668,  669,  670,  671,  672,  673,  674,  675,  676,  677,  678,  679,  680,  681,  682,  683,
    684,  685,  686,  687,  688,  689,  690,  691,  692,  693,  694,  695,  696,  697,  698,  699,  700,  701,  702,
    703,  704,  705,  706,  707,  708,  709,  710,  711,  712,  713,  714,  715,  716,  717,  718,  719,  720,  721,
    722,  723,  724,  725,  726,  727,  728,  729,  730,  731,  732,  733,  734,  735,  736,  737,  738,  739,  740,
    741,  742,  743,  744,  745,  746,  747,  748,  749,  750,  751,  752,  753,  754,  755,  756,  757,  758,  759,
    760,  761,  762,  763,  764,  765,  766,  767,  768,  769,  770,  771,  772,  773,  774,  775,  776,  777,  778,
    779,  780,  781,  782,  783,  784,  785,  786,  787,  788,  789,  790,  791,  792,  793,  794,  795,  796,  797,
    798,  799,  800,  801,  802,  803,  804,  805,  806,  807,  808,  809,  810,  811,  812,  813,  814,  815,  816,
    817,  818,  819,  820,  821,  822,  823,  824,  825,  826,  827,  828,  829,  830,  831,  832,  833,  834,  835,
    836,  837,  838,  839,  840,  841,  842,  843,  844,  845,  846,  847,  848,  849,  850,  851,  852,  853,  854,
    855,  856,  857,  858,  859,  860,  861,  862,  863,  864,  865,  866,  867,  868,  869,  870,  871,  872,  873,
    874,  875,  876,  877,  878,  879,  880,  881,  882,  883,  884,  885,  886,  887,  888,  889,  890,  891,  892,
    893,  894,  895,  896,  897,  898,  899,  900,  901,  902,  903,  904,  905,  906,  907,  908,  909,  910,  911,
    912,  913,  914,  915,  916,  917,  918,  919,  920,  921,  922,  923,  924,  925,  926,  927,  928,  929,  930,
    931,  932,  933,  934,  935,  936,  937,  938,  939,  940,  941,  942,  943,  944,  945,  946,  947,  948,  949,
    950,  951,  952,  953,  954,  955,  956,  957,  958,  959,  960,  961,  962,  963,  964,  965,  966,  967,  968,
    969,  970,  971,  972,  973,  974,  975,  976,  977,  978,  979,  980,  981,  982,  983,  984,  985,  986,  987,
    988,  989,  990,  991,  992,  993,  994,  995,  996,  997,  998,  999,  1000, 1001, 1002, 1003, 1004, 1005, 1006,
    1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023,
};

inline uint8_t* lookup_table = new (std::align_val_t {64}) uint8_t[256] {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2,
    3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
    3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
    6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
    3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4,
    5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
    6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

inline uint64_t* tmp_index = new (std::align_val_t {64}) uint64_t[1024];

inline double magic_number = static_cast<double>(0x001800000000000);

inline uint32_t smp_size = 32;

inline void find_best_exponent_factor_from_combination(std::vector<std::pair<int, int>>& top_combinations,
                                                       uint8_t                           top_n,
                                                       const double*                     smp_arr,
                                                       uint8_t&                          factor,
                                                       uint8_t&                          exponent) {
	uint8_t  found_exponent {0};
	uint8_t  found_factor {0};
	uint64_t previous_bit_count {0};
	uint8_t  worse_threshold {0};

	// For each top combination
	for (size_t k {0}; k < top_n; k++) {
		int      exp_ref    = top_combinations[k].first;
		int      factor_idx = top_combinations[k].second;
		uint32_t exception_c {0};
		uint32_t bits_per_digit {0};
		uint64_t local_total_bits {0};
		int64_t  local_max_digits {std::numeric_limits<int64_t>().min()};
		int64_t  local_min_digits {std::numeric_limits<int64_t>().max()};

		auto j {0};
		// Test combination of exponent and factor for the sample
		for (size_t i = 0; i < smp_size; ++i) {
			int64_t digits;
			double  dbl = smp_arr[j];
			j           = j + 32;

			double orig;
			double cd;

			cd     = dbl * alp::exp_arr[exp_ref] * alp::frac_arr[factor_idx];
			digits = alp::double_to_int64(cd);
			orig   = digits * alp::fact_arr[factor_idx] * alp::frac_arr[exp_ref];
			if (orig == dbl) {
				if (digits > local_max_digits) { local_max_digits = digits; }
				if (digits < local_min_digits) { local_min_digits = digits; }
			} else {
				exception_c++;
			}
		}

		// Evaluate factor/exponent performance (we optimize for FOR)
		uint64_t delta = local_max_digits - local_min_digits;
		bits_per_digit = ceil(log2(delta + 1));
		local_total_bits += smp_size * bits_per_digit;
		local_total_bits += exception_c * (64 + 16);

		if (k == 0) { // First try with first combination
			previous_bit_count = local_total_bits;
			found_factor       = factor_idx;
			found_exponent     = exp_ref;
			continue; // Go to second
		}
		if (local_total_bits >= previous_bit_count) { // If current is worse or equal than previous
			worse_threshold += 1;
			if (worse_threshold == 2) {
				break; // We stop only if two are worse
			}
			continue;
		}
		// Otherwise we replace best and continue with next
		previous_bit_count = local_total_bits;
		found_factor       = factor_idx;
		found_exponent     = exp_ref;
		worse_threshold    = 0;
	}
	exponent = found_exponent;
	factor   = found_factor;
}

inline void encode_simdized(
    const double* in_p, double* exc_p, uint16_t* pos_p, uint16_t* exp_c_p, int64_t* dig, uint8_t fac, uint8_t exp) {

	int64_t  tmp_digit {0};
	uint16_t exc_c {0};
	double   cd {0};
	double   orig {0};
	uint64_t pos {0};

	double s_magic_number = static_cast<double>(0x001800000000000);

	// #pragma clang loop vectorize_width(8)
	for (size_t i {0}; i <= 1023; ++i) {
		auto dbl = in_p[i];

		// Attempt conversion
		cd             = dbl * exp_arr[exp] * frac_arr[fac];
		cd             = cd + s_magic_number;
		tmp_digit      = static_cast<int64_t>(cd) - static_cast<int64_t>(s_magic_number);
		dig[i]         = tmp_digit;
		orig           = static_cast<double>(tmp_digit * fact_arr[fac]) * frac_arr[exp];
		tmp_dbl_arr[i] = orig;
	}

#ifdef __AVX512F__
	for (size_t i {0}; i <= 1023; i = i + 8) {
		__m512d l         = _mm512_loadu_pd(tmp_dbl_arr + i);
		__m512d r         = _mm512_loadu_pd(in_p + i);
		__m512i index     = _mm512_loadu_pd(index_arr + i);
		auto    compare_r = _mm512_cmpneq_pd_mask(l, r);
		_mm512_mask_compressstoreu_pd(tmp_index + pos, compare_r, index);
		pos += lookup_table[compare_r];
	}
#else
	for (size_t i {0}; i <= 1023; ++i) {
		auto l         = tmp_dbl_arr[i];
		auto r         = in_p[i];
		auto compare_r = (l != r);
		tmp_index[pos] = i;
		pos += compare_r;
	}
#endif

	int64_t for_sure;
	for (size_t i {0}; i <= 1023; ++i) {
		if (i != tmp_index[i]) {
			for_sure = dig[i];
			break;
		}
	}

	for (size_t j {0}; j < pos; ++j) {
		size_t i     = tmp_index[j];
		auto   dbl   = in_p[i];
		dig[i]       = for_sure;
		exc_p[exc_c] = dbl;
		pos_p[exc_c] = i;
		exc_c        = exc_c + 1;
	}

	*exp_c_p = exc_c;
}

inline void
encode_patch_v6(const double* in_p, double* exc_p, uint16_t* pos_p, uint16_t* exp_c_p, int64_t* dig, state stt) {

	int64_t  tmp_digit {0};
	uint16_t exc_c {0};
	double   cd {0};
	double   orig {0};
	uint64_t pos {0};

	auto fac = stt.fac;
	auto exp = stt.exp;

	double s_magic_number = static_cast<double>(0x001800000000000);

	// #pragma clang loop vectorize_width(64)
	for (size_t i {0}; i <= 1023; ++i) {
		auto dbl = in_p[i];

		// Attempt conversion
		cd             = dbl * exp_arr[exp] * frac_arr[fac];
		cd             = cd + s_magic_number;
		tmp_digit      = static_cast<int64_t>(cd) - static_cast<int64_t>(s_magic_number);
		dig[i]         = tmp_digit;
		orig           = static_cast<double>(tmp_digit * fact_arr[fac]) * frac_arr[exp];
		tmp_dbl_arr[i] = orig;
	}

#ifdef __AVX512F__
	for (size_t i {0}; i <= 1023; i = i + 8) {
		__m512d l         = _mm512_loadu_pd(tmp_dbl_arr + i);
		__m512d r         = _mm512_loadu_pd(in_p + i);
		__m512i index     = _mm512_loadu_pd(index_arr + i);
		auto    compare_r = _mm512_cmpneq_pd_mask(l, r);
		_mm512_mask_compressstoreu_pd(tmp_index + pos, compare_r, index);
		pos += lookup_table[compare_r];
	}
#else
	for (size_t i {0}; i <= 1023; ++i) {
		auto l         = tmp_dbl_arr[i];
		auto r         = in_p[i];
		auto compare_r = (l != r);
		tmp_index[pos] = i;
		pos += compare_r;
	}
#endif

	int64_t for_sure;
	for (size_t i {0}; i <= 1023; ++i) {
		if (i != tmp_index[i]) {
			for_sure = dig[i];
			break;
		}
	}

	for (size_t j {0}; j < pos; ++j) {
		size_t i   = tmp_index[j];
		auto   dbl = in_p[i];

		cd        = dbl / frac_arr[exp];
		tmp_digit = double_to_int64(cd);
		orig      = static_cast<double>(tmp_digit) * frac_arr[exp];

		if (orig == dbl) {
			tmp_digit = double_to_int64(double(tmp_digit) / fact_arr[fac]);
			orig      = static_cast<double>(tmp_digit * fact_arr[fac]) * frac_arr[exp];
			if (orig == dbl) {
				dig[i] = tmp_digit;
				continue;
			}
		}

		// Attempt convertion with /* and FLOOR
		tmp_digit = static_cast<int64_t>(ceil(cd));
		orig      = static_cast<double>(tmp_digit) * frac_arr[exp];

		if (orig == dbl) {
			tmp_digit = ceil(double(tmp_digit) / fact_arr[fac]);
			orig      = static_cast<double>(tmp_digit * fact_arr[fac]) * frac_arr[exp];
			if (orig == dbl) {
				dig[i] = tmp_digit;
				continue;
			}
		}

		dig[i]       = for_sure;
		exc_p[exc_c] = dbl;
		pos_p[exc_c] = i;
		exc_c        = exc_c + 1;
	}

	*exp_c_p = exc_c;
}

inline void encode_simdized_combined(
    const double* in_p, double* exc_p, uint16_t* pos_p, uint16_t* exp_c_p, int64_t* dig, state& stt) {

	int64_t  tmp_digit {0};
	uint16_t exc_c {0};
	double   cd {0};
	double   orig {0};
	uint64_t pos {0};

	if (stt.rg_n_comb > 1) { // Only if more than 1 found top combinations we sample and search
		find_best_exponent_factor_from_combination(stt.cmb_arr, stt.rg_n_comb, in_p, stt.fac, stt.exp);
	} else {
		stt.exp = stt.cmb_arr[0].first;
		stt.fac = stt.cmb_arr[0].second;
	}

	// #pragma clang loop vectorize_width(64)
	for (size_t i {0}; i <= 1023; ++i) {
		auto dbl = in_p[i];

		// Attempt conversion
		cd             = dbl * exp_arr[stt.exp] * frac_arr[stt.fac];
		cd             = cd + magic_number;
		tmp_digit      = static_cast<int64_t>(cd) - static_cast<int64_t>(magic_number);
		dig[i]         = tmp_digit;
		orig           = static_cast<double>(tmp_digit * fact_arr[stt.fac]) * frac_arr[stt.exp];
		tmp_dbl_arr[i] = orig;
	}

#ifdef __AVX512F__
	for (size_t i {0}; i <= 1023; i = i + 8) {
		__m512d l         = _mm512_loadu_pd(tmp_dbl_arr + i);
		__m512d r         = _mm512_loadu_pd(in_p + i);
		__m512i index     = _mm512_loadu_pd(index_arr + i);
		auto    compare_r = _mm512_cmpneq_pd_mask(l, r);
		_mm512_mask_compressstoreu_pd(tmp_index + pos, compare_r, index);
		pos += lookup_table[compare_r];
	}
#else
	for (size_t i {0}; i <= 1023; ++i) {
		auto l         = tmp_dbl_arr[i];
		auto r         = in_p[i];
		auto compare_r = (l != r);
		tmp_index[pos] = i;
		pos += compare_r;
	}
#endif

	int64_t for_sure;
	for (size_t i {0}; i <= 1023; ++i) {
		if (i != tmp_index[i]) {
			for_sure = dig[i];
			break;
		}
	}

	for (size_t j {0}; j < pos; ++j) {
		size_t i     = tmp_index[j];
		auto   dbl   = in_p[i];
		dig[i]       = for_sure;
		exc_p[exc_c] = dbl;
		pos_p[exc_c] = i;
		exc_c        = exc_c + 1;
	}

	*exp_c_p = exc_c;
}

} // namespace alp
#endif

// NOLINTEND
