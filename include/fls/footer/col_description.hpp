#ifndef FLS_FOOTER_COL_DESCRIPTION_HPP
#define FLS_FOOTER_COL_DESCRIPTION_HPP

#include "fls/common/alias.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/std/string.hpp"
#include "fls/std/unordered_map.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
class ColDescription;
using col_descriptions_t = vector<ColDescription>;

class ColDescription {
public: /* Constructors */
	ColDescription(idx_t idx, string name, DataType type);
	ColDescription(ColDescription&&)                   = default;
	ColDescription& operator=(const ColDescription&) & = default;
	ColDescription& operator=(ColDescription&&)        = delete;
	~ColDescription()                                  = default;
	ColDescription(const ColDescription&)              = default;

public:
	///!
	idx_t idx;
	///!
	string name;
	///!
	DataType type;
	///!
	col_descriptions_t children;
	///!
	unordered_map<string, idx_t> name_idx_map;
};

} // namespace fastlanes
#endif // FLS_FOOTER_COL_DESCRIPTION_HPP
