#ifndef FLS_TABLE_SCHEMA_HPP
#define FLS_TABLE_SCHEMA_HPP

#include "fls/footer/col_description.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/unordered_map.hpp"

namespace fastlanes {
using map                       = unordered_map<string, idx_t>;
using col_descripption_it       = vector<ColDescription>::iterator;
using const_col_descripption_it = vector<ColDescription>::const_iterator;

class Schema {
public: /* Constructors */
	explicit Schema(const path& schema_json_file);
	explicit Schema(const string& json_dump);
	explicit Schema(const col_descriptions_t& col_descriptions);
	Schema()                           = default;
	Schema(const Schema&)              = default;
	Schema(Schema&&)                   = default;
	Schema& operator=(const Schema&) & = default;
	Schema& operator=(Schema&&) &      = default;
	~Schema()                          = default;

public:
	///
	[[nodiscard]] col_descriptions_t& GetColDescriptions() { return m_col_descriptions; }
	///
	[[nodiscard]] col_descriptions_t col_descriptions() const { return m_col_descriptions; }
	///
	void AddCol(const ColDescription& col);
	///
	const ColDescription& operator[](idx_t idx) const;
	///
	[[nodiscard]] idx_t GetNextColIdx() const;
	///
	[[nodiscard]] sz_t size() const;
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
	[[nodiscard]] up<Schema> Project(const vector<idx_t>& idxs) const;

private:
	///
	void parse_json_text(const string& json_text);

private:
	///!
	col_descriptions_t m_col_descriptions;
	///!
	map m_name_idx_map;
};

} // namespace fastlanes

#endif // FLS_TABLE_SCHEMA_HPP
