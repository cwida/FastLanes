#ifndef FLS_TABLE_ROWGROUP_HPP
#define FLS_TABLE_ROWGROUP_HPP

#include "fls/common/common.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/string.hpp"
#include "fls/std/variant.hpp"
#include "fls/std/vector.hpp"
#include "fls/table/schema.hpp"
#include "fls/table/stats.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Vector;
class LogicalExpr;
class column;
/*--------------------------------------------------------------------------------------------------------------------*/
using null_map_arr = vector<bool>;
using byte_arr_t   = vector<uint8_t>;
using ofs_arr_t    = vector<ofs_t>;
using length_arr_t = vector<len_t>;

class BaseCol {
public:
	null_map_arr null_map_arr {};
};

class VariableSizeCol : public BaseCol {
public:
	ofs_arr_t ofs_arr {};
};

template <typename T>
class TypedCol : public BaseCol {
public:
	TypedCol() = default;

public:
	vector<T>     data;
	TypedStats<T> m_stats;
};

using str_col_t = TypedCol<str_pt>;
using flt_col_t = TypedCol<flt_pt>;
using dbl_col_t = TypedCol<dbl_pt>;
using i08_col_t = TypedCol<i08_pt>;
using i16_col_t = TypedCol<i16_pt>;
using i32_col_t = TypedCol<i32_pt>;
using col_i64   = TypedCol<i64_pt>;
using u08_col_t = TypedCol<u08_pt>;
using u16_col_t = TypedCol<u16_pt>;
using u32_col_t = TypedCol<u32_pt>;
using u64_col_t = TypedCol<u64_pt>;

using col_pt = variant<std::monostate,
                       up<u08_col_t>,
                       up<u16_col_t>,
                       up<u32_col_t>,
                       up<u64_col_t>,
                       up<i08_col_t>,
                       up<i16_col_t>,
                       up<i32_col_t>,
                       up<col_i64>,
                       up<flt_col_t>,
                       up<dbl_col_t>,
                       up<str_col_t>,
                       up<class List>,
                       up<class Struct>>;

using rowgroup_pt = vector<col_pt>;

class List : public VariableSizeCol {
public:
	col_pt child {};
};

class Struct : public BaseCol {
public:
	rowgroup_pt table {};
};

class Rowgroup {
public:
	friend class LogicalExpr;
	friend class column;

public:
	explicit Rowgroup(const Schema& schema);
	Rowgroup(const Rowgroup&)             = delete;
	Rowgroup& operator=(const Rowgroup&)  = delete;
	Rowgroup(const Rowgroup&&)            = delete;
	Rowgroup& operator=(const Rowgroup&&) = delete;

public:
	///
	void ReadCsv(const path& csv_path, char delimiter = '|', char terminator = '\n');
	///
	void ReadJson(const path& json_path);
	///
	void WriteJson(std::ostream& os) const;
	///
	[[nodiscard]] n_t RowCount() const;
	///
	[[nodiscard]] n_t VecCount() const;
	///
	[[nodiscard]] n_t ColCount() const;
	///
	[[nodiscard]] idx_t LookUp(const string& name) const;
	///
	[[nodiscard]] DataType GetDataType(idx_t col_idx) const;
	///
	[[nodiscard]] Schema& GetSchema();
	///
	[[nodiscard]] up<Rowgroup> Project(const vector<idx_t>& idxs);
	///
	[[nodiscard]] up<Rowgroup> Project(const vector<string>& idxs);
	///
	[[nodiscard]] bool Equal(n_t first_col_idx, n_t second_col_idx) const;
	///
	[[nodiscard]] bool IsMap1t1(n_t first_col_idx, n_t second_col_idx) const;
	///
	[[nodiscard]] bool is_good_for_ditionary_encoding(n_t col_idx) const;

public: /* Members */
	Schema      m_schema;
	n_t         n_tup;
	rowgroup_pt internal_rowgroup;
};

std::ostream& operator<<(std::ostream& output, const Rowgroup& mini_arrow);

} // namespace fastlanes

#endif // FLS_TABLE_ROWGROUP_HPP
