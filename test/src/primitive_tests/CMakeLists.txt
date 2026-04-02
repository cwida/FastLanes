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

fls_enable_sanitizers(primitive_test)

gtest_discover_tests(            # single call with extended timeout
        primitive_test
        DISCOVERY_TIMEOUT 120        # seconds
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
