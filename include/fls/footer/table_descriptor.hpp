#ifndef FLS_FOOTER_TABLE_DESCRIPTOR_HPP
#define FLS_FOOTER_TABLE_DESCRIPTOR_HPP

#include "fls/footer/rowgroup_descriptor.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Table;
/*--------------------------------------------------------------------------------------------------------------------*/

class TableDescriptor {
public: /* Constructors */
	TableDescriptor();

public:
	vector<RowgroupDescriptor> m_rowgroup_descriptors;
	n_t                        m_table_size;
	//
	n_t GetNRowgroups() const;
};

up<TableDescriptor> make_table_descriptor(const Table& table);
up<TableDescriptor> make_table_descriptor(const path& dir_path);

} // namespace fastlanes

#endif // FLS_FOOTER_TABLE_DESCRIPTOR_HPP
