#include "test/tester.hpp"
#include "fastlanes.hpp"
#include "fls/table/dir.hpp"

namespace fastlanes {
void Tester::Test(const path& dir_path) {
	Connection con;
	const path fastlanes_data_path {CMAKE_SOURCE_DIR};
	const path full_dir_path = fastlanes_data_path / dir_path;
	con.read(full_dir_path).verify_encoding(); // NOLINT
}

void Tester::Test(const path& dir_path, idx_t col_id) {
	Connection con;
	const path fastlanes_data_path {CMAKE_SOURCE_DIR};
	const path full_dir_path = fastlanes_data_path / dir_path;
	con.read(full_dir_path).project({col_id}).verify_encoding(); // NOLINT
}

void Tester::RealNestTest(const string& table_name) {
	const path dir_path {"FastLanes_Data/RealNest/sample-data/100mib/" + table_name};

	Test(dir_path);
}
} // namespace fastlanes