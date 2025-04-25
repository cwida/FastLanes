# C++ Example : --------------------------------------------------------------------------------------------------------
add_executable(cpp_example ${CMAKE_CURRENT_SOURCE_DIR}/cpp_example.cpp)
target_link_libraries(cpp_example PUBLIC FastLanes)

target_compile_options(cpp_example PRIVATE "-fsanitize=address,undefined")
target_link_options(cpp_example PRIVATE "-fsanitize=address,undefined")

# C Example : ----------------------------------------------------------------------------------------------------------
#add_executable(c_api ${CMAKE_CURRENT_SOURCE_DIR}/c_api.c)
#target_link_libraries(c_api PUBLIC FastLanes)
#
#target_compile_options(c_api PRIVATE "-fsanitize=address,undefined")
#target_link_options(c_api PRIVATE "-fsanitize=address,undefined")
