add_executable(test_frequency frequency_test.cpp)
target_link_libraries(test_frequency PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_frequency COMMAND $<TARGET_FILE:test_frequency>)

add_executable(test_rle rle_test.cpp)
target_link_libraries(test_rle PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_rle COMMAND $<TARGET_FILE:test_rle>)

add_executable(test_cross_rle cross_rle_test.cpp)
target_link_libraries(test_cross_rle PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_cross_rle COMMAND $<TARGET_FILE:test_cross_rle>)

add_executable(test_alp alp_test.cpp)
target_link_libraries(test_alp PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_alp COMMAND $<TARGET_FILE:test_alp>)

fls_enable_sanitizers(test_frequency)
fls_enable_sanitizers(test_rle)
fls_enable_sanitizers(test_cross_rle)
fls_enable_sanitizers(test_alp)
