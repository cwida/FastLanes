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
class ExpEncodedCol;
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
	static void flush(io& io, const ExpEncodedCol& exp_encoded_col);
	///
	static void flush(io& io, const Buf& buf);
	///
	static void read(const io& io, Buf& buf);
	///
	template <typename PT>
	static span<PT> read(const io& io);
	///
	static bsz_t get_size(const io& io);
};

} // namespace fastlanes

#endif // FLS_IO_IO_HPP
