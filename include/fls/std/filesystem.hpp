#ifndef FLS_STD_FILESYSTEM_HPP
#define FLS_STD_FILESYSTEM_HPP

#include <filesystem>
#include <fstream>

namespace fastlanes {
using path    = std::filesystem::path;
using fstream = std::fstream;
namespace fs  = std::filesystem;

class FileSystem {
public:
	///! open read
	static std::ifstream open_r(const path& file);
	///! open read in binary
	static std::ifstream open_r_binary(const path& file);
	///! open write
	static std::ofstream open_w(const path& file);
	///! close
	template <typename STREAM>
	static void close(STREAM& stream);
};

} // namespace fastlanes

#endif // FLS_STD_FILESYSTEM_HPP
