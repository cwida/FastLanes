add_subdirectory(unit_test)
add_subdirectory(expression_test)

add_executable(
        tests
        #        clickbench_test.cpp
        #[[]]
        csv_reader_test.cpp
        #        issue_test.cpp
        #        main.cpp
        #        nextiajd_test.cpp
        #        public_bi_test.cpp
        #        realnest_read_test.cpp
        #        tester.cpp
        test_datasets/wrong_schema.cpp
        test_datasets/generated_data.cpp
        test_datasets/test_fc_bench.cpp
        test_datasets/issue.cpp
        test_datasets/public_bi.cpp)

target_link_libraries(tests PUBLIC gtest_main gmock_main FastLanes)
gtest_discover_tests(tests DISCOVERY_TIMEOUT 60)

target_compile_options(tests
        PRIVATE
        "-fsanitize=address"
        "-fsanitize=undefined")

target_link_options(tests
        PRIVATE
        "-fsanitize=address"
        "-fsanitize=undefined")


