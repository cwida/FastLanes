#ifndef FLS_FILE_FILE_HEADER_HPP
#define FLS_FILE_FILE_HEADER_HPP

#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/

class Setting {
public:
	uint8_t inline_footer;
	uint8_t empty_option_0;
	uint8_t empty_option_1;
	uint8_t empty_option_2;
	uint8_t empty_option_3;
	uint8_t empty_option_4;
	uint8_t empty_option_5;
	uint8_t empty_option_6;
};

static_assert(sizeof(Setting) == 8);

class FileHeader {
public:
	static void Write(const Connection& connection, const path& dir_path);

public:
	uint64_t magic_bytes;
	uint64_t version;
	Setting  settings;
};

static_assert(sizeof(FileHeader) == 24);

} // namespace fastlanes

#endif // FLS_FILE_FILE_HEADER_HPP
