add_executable(
        dataset_tests
        wrong_schema.cpp
        generated_data.cpp
        test_fc_bench.cpp
        issue.cpp
        issues.cpp
        public_bi.cpp)

target_link_libraries(dataset_tests PUBLIC gtest_main gmock_main FastLanes)
gtest_discover_tests(dataset_tests DISCOVERY_TIMEOUT 60)
fls_enable_sanitizers(dataset_tests)

