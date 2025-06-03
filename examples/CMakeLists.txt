# C++ Example : --------------------------------------------------------------------------------------------------------
add_executable(cpp_example ${CMAKE_CURRENT_SOURCE_DIR}/cpp_example.cpp)
target_link_libraries(cpp_example PUBLIC FastLanes)

if (WIN32 AND FLS_BUILD_SHARED_LIBS)
    add_custom_command(
            TARGET cpp_example
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            -E copy_if_different
            $<TARGET_RUNTIME_DLLS:cpp_example>
            $<TARGET_FILE_DIR:cpp_example>
    )
endif ()