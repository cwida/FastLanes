add_executable(
        fls_reader_tests
        #[[]]
        incomplete_vectors_test.cpp
        inlined_footer_test.cpp
        rowgroup_size_test.cpp
        verify_fastlanes_files_test.cpp)

target_link_libraries(fls_reader_tests PUBLIC gtest_main gmock_main FastLanes msvc_heap_guard)
fls_msvc_test_setup(fls_reader_tests)
# PRE_TEST: enumerate tests when ctest runs rather than as a post-link build step;
# sanitized Debug binaries can take minutes just to start on CI runners.
gtest_discover_tests(fls_reader_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 600)

fls_enable_sanitizers(fls_reader_tests)


