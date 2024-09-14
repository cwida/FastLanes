#ifndef FLS_FOOTER_ROWGROUP_FOOTER_HPP
#define FLS_FOOTER_ROWGROUP_FOOTER_HPP

#include "fls/common/alias.hpp"       // for sz_t, n_t
#include "fls/expression/new_rpn.hpp" // for NewRPN
#include "fls/std/vector.hpp"         // for vector
#include <limits>                     // for numeric_limits
#include <stddef.h>                   // for size_t

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Rowgroup;
enum class DataType : uint8_t;
/*--------------------------------------------------------------------------------------------------------------------*/
enum class ColumnType : uint8_t {
	INVALID    = 0,
	HORIZONTAL = 1,
	VERTICAL   = 2,
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnMetadata
\*--------------------------------------------------------------------------------------------------------------------*/
class ColumnMetadata {

public:
	ColumnMetadata();
	explicit ColumnMetadata(const DataType& logical_type);

public:
	/// it is determined already?
	[[nodiscard]] bool IsDetermined() const;

public:
	///!
	DataType data_type;
	/// offset to column
	sz_t offset;
	/// offset to column
	sz_t size;
	///!
	NewRPN encoding_rpn;
	/// is this sub plan determined?
	bool m_is_determined;

public:
	constexpr static sz_t INVALID_OFFSET = std::numeric_limits<sz_t>::max(); // INVALID
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * Footer
      -  is composed of one ColumnMetadata for each column in schema
\*--------------------------------------------------------------------------------------------------------------------*/
class Footer {
public:
	Footer();
	explicit Footer(const Rowgroup& row_group);

public:
	///
	void push_back(ColumnMetadata&&);
	///
	ColumnMetadata& operator[](size_t idx);
	///
	const ColumnMetadata& operator[](size_t idx) const;
	///
	[[nodiscard]] size_t size() const;

public:
	/// number of vectors
	n_t n_vec;
	/// metadata of each column in rowgroup
	vector<ColumnMetadata> column_metadatas;
	/// binary size of rowgroup
	sz_t rowgroup_size;
};

} // namespace fastlanes

#endif
