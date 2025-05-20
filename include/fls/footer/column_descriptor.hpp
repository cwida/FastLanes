#ifndef FLS_FOOTER_COLUMN_DESCRIPTOR_HPP
#define FLS_FOOTER_COLUMN_DESCRIPTOR_HPP

#include "fls/common/alias.hpp"
#include "fls/common/decimal.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/new_rpn.hpp" // for NewRPN
#include "fls/footer/binary_value.hpp"
#include "fls/footer/segment_descriptor.hpp"
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
	BinaryValue max;
	/**
	 * @brief Represents the offset (in bytes) of the column's data within the serialized buffer.
	 *
	 * This value is used to indicate the starting position of the column's data in a serialized storage
	 * format. It is set during the serialization process and helps in locating and accessing the column's
	 * data efficiently. The offset is relative to the beginning of the buffer.
	 *
	 * This member is read and written during serialization and deserialization processes, ensuring that
	 * data integrity and structure are maintained during storage and retrieval operations.
	 */
	sz_t column_offset;
	///
	sz_t total_size;
	///
	unordered_map<OperatorToken, n_t> expr_space;
	///
	vector<SegmentDescriptor> segment_descriptors;
	///
	n_t n_null;
	///!
	DecimalType fix_me_decimal_type;
};

} // namespace fastlanes
#endif // FLS_FOOTER_COLUMN_DESCRIPTOR_HPP
