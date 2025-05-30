#ifndef FLS_TABLE_DIR_HPP
#define FLS_TABLE_DIR_HPP

#include "fls/common/common.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/string.hpp"

namespace fastlanes {

enum class FileT : uint8_t {
	INVALID = 0, //
	CSV     = 1,
	JSON    = 2, //
	CONSOLE = 3,
};

inline constexpr auto CSV     = FileT::CSV;
inline constexpr auto JSON    = FileT::JSON;
inline constexpr auto CONSOLE = FileT::CONSOLE;

class Dir {
public:
	string table_name;
	path   file_path;
	path   schema_path;
	FileT  file_t;
};

} // namespace fastlanes

#endif // FLS_TABLE_DIR_HPP
