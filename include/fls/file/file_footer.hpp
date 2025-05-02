#ifndef FLS_FILE_FILE_FOOTER_HPP
#define FLS_FILE_FILE_FOOTER_HPP

#include "fls/common/alias.hpp"
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/

class FileFooter {
public:
	static void write(const Connection& connection, const path& dir_path, n_t table_descriptor_size);

public:
	n_t table_descriptor_size;
	n_t magic_bytes;
};

static_assert(sizeof(FileFooter) == 16);

} // namespace fastlanes

#endif // FLS_FILE_FILE_FOOTER_HPP
