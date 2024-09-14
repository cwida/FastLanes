#ifndef FLS_IO_FILE_HPP
#define FLS_IO_FILE_HPP

#include "fls/common/common.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/std/string.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

class File {
public:
	explicit File(const path& path);
	~File();

public:
	/// write to file_path
	void Write(const Buf& buf);
	/// write to file_path
	void Read(Buf& buf);

public:
	/// read from file_path and return string.
	static string read(const path& file_path);
	/// write to file_path
	static void write(const path& file_path, const string& dump);

private:
	path              m_path;
	up<std::ofstream> m_of_stream;
	up<std::ifstream> m_if_stream;
};
} // namespace fastlanes

#endif // FLS_IO_FILE_HPP
