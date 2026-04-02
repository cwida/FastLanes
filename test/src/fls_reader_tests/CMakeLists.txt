add_executable(
        fls_reader_tests
        #[[]]
        incomplete_vectors_test.cpp
        inlined_footer_test.cpp
        rowgroup_size_test.cpp
        verify_fastlanes_files_test.cpp)

target_link_libraries(fls_reader_tests PUBLIC gtest_main gmock_main FastLanes msvc_heap_guard)
if (MSVC)
    target_link_options(fls_reader_tests PRIVATE /WHOLEARCHIVE:FastLanes.lib)
endif ()
gtest_discover_tests(fls_reader_tests DISCOVERY_TIMEOUT 60)

fls_enable_sanitizers(fls_reader_tests)


