add_executable(
        tests
        clickbench_test.cpp
        #[[]]
        csv_reader_test.cpp
        issue_test.cpp
        main.cpp
        nextiajd_test.cpp
        public_bi_test.cpp
#        realnest_read_test.cpp
        tester.cpp)

target_link_libraries(tests PUBLIC gtest_main gmock_main fastlanes)
gtest_discover_tests(tests)

#target_compile_options(tests
#        PRIVATE
#        "-fsanitize=address"
#        "-fsanitize=undefined"
#        "-fsanitize=leak")
#
#target_link_options(tests
#        PRIVATE
#        "-fsanitize=address"
#        "-fsanitize=undefined"
#        "-fsanitize=leak")


