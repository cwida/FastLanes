#include "fls/io/file.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/string.hpp"
#include <sstream>

namespace fastlanes {

File::File(const path& path) // NOLINT
    : m_path(path) {}

File::~File() {

	if (m_of_stream != nullptr) { FileSystem::close(*m_of_stream); }

	if (m_if_stream != nullptr) { FileSystem::close(*m_if_stream); }
}

void File::Write(const Buf& buf) {
	if (m_of_stream == nullptr) { m_of_stream = make_unique<std::ofstream>(FileSystem::open_w(m_path)); }
	//
	m_of_stream->write(reinterpret_cast<char*>(buf.data()), static_cast<int64_t>(buf.Size()));
}

void File::Read(Buf& buf) {
	if (m_if_stream == nullptr) { m_if_stream = make_unique<std::ifstream>(FileSystem::open_r_binary(m_path)); }

	FLS_ASSERT_LE(fs::file_size(m_path), buf.Capacity())

	m_if_stream->read(reinterpret_cast<char*>(buf.mutable_data()), static_cast<int64_t>(buf.Size()));
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * STATIC
\*--------------------------------------------------------------------------------------------------------------------*/
string File::read(const path& file_path) {
	std::ifstream     json_stream = FileSystem::open_r(file_path);
	std::stringstream buffer;
	buffer << json_stream.rdbuf();
	return buffer.str();
}

void File::write(const path& dir_path, const string& dump) {
	auto file = FileSystem::open_w(dir_path);

	file << dump;

	FileSystem::close(file);
}
} // namespace fastlanes