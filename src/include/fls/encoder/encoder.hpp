#ifndef FLS_ENCODER_ENCODER_HPP
#define FLS_ENCODER_ENCODER_HPP

#include "fls/footer/table_descriptor_generated.h"
#include "fls/std/filesystem.hpp"
#include "fls/table/table.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

class Encoder {
public:
	static void encode(Table& table, TableDescriptorT& descriptor, const path& file_path);
};
} // namespace fastlanes

#endif // FLS_ENCODER_ENCODER_HPP
