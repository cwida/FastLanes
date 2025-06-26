#ifndef FLS_FLATBUFFER_FLATBUFFER_HPP
#define FLS_FLATBUFFER_FLATBUFFER_HPP

#include "fls/common/common.hpp"
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
	static n_t Write(fls_bool inlined, const path& file_path, TableDescriptorT& table_descriptor);
};

/// write the footer or profiling as json file

} // namespace fastlanes

#endif // FLS_FLATBUFFER_FLATBUFFER_HPP
