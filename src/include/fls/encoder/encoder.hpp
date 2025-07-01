#ifndef FLS_ENCODER_ENCODER_HPP
#define FLS_ENCODER_ENCODER_HPP

#include "fls/footer/table_descriptor_generated.h"
#include "fls/std/filesystem.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/table/table.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

class Encoder {
public:
	static void encode(Table& table, TableDescriptorT& descriptor, const path& file_path);

	static n_t
	encode_row_group(const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer, const path& file_path, n_t offset);

	static void encode_row_groupv2(Buf& buf, const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer);
};
} // namespace fastlanes

#endif // FLS_ENCODER_ENCODER_HPP
