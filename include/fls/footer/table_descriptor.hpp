#ifndef FLS_FOOTER_TABLE_DESCRIPTOR_HPP
#define FLS_FOOTER_TABLE_DESCRIPTOR_HPP

#include "fls/footer/rowgroup_descriptor.hpp"
#include "fls/footer/table_descriptor_generated.h"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Table;
/*--------------------------------------------------------------------------------------------------------------------*/
up<TableDescriptorT> make_table_descriptor(const Table& table);
//
up<TableDescriptorT> make_table_descriptor(const path& file_path);
//
up<TableDescriptorT> make_table_descriptor(const path& file_path, n_t offset, n_t size);

} // namespace fastlanes

#endif // FLS_FOOTER_TABLE_DESCRIPTOR_HPP
