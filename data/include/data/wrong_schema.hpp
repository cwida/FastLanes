#ifndef DATA_WRONG_SCHEMA_HPP
#define DATA_WRONG_SCHEMA_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

class WRONG_SCHEMA {
public:
	static constexpr string_view FLOAT {FLS_CMAKE_SOURCE_DIR "/data/wrong_schema/float"};
};
} // namespace fastlanes

#endif // DATA_WRONG_SCHEMA_HPP
