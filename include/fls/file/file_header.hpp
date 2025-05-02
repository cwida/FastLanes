#ifndef FLS_FILE_FILE_HEADER_HPP
#define FLS_FILE_FILE_HEADER_HPP

#include "fls/common/alias.hpp"
#include "fls/common/status.hpp"
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/

class Setting {
public:
	/* 0 */ fls_bool inline_footer {FLS_FALSE}; // 0x58
	/* 1 */ fls_bool empty_option_0 {FLS_FALSE};
	/* 2 */ fls_bool empty_option_1 {FLS_FALSE};
	/* 3 */ fls_bool empty_option_2 {FLS_FALSE};
	/* 4 */ fls_bool empty_option_3 {FLS_FALSE};
	/* 5 */ fls_bool empty_option_4 {FLS_FALSE};
	/* 6 */ fls_bool empty_option_5 {FLS_FALSE};
	/* 7 */ fls_bool empty_option_6 {FLS_FALSE};
};

static_assert(sizeof(Setting) == 8);

class FileHeader {
public:
	static void   Write(const Connection& connection, const path& dir_path);
	static Status Load(FileHeader& file_footer, const path& file_path);

public:
	uint64_t magic_bytes;
	uint64_t version;
	Setting  settings;
};

static_assert(sizeof(FileHeader) == 24);

} // namespace fastlanes

#endif // FLS_FILE_FILE_HEADER_HPP
