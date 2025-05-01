#ifndef DATA_TEST_HPP
#define DATA_TEST_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {

/* ---------------------------------------------------------------------------
   Helper aliases
   -------------------------------------------------------------------------*/
using dataset_entry_t = std::pair<string_view, string_view>;
using test_dataset_t  = std::array<dataset_entry_t, 6>;

/* ---------------------------------------------------------------------------
   Dataset of sample FastLanes files
   -------------------------------------------------------------------------*/
class test_dataset {
public:
	// Absolute or CMake-relative paths (CMake sets FLS_CMAKE_SOURCE_DIR)
	static constexpr string_view VALID_FLS {FLS_CMAKE_SOURCE_DIR "/data/test/verify_fastlanes_file_tests/valid.fls"};

	static constexpr string_view BAD_HEADER_MAGIC {FLS_CMAKE_SOURCE_DIR
	                                               "/data/test/verify_fastlanes_file_tests/bad_header_magic.fls"};

	static constexpr string_view BAD_FOOTER_MAGIC {FLS_CMAKE_SOURCE_DIR
	                                               "/data/test/verify_fastlanes_file_tests/bad_footer_magic.fls"};

	static constexpr string_view BAD_VERSION {FLS_CMAKE_SOURCE_DIR
	                                          "/data/test/verify_fastlanes_file_tests/bad_version.fls"};

	static constexpr string_view MISSING_FOOTER {FLS_CMAKE_SOURCE_DIR
	                                             "/data/test/verify_fastlanes_file_tests/missing_footer.fls"};

	static constexpr string_view TRUNCATED_HEADER {FLS_CMAKE_SOURCE_DIR
	                                               "/data/test/verify_fastlanes_file_tests/truncated_header.fls"};

	// Handy iterable for parameterised tests
	static constexpr test_dataset_t dataset = {{{"VALID_FLS", VALID_FLS},
	                                            {"BAD_HEADER_MAGIC", BAD_HEADER_MAGIC},
	                                            {"BAD_FOOTER_MAGIC", BAD_FOOTER_MAGIC},
	                                            {"BAD_VERSION", BAD_VERSION},
	                                            {"MISSING_FOOTER", MISSING_FOOTER},
	                                            {"TRUNCATED_HEADER", TRUNCATED_HEADER}}};
};

} // namespace fastlanes

#endif // DATA_TEST_HPP
