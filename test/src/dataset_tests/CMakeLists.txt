add_executable(
        dataset_tests
        #
        embedding.cpp
        generated_data.cpp
        issues.cpp
        nextiajd_test.cpp
        public_bi.cpp
        test_fc_bench.cpp
        tpch.cpp
        wrong_schema.cpp)

target_link_libraries(dataset_tests PUBLIC gtest_main gmock_main FastLanes)
gtest_discover_tests(dataset_tests DISCOVERY_TIMEOUT 60)
fls_enable_sanitizers(dataset_tests)

