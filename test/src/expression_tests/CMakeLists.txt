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

add_executable(test_fsst_expr fsst_test.cpp)
target_link_libraries(test_fsst_expr PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_fsst_expr COMMAND $<TARGET_FILE:test_fsst_expr>)

add_executable(test_uncompressed uncompressed_test.cpp)
target_link_libraries(test_uncompressed PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_uncompressed COMMAND $<TARGET_FILE:test_uncompressed>)

fls_enable_sanitizers(test_frequency)
fls_enable_sanitizers(test_rle)
fls_enable_sanitizers(test_cross_rle)
fls_enable_sanitizers(test_alp)
fls_enable_sanitizers(test_fsst_expr)
fls_enable_sanitizers(test_uncompressed)
