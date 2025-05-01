#include "fls/file/file_header.hpp"
#include "fls/connection.hpp"
#include "fls/info.hpp"
#include "fls/io/io.hpp"

namespace fastlanes {

void FileHeader::Write(const Connection& connection, const path& dir_path) {
	io file_io = make_unique<File>(dir_path / FASTLANES_FILE_NAME); // TODO[io]

	FileHeader file_header {};
	file_header.magic_bytes            = Info::get_magic_bytes();
	file_header.version                = Info::get_version_bytes();
	file_header.settings.inline_footer = connection.is_footer_inlined();

	IO::append(file_io, reinterpret_cast<const char*>(&file_header), sizeof(file_header));
}
} // namespace fastlanes