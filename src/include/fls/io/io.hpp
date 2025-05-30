#ifndef FLS_IO_IO_HPP
#define FLS_IO_IO_HPP

#include "fls/common/alias.hpp"
#include "fls/io/external_memory.hpp"
#include "fls/io/file.hpp"
#include "fls/std/span.hpp"
#include "fls/std/variant.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Mmap;
class S3;
class Socket;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * IOType
\*--------------------------------------------------------------------------------------------------------------------*/
enum class IOType : uint8_t {
	INVALID = 0,
	FILE    = 1,
	MEMORY  = 2,
	MMAP    = 3,
	S3      = 4,
	SOCKET  = 5,
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * io
\*--------------------------------------------------------------------------------------------------------------------*/
using io = variant<std::monostate,
                   up<File>,          //
                   up<ExternalMemory> //
                   // up<Mmap>,       //
                   // up<S3>,         //
                   // up<Socket>      //
                   >;

/*--------------------------------------------------------------------------------------------------------------------*\
 * IO
\*--------------------------------------------------------------------------------------------------------------------*/
class IO {
public:
	///
	static void flush(io& io, const Buf& buf);
	///
	static void append(io& io, const Buf& buf);
	///
	static void append(io& io, const char* pointer, n_t size);
	///
	static void read(const io& io, Buf& buf);
	///
	static void range_read(const io& io, Buf& buf, n_t offset, n_t size);
	///
	template <typename PT>
	static span<PT> read(const io& io);
	///
	static n_t get_size(const io& io);
};

} // namespace fastlanes

#endif // FLS_IO_IO_HPP
