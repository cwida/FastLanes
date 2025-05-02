#include "fls/common/status.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * Status
\*--------------------------------------------------------------------------------------------------------------------*/

// Constructor
Status::Status(bool success, ErrorCode code)
    : success(success)
    , code(code) {
}

// Static factory for Ok
Status Status::Ok() {
	return {true, ErrorCode::Ok};
}

// Static factory for Error
Status Status::Error(ErrorCode code) {
	return {false, code};
}

// Message lookup
std::string_view Status::message_for(ErrorCode code) {
	switch (code) {
	case ErrorCode::Ok:
		return "";
	case ErrorCode::ERR_1_SMALL_FILE_SIZE:
		return "File too small";
	case ErrorCode::ERR_2_INVALID_HEADER:
		return "Invalid header";
	case ErrorCode::ERR_3_INVALID_FOOTER:
		return "Invalid footer";
	case ErrorCode::ERR_4_INVALID_CHECKSUM:
		return "Checksum mismatch";
	case ErrorCode::ERR_5_INVALID_MAGIC_BYTES:
		return "Invalid magic bytes";
	case ErrorCode::ERR_6_INVALID_VERSION_BYTES:
		return "Unsupported version";
	case ErrorCode::ERR_7_INVALID_ROWGROUP_DESCRIPTOR:
		return "Corrupt row group descriptor";
	case ErrorCode::ERR_8_INVALID_TABLE_DESCRIPTOR:
		return "Corrupt table descriptor";
	case ErrorCode::ERR_9_INVALID_ROWGROUP_COUNT:
		return "Invalid row group count";
	case ErrorCode::ERR_10_INVALID_ROWGROUP_SIZE:
		return "Row group size mismatch";
	case ErrorCode::Error2:
		return "Generic error"; // TODO: Rename or remove
	default:
		return "Unknown error";
	}
}

} // namespace fastlanes