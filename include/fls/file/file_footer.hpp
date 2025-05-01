#ifndef FLS_FILE_FILE_FOOTER_HPP
#define FLS_FILE_FILE_FOOTER_HPP

#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/

class FileFooter {
public:
	static void Write(const Connection& connection, const path& dir_path);

public:
	uint64_t magic_bytes;
};

} // namespace fastlanes

#endif // FLS_FILE_FILE_FOOTER_HPP
