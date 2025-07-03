#ifndef FLS_FLATBUFFER_FLATBUFFER_HPP
#define FLS_FLATBUFFER_FLATBUFFER_HPP

#include "fls/common/common.hpp"
#include "fls/io/io.hpp"
#include "fls/std/filesystem.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct TableDescriptorT;
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * FLATBUFFERS
\*--------------------------------------------------------------------------------------------------------------------*/
class FlatBuffers {
public:
	static n_t Write(io& io, const TableDescriptorT& table_descriptor);
};

/// write the footer or profiling as json file

} // namespace fastlanes

#endif // FLS_FLATBUFFER_FLATBUFFER_HPP
