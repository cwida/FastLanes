#ifndef FLS_TESTER_HPP
#define FLS_TESTER_HPP

#include "data/fastlanes_data.hpp"
#include "fastlanes.hpp"
#include "fls/connection.hpp"
#include "gtest/gtest.h"
#include <fls/table/dir.hpp>
#if defined(_WIN32)
#include <process.h> // for _getpid()
#define getpid _getpid
#else
#include <unistd.h> // for getpid()
#endif

namespace fastlanes {
class FastLanesReaderTester : public ::testing::Test {
	const path fastlanes_repo_data_path {FLS_CMAKE_SOURCE_DIR};
	const path fls_dir_path = fastlanes_repo_data_path / "data" / "fls";
	path       fls_file_path_process_specific;
	path       fls_dir_path_process_specific;

	void SetUp() override {
		fls_dir_path_process_specific  = fls_dir_path / std::to_string(getpid());
		fls_file_path_process_specific = fls_dir_path_process_specific / "data.fls";
		if (!exists(fls_dir_path_process_specific)) {
			create_directories(fls_dir_path_process_specific);
		}
	};

	void TearDown() override {
		if (exists(fls_dir_path_process_specific)) {
			remove_all(fls_dir_path_process_specific);
		}
	}

public:
	template <FileT DATA_TYPE = FileT::CSV>
	void TestCorrectness(const string_view            table,
	                     const vector<OperatorToken>& expressions    = {},
	                     const n_t                    rowgroup_size  = CFG::RowGroup::N_VECTORS_PER_ROWGROUP,
	                     bool                         inlined_footer = false) const {

		const path dir_path = fastlanes_repo_data_path / string(table);
		// original rowgroup
		Connection con1;

		con1.reset().set_n_vectors_per_rowgroup(rowgroup_size);
		if (inlined_footer) {
			con1.inline_footer();
		}

		if (!expressions.empty()) {
			con1.force_schema_pool(expressions);
		}

		if constexpr (DATA_TYPE == FileT::CSV) {
			con1.read_csv(dir_path);
		} else {
			con1.read_json(dir_path);
		}

		const auto& original_table = con1.get_table();

		// to_fls
		con1.to_fls(fls_file_path_process_specific);

		// decoded rowgroup
		Connection con2;
		auto       fls_reader    = con2.reset().read_fls(fls_file_path_process_specific);
		auto       decoded_table = fls_reader->materialize();
		// Compare rowgroups
		auto result = (original_table == *decoded_table);
		ASSERT_TRUE(result.is_equal) << "Rowgroups differs. The first not matching column index is: " //
		                             << result.first_failed_column_idx                                //
		                             << " ❌"                                                          //
		                             << "description: "                                               //
		                             << result.description << std::endl;
	}

	void TestConstantness(const vector<n_t>& constant_indexes) const {
		Connection  con;
		const auto  fls_reader            = con.reset().read_fls(fls_file_path_process_specific);
		auto        first_rowgroup_reader = fls_reader->get_rowgroup_reader(0);
		const auto& footer                = first_rowgroup_reader->get_descriptor();

		for (const auto col_idx : constant_indexes) {
			//
			auto& col_descriptor = footer.m_column_descriptors[col_idx];
			ASSERT_EQ(col_descriptor->total_size, 0) << col_idx << " should be constant";
		}
	}

	void TestEquality(const string_view table) const {
		TestCorrectness(table);

		// decoded rowgroup
		Connection con2;
		const auto fls_reader            = con2.reset().read_fls(fls_file_path_process_specific);
		auto       first_rowgroup_reader = fls_reader->get_rowgroup_reader(0);
		const auto footer                = first_rowgroup_reader->get_descriptor();

		for (n_t col_idx = 1; col_idx < footer.m_column_descriptors.size(); ++col_idx) {
			ASSERT_EQ(footer.m_column_descriptors[col_idx]->total_size, 0) << col_idx << " should be of size 0";
		}
	}

	void TestEquality(const vector<n_t>& equal_cols) const {
		Connection con;
		const auto fls_reader            = con.reset().read_fls(fls_file_path_process_specific);
		auto       first_rowgroup_reader = fls_reader->get_rowgroup_reader(0);
		const auto footer                = first_rowgroup_reader->get_descriptor();

		for (const auto col_index : equal_cols) {
			auto& col_descriptor = footer.m_column_descriptors[col_index];
			ASSERT_EQ(col_descriptor->total_size, 0) << "size of column " << col_index << ":" << col_descriptor->name
			                                         << " should be 0, as it is equal to another col.";
		}
	}

	void TestMap1To1(const vector<n_t>& target_column_indexes) const {
		Connection con;
		const auto fls_reader            = con.reset().read_fls(fls_file_path_process_specific);
		auto       first_rowgroup_reader = fls_reader->get_rowgroup_reader(0);
		const auto footer                = first_rowgroup_reader->get_descriptor();

		for (const auto col_index : target_column_indexes) {
			auto& col_descriptor = footer.m_column_descriptors[col_index];
			ASSERT_TRUE(is_1_to_1(col_descriptor->encoding_rpn->operator_tokens[0])) << "  " << col_index;
		}
	}

	void AllTest(const string_view  table,
	             const vector<n_t>& constant_indexes,
	             const vector<n_t>& equal_cols,
	             const vector<n_t>& target_column_indexes) const {
		//
		TestCorrectness(table);
		TestConstantness(constant_indexes);
		TestMap1To1(target_column_indexes);
		TestEquality(equal_cols);
	}

	static Status VerifyFastLanesFile(const path& fls_file_path) {
		Connection con;
		return con.verify_fls(fls_file_path);
	}
};
} // namespace fastlanes

#endif // FLS_TESTER_HPP
