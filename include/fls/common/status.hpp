#ifndef FOR_NOW_ERROR_HPP
#define FOR_NOW_ERROR_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

class Status {
public:
	enum class ErrorCode {
		Ok,
		ERR_1_SMALL_FILE_SIZE,
		ERR_2_INVALID_HEADER,
		ERR_3_INVALID_FOOTER,
		ERR_4_INVALID_CHECKSUM,
		ERR_5_INVALID_MAGIC_BYTES,
		ERR_6_INVALID_VERSION_BYTES,
		ERR_7_INVALID_ROWGROUP_DESCRIPTOR,
		ERR_8_INVALID_TABLE_DESCRIPTOR,
		ERR_9_INVALID_ROWGROUP_COUNT,
		ERR_10_INVALID_ROWGROUP_SIZE,
		Error2,
		// Add more as needed
	};

	bool      success;
	ErrorCode code;

	static Status      Ok();
	static Status      Error(ErrorCode code);
	static string_view message_for(ErrorCode code);

private:
	Status(bool success, ErrorCode code);
};

} // namespace fastlanes

#endif // FOR_NOW_ERROR_HPP
