#include "fls_tester.hpp"

namespace fastlanes {

/*───────────────────────────────────────────────────────────────*/
/* Good file – must pass                                         */
/*───────────────────────────────────────────────────────────────*/
TEST_F(FastLanesReaderTester, verify_valid_fastlanes_file) {
	auto result = VerifyFastLanesFile(test_dataset::VALID_FLS);
	ASSERT_TRUE(result.success);
}

/*───────────────────────────────────────────────────────────────*/
/* Bad header magic – must fail                                  */
/*───────────────────────────────────────────────────────────────*/
TEST_F(FastLanesReaderTester, verify_bad_header_magic_fastlanes_file) {
	auto result = VerifyFastLanesFile(test_dataset::BAD_HEADER_MAGIC);
	ASSERT_FALSE(result.success);
}

/*───────────────────────────────────────────────────────────────*/
/* Bad footer magic – must fail                                  */
/*───────────────────────────────────────────────────────────────*/
TEST_F(FastLanesReaderTester, verify_bad_footer_magic_fastlanes_file) {
	auto result = VerifyFastLanesFile(test_dataset::BAD_FOOTER_MAGIC);
	ASSERT_FALSE(result.success);
}

/*───────────────────────────────────────────────────────────────*/
/* Bad version tag – must fail                                   */
/*───────────────────────────────────────────────────────────────*/
TEST_F(FastLanesReaderTester, verify_bad_version_fastlanes_file) {
	auto result = VerifyFastLanesFile(test_dataset::BAD_VERSION);
	ASSERT_FALSE(result.success);
}

/*───────────────────────────────────────────────────────────────*/
/* Missing 8-byte footer – must fail                             */
/*───────────────────────────────────────────────────────────────*/
TEST_F(FastLanesReaderTester, verify_missing_footer_fastlanes_file) {
	auto result = VerifyFastLanesFile(test_dataset::MISSING_FOOTER);
	ASSERT_FALSE(result.success);
}

/*───────────────────────────────────────────────────────────────*/
/* Header truncated (<24 bytes) – must fail                      */
/*───────────────────────────────────────────────────────────────*/
TEST_F(FastLanesReaderTester, verify_truncated_header_fastlanes_file) {
	auto result = VerifyFastLanesFile(test_dataset::TRUNCATED_HEADER);
	ASSERT_FALSE(result.success);
}

} // namespace fastlanes
