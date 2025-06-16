#ifndef FLS_TABLE_STATS_HPP
#define FLS_TABLE_STATS_HPP

#include "fls/common/alias.hpp"
#include "fls/common/bimap.hpp"
#include "fls/common/bimap_frequency.hpp"

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

public:
	TypedStats();
	~TypedStats();

public:
	bool IsConstant();

public:
	///!
	BiMapFrequency<PT> bimap_frequency;
	///!
	PT min;
	///!
	PT max;
	///!
	PT last_seen_val;
	///!
	n_t n_nulls;
	///!
	bool is_double_castable;
};

class FlsStringStats {
public:
	FlsStringStats();

public:
	///!
	bool is_constant;
	///!
	n_t maximum_n_bytes_p_value;
	///
	bool is_numeric;
	///
	BiMapFrequencyStr bimap;
	///
	string last_seen_val;
};

} // namespace fastlanes

#endif // FLS_TABLE_STATS_HPP
