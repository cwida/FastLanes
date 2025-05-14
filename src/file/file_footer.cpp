#include "fls/file/file_footer.hpp"
#include "fls/connection.hpp"
#include "fls/file/file_header.hpp"
#include "fls/info.hpp"
#include "fls/io/io.hpp"

namespace fastlanes {

void FileFooter::Write(const Connection& connection, const path& file_path, const FileFooter& file_footer) {
	io file_io = make_unique<File>(file_path); // TODO[io]

	IO::append(file_io, reinterpret_cast<const char*>(&file_footer), sizeof(file_footer));
}

Status FileFooter::Load(FileFooter& file_footer, const path& file_path) {
	const io io = make_unique<File>(file_path);

	if (const auto file_size = IO::get_size(io); file_size < sizeof(FileHeader) + sizeof(FileFooter)) {
		return Status::Error(Status::ErrorCode::ERR_1_SMALL_FILE_SIZE);
	}

	std::ifstream file(file_path, std::ios::binary);

	// Seek to 8 bytes before end
	file.seekg(static_cast<std::streamoff>(-1) * static_cast<std::streamoff>(sizeof(FileFooter)), std::ios::end);

	// Read last 8 bytes
	file.read(reinterpret_cast<char*>(&file_footer), sizeof(FileFooter));

	if (file_footer.magic_bytes != Info::get_magic_bytes()) {
		return Status::Error(Status::ErrorCode::ERR_5_INVALID_MAGIC_BYTES);
	}

	return Status::Ok();
}
} // namespace fastlanes