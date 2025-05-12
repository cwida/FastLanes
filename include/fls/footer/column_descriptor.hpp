#ifndef FLS_FOOTER_COLUMN_DESCRIPTOR_HPP
#define FLS_FOOTER_COLUMN_DESCRIPTOR_HPP

#include "fls/common/alias.hpp"
#include "fls/common/decimal.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/new_rpn.hpp" // for NewRPN
#include "fls/footer/footer_generated.h"
#include "fls/std/string.hpp"
#include "fls/std/unordered_map.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * ColumnDescriptor
\*--------------------------------------------------------------------------------------------------------------------*/
using ColumnDescriptors = vector<class ColumnDescriptor>;

class ColumnDescriptor {

public:
	ColumnDescriptor();
	explicit ColumnDescriptor(idx_t idx, string name, DataType type);
	ColumnDescriptor(ColumnDescriptor&&)                   = default;
	ColumnDescriptor& operator=(const ColumnDescriptor&) & = default;
	~ColumnDescriptor()                                    = default;
	ColumnDescriptor(const ColumnDescriptor&)              = default;

public:
	///!
	DataType data_type;
	///!
	NewRPN encoding_rpn;
	///!
	n_t idx;
	///!
	string name;
	///!
	ColumnDescriptors children;
	///!
	unordered_map<string, idx_t> name_idx_map;
	///!
	BinaryValueT max;
	///
	sz_t column_offset;
	///
	sz_t total_size;
	///
	unordered_map<OperatorToken, n_t> expr_space;
	///
	vector<SegmentDescriptorT> segment_descriptors;
	///
	n_t n_null;
	///!
	DecimalType fix_me_decimal_type;
};

} // namespace fastlanes
#endif // FLS_FOOTER_COLUMN_DESCRIPTOR_HPP
