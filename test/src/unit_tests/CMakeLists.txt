add_executable(
        unit_test
        csv_reader_test.cpp
        double_test.cpp
        decimal_test.cpp
        sampling_layout_test.cpp)

target_link_libraries(unit_test PUBLIC gtest_main gmock_main FastLanes)
gtest_discover_tests(unit_test)

fls_enable_sanitizers(unit_test)


