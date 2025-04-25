#include "fls/std/filesystem.hpp"
#include <cstring>

namespace fastlanes {
std::ifstream FileSystem::open_r(const path& file) {
	std::ifstream stream(file.c_str());
	if (!stream) {
		throw std::runtime_error(strerror(errno) + std::string {": "} + file.string());
	}
	return stream;
}

std::ifstream FileSystem::open_r_binary(const path& file) {
	std::ifstream stream(file.c_str(), std::ios::binary);
	if (!stream) {
		throw std::runtime_error(strerror(errno) + std::string {": "} + file.string());
	}
	return stream;
}

std::ofstream FileSystem::open_w(const path& file) {
	std::ofstream stream(file.c_str());
	if (!stream) {
		throw std::runtime_error(strerror(errno) + std::string {": "} + file.string());
	}
	return stream;
}

std::ofstream FileSystem::open_w_binary(const path& file) {
	std::ofstream stream(file.c_str(), std::ios::binary);
	if (!stream) {
		throw std::runtime_error(strerror(errno) + std::string {": "} + file.string());
	}
	return stream;
}

std::ofstream FileSystem::opend_app(const path& file) {
	std::ofstream stream(file.c_str(), std::ios::app);
	if (!stream) {
		throw std::runtime_error(strerror(errno) + std::string {": "} + file.string());
	}
	return stream;
}

void FileSystem::check_if_dir_exists(const path& dir_path) {
	if (!exists(dir_path) || !is_directory(dir_path)) {
		throw std::runtime_error("Directory with path | " + dir_path.string() + " | does not exist.");
	}
}

template <typename STREAM>
void FileSystem::close(STREAM& stream) {
	stream.close();
}

template void FileSystem::close(std::ifstream& stream);
template void FileSystem::close(std::ofstream& stream);

} // namespace fastlanes