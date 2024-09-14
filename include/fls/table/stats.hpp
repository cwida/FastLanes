#ifndef FLS_TABLE_STATS_HPP
#define FLS_TABLE_STATS_HPP

#include "fls/common/alias.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/std/unordered_map.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Struct;
class List;
class Column;
class Rowgroup;
template <typename PT>
class TypedCol;
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class TypedStats {
	///!
	class NumericStats {
	public:
		bool    is_there_negative     = false;
		uint8_t maximum_required_bits = 64;
	};
	///!
	class StrStats {
	public:
		idx_t total_length        = 0;
		idx_t total_unique_length = 0;
		idx_t total_run_length    = 0;
	};
	///!
	using type_specific_stats_t = std::conditional_t<is_str<PT>(), StrStats, NumericStats>;
	///!
	class ValueMtd {
	public:
		explicit ValueMtd(n_t dict_code);

	public:
		n_t dict_code;
		n_t repetition;
	};

public:
	TypedStats();

public:
	///!
	unordered_map<PT, ValueMtd> dict;
	///!
	type_specific_stats_t t_stats;
	///!
	n_t n_null;
	///!
	n_t n_run;
	///!
	bool is_constant;
	///!
	PT min;
	///!
	PT max;
};

} // namespace fastlanes

#endif // FLS_TABLE_STATS_HPP
