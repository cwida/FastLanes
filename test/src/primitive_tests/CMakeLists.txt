add_executable(primitive_test
        fsst_test.cpp
        patch_test.cpp
)

target_link_libraries(primitive_test
        PRIVATE
        gtest_main     # GoogleTest’s main first
        FastLanes      # your library second
        msvc_heap_guard
)
fls_msvc_test_setup(primitive_test)

fls_enable_sanitizers(primitive_test)

gtest_discover_tests(            # single call with extended timeout
        primitive_test
        DISCOVERY_MODE PRE_TEST      # enumerate at ctest time, not as a post-link build step
        DISCOVERY_TIMEOUT 600        # seconds; sanitized Debug binaries start slowly on CI runners
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
