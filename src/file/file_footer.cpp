#include "fls/file/file_footer.hpp"
#include "fls/connection.hpp"
#include "fls/info.hpp"
#include "fls/io/io.hpp"

namespace fastlanes {

void FileFooter::Write(const Connection& connection, const path& dir_path) {
	io file_io = make_unique<File>(dir_path / FASTLANES_FILE_NAME); // TODO[io]

	FileFooter file_footer {};
	file_footer.magic_bytes = Info::get_magic_bytes();

	IO::append(file_io, reinterpret_cast<const char*>(&file_footer), sizeof(file_footer));
}
} // namespace fastlanes