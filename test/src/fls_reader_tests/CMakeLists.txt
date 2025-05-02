add_executable(
        fls_reader_tests
        #[[]]
        inlined_footer_test.cpp
        rowgroup_size_test.cpp
        verify_fastlanes_files_test.cpp)

target_link_libraries(fls_reader_tests PUBLIC gtest_main gmock_main FastLanes)
gtest_discover_tests(fls_reader_tests DISCOVERY_TIMEOUT 60)

target_compile_options(fls_reader_tests
        PRIVATE
        "-fsanitize=address"
        "-fsanitize=undefined")

target_link_options(fls_reader_tests
        PRIVATE
        "-fsanitize=address"
        "-fsanitize=undefined")


