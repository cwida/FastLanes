#ifndef DATA_WRONG_SCHEMA_HPP
#define DATA_WRONG_SCHEMA_HPP

#include <string>

namespace fastlanes {

class WRONG_SCHEMA {
public:
	static constexpr std::string_view FLOAT {FLS_CMAKE_SOURCE_DIR "/data/wrong_schema/float"};
};
} // namespace fastlanes

#endif // DATA_WRONG_SCHEMA_HPP
