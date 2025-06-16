#ifndef FLS_FILE_FOOTER_HPP
#define FLS_FILE_FOOTER_HPP

#include "fls/footer/column_descriptor.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/unordered_map.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Rowgroup;
enum class DataType : uint8_t;
/*--------------------------------------------------------------------------------------------------------------------*/

using map                       = unordered_map<string, idx_t>;
using col_descripption_it       = vector<ColumnDescriptor>::iterator;
using const_col_descripption_it = vector<ColumnDescriptor>::const_iterator;

class Footer {
public: /* Constructors */
	Footer();
	Footer(const Footer&)              = default;
	Footer(Footer&&)                   = default;
	Footer& operator=(const Footer&) & = default;
	Footer& operator=(Footer&&) &      = default;
	~Footer()                          = default;

public:
	///
	[[nodiscard]] const ColumnDescriptors& GetColumnDescriptors() const {
		return m_column_descriptors;
	}
	///
	void AddCol(const ColumnDescriptor& col);
	///
	ColumnDescriptor& operator[](n_t idx);
	///
	const ColumnDescriptor& operator[](n_t idx) const;
	///
	[[nodiscard]] n_t GetNextColIdx() const;
	///
	[[nodiscard]] n_t size() const;
	///!
	[[nodiscard]] map GetMap() const;
	///
	col_descripption_it                     begin();
	[[nodiscard]] const_col_descripption_it begin() const;
	col_descripption_it                     end();
	[[nodiscard]] const_col_descripption_it end() const;
	///
	[[nodiscard]] idx_t LookUp(const string& name) const;
	///
	[[nodiscard]] up<Footer> Project(const vector<idx_t>& idxs) const;
	///
	void push_back(ColumnDescriptor&&);
	//
	[[nodiscard]] vector<string> GetColumnNames() const;
	//
	[[nodiscard]] vector<DataType> GetDataTypes() const;
	//
	[[nodiscard]] n_t GetNVectors() const;

public:
	/// number of vectors
	n_t m_n_vec;
	///!
	ColumnDescriptors m_column_descriptors;
	///!
	map m_name_idx_map;
	/// binary size of rowgroup
	sz_t m_rowgroup_size;
};

up<Footer> make_footer(const Rowgroup& rowgroup);
up<Footer> make_footer(const path& dir_path);

} // namespace fastlanes

#endif // FLS_FILE_FOOTER_HPP
