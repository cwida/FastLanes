#ifndef FLS_ENCODER_ENCODER_HPP
#define FLS_ENCODER_ENCODER_HPP

#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

class Encoder {
public:
	static void encode_rowgroup(Buf& buf, const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer);
};
} // namespace fastlanes

#endif // FLS_ENCODER_ENCODER_HPP
