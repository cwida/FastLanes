add_executable(test_frequency test_frequency.cpp)
target_link_libraries(test_frequency PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_frequency COMMAND $<TARGET_FILE:test_frequency>)

add_executable(test_rle test_rle.cpp)
target_link_libraries(test_rle PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_rle COMMAND $<TARGET_FILE:test_rle>)

add_executable(test_cross_rle test_cross_rle.cpp)
target_link_libraries(test_cross_rle PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_cross_rle COMMAND $<TARGET_FILE:test_cross_rle>)


add_executable(test_alp test_alp.cpp)
target_link_libraries(test_alp PUBLIC gtest_main gmock_main FastLanes)
add_test(NAME test_alp COMMAND $<TARGET_FILE:test_alp>)

# Add sanitizer options if needed
foreach (test_target IN ITEMS test_frequency test_rle test_cross_rle test_alp)
    target_compile_options(${test_target} PRIVATE "-fsanitize=address" "-fsanitize=undefined")
    target_link_options(${test_target} PRIVATE "-fsanitize=address" "-fsanitize=undefined")
endforeach ()
