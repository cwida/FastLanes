add_executable(unit_test
        csv_reader_test.cpp
        double_test.cpp
        json_test.cpp
        decimal_test.cpp
        parse_integer_test.cpp
        parse_timestamp_test.cpp
        parse_timestamp_12hour_test.cpp
        parse_timestamp_with_offset_test.cpp
        parse_timestamp_zulu_test.cpp
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
