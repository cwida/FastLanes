add_executable(unit_test
        csv_reader_test.cpp
        double_test.cpp
        json_test.cpp
        decimal_test.cpp
        sampling_layout_test.cpp
)

target_link_libraries(unit_test
        PRIVATE
        gtest_main     # GoogleTest’s main first
        FastLanes      # your library second
)

fls_enable_sanitizers(unit_test)

gtest_discover_tests(            # single call with extended timeout
        unit_test
        DISCOVERY_TIMEOUT 120        # seconds
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
