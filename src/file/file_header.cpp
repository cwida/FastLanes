#include "fls/file/file_header.hpp"
#include "fls/connection.hpp"
#include "fls/file/file_footer.hpp"
#include "fls/info.hpp"
#include "fls/io/io.hpp"

namespace fastlanes {

void FileHeader::Write(const Connection& connection, const path& file_path) {
	io         file_io = make_unique<File>(file_path); // TODO[io]
	FileHeader file_header {};

	file_header.magic_bytes            = Info::get_magic_bytes();
	file_header.version                = Info::get_version_bytes();
	file_header.settings.inline_footer = connection.is_footer_inlined();

	IO::append(file_io, reinterpret_cast<const char*>(&file_header), sizeof(file_header));
}

Status FileHeader::Load(FileHeader& file_header, const path& file_path) {
	io io = make_unique<File>(file_path); // todo[IO]

	if (const auto file_size = IO::get_size(io); file_size < sizeof(FileHeader) + sizeof(FileFooter)) {
		return Status::Error(Status::ErrorCode::ERR_1_SMALL_FILE_SIZE);
	}

	std::ifstream file(file_path, std::ios::binary);

	auto fastlanes_file = FileSystem::open_r(file_path);

	// Read first 24 bytes
	file.read(reinterpret_cast<char*>(&file_header), sizeof(FileHeader));

	return Status::Ok();
}
} // namespace fastlanes