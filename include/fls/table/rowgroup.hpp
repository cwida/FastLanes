#ifndef FLS_TABLE_ROWGROUP_HPP
#define FLS_TABLE_ROWGROUP_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/string.hpp"
#include "fls/std/variant.hpp"
#include "fls/std/vector.hpp"
#include "fls/table/stats.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Vector;
class LogicalExpr;
class column;
struct RowgroupDescriptorT;
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/
using null_map_arr = vector<uint8_t>;
using byte_arr_t   = vector<uint8_t>;
using ofs_arr_t    = vector<ofs_t>;
using length_arr_t = vector<len_t>;

class BaseCol {
public:
	null_map_arr null_map_arr;
};

class VariableSizeCol : public BaseCol {
public:
	ofs_arr_t    ofs_arr;
	length_arr_t length_arr;
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
using col_i08   = TypedCol<i08_pt>;
using col_i16   = TypedCol<i16_pt>;
using col_i32   = TypedCol<i32_pt>;
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
                       up<col_i08>,
                       up<col_i16>,
                       up<col_i32>,
                       up<col_i64>,
                       up<flt_col_t>,
                       up<dbl_col_t>,
                       up<str_col_t>,
                       up<class FLSStrColumn>,
                       up<class List>,
                       up<class Struct>>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * TypedColumnView
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class TypedColumnView {
public:
	explicit TypedColumnView(const col_pt& column);

public:
	const PT*            Data();
	const PT*            Data(n_t vec_idx);
	static constexpr n_t GetSizeOfOneVector();
	void                 PointTo(const n_t a_vec_n) {
		                this->m_vec_idx = a_vec_n;
	}
	[[nodiscard]] n_t TotalSize() const;
	const uint8_t*    NullMap() const;
	const n_t         GetNTuples() const;

private:
	const PT*       m_data;
	n_t             m_vec_idx;
	TypedStats<PT>* m_stats_p;
	n_t             n_vals;
	const uint8_t*  m_bools;
	n_t             n_tuples;

public:
	[[nodiscard]] TypedStats<PT>* GetStats() const {
		return m_stats_p;
	}
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * NullMapView
\*--------------------------------------------------------------------------------------------------------------------*/
class NullMapView {
public:
	explicit NullMapView(const col_pt& column);

public:
	void PointTo(const n_t a_vec_n) {
		this->m_vec_idx = a_vec_n;
	}
	const uint8_t* NullMap() const;

private:
	const uint8_t* m_null_map;
	n_t            m_vec_idx;
};

template <typename PT>
constexpr n_t TypedColumnView<PT>::GetSizeOfOneVector() {
	return sizeof(PT) * CFG::VEC_SZ;
}
/*--------------------------------------------------------------------------------------------------------------------*\
 * FLSStringView
\*--------------------------------------------------------------------------------------------------------------------*/
class FlsStrColumnView {
public:
	explicit FlsStrColumnView(const col_pt& column);

public:
	[[nodiscard]] uint8_t*  Data() const;
	[[nodiscard]] uint8_t** String_p() const;
	[[nodiscard]] len_t*    Length() const;
	void                    PointTo(const n_t a_vec_n);
	static constexpr n_t    GetSizeOfOneVector() {
		   return sizeof(ofs_t) * CFG::VEC_SZ;
	}
	[[nodiscard]] uint8_t**     FsstString() const;
	[[nodiscard]] len_t*        FSSTLength() const;
	[[nodiscard]] fls_string_t* String() const;
	const n_t                   GetNTuples() const;

public:
	uint8_t**       string_p;
	len_t*          length_ptr;
	const n_t*      ttl_size_ptr;
	n_t             vec_idx;
	n_t             n_tuples;
	FlsStringStats& stats;
	uint8_t**       fsst_string_p;
	len_t*          fsst_length_ptr;
	fls_string_t*   fls_string_p;
};

using rowgroup_pt = vector<col_pt>;

class List : public VariableSizeCol {
public:
	col_pt child;
};

class FLSStrColumn : public VariableSizeCol {
public:
	vector<uint8_t>  byte_arr;
	vector<uint8_t*> str_p_arr;
	FlsStringStats   m_stats;

	vector<uint8_t*>     fsst_str_p_arr;
	length_arr_t         fsst_length_arr;
	vector<uint8_t>      fsst_byte_arr;
	vector<fls_string_t> fls_str_arr;
};

class Struct : public BaseCol {
public:
	rowgroup_pt internal_rowgroup;
};

class RowgroupComparisonResult {
public:
	bool   is_equal {true};
	n_t    first_failed_column_idx {0};
	n_t    first_failed_row_idx {0};
	string description;
};

class Rowgroup {
public:
	friend class LogicalExpr;
	friend class column;

public:
	explicit Rowgroup(const RowgroupDescriptorT& rowgroup_footer, const Connection& connection);

	Rowgroup(const Rowgroup&)             = delete;
	Rowgroup& operator=(const Rowgroup&)  = delete;
	Rowgroup(const Rowgroup&&)            = delete;
	Rowgroup& operator=(const Rowgroup&&) = delete;

	RowgroupComparisonResult operator==(const Rowgroup& other_rowgroup) const;

public:
	[[deprecated]] void ReadCsv(const path& csv_path, char delimiter = '|', char terminator = '\n');
	[[deprecated]] void ReadJson(const path& json_path);
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
	[[nodiscard]] RowgroupDescriptor& GetRowgroupDescriptor();
	///
	[[nodiscard]] up<Rowgroup> Project(const vector<idx_t>& idxs, const Connection& connection);
	///
	[[nodiscard]] up<Rowgroup> Project(const vector<string>& idxs, const Connection& connection);
	///
	void GetStatistics();
	///
	void Finalize();
	///
	void Cast();
	///
	void Init();
	///
	void FillMissingValues(n_t how_many_to_fill);

public: /* Members */
	RowgroupDescriptorT m_descriptor;
	n_t                 n_tup;
	rowgroup_pt         internal_rowgroup;
	const Connection&   m_connection;
	const n_t           capacity;
};

std::ostream& operator<<(std::ostream& output, const Rowgroup& mini_arrow);

} // namespace fastlanes

#endif // FLS_TABLE_ROWGROUP_HPP
