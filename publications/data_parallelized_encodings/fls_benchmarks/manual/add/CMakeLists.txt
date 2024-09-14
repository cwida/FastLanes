add_library(add OBJECT
            add_src.cpp)
target_compile_definitions(add PRIVATE IS_SCALAR)
set(FLAG -mavx512bw -fno-builtin)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
	message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(add PUBLIC ${FLAG})
cmake_print_properties(TARGETS add
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST(APPEND FLS_GENERATED_OBJECT_FILES
     $<TARGET_OBJECTS:add>)
get_target_property(TARGET_NAME add NAME)
get_target_property(TARGET_COMPILE_OPTIONS add COMPILE_OPTIONS)
#-----------------------------------------------------------------------------------------------------------------------
add_executable(add_test add_test.cpp)
target_link_libraries(add_test PRIVATE add)
target_link_libraries(add_test PRIVATE gtest_main)
target_include_directories(add_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(add_test)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/add_bench.hpp)
add_executable(add_bench add_bench.cpp)
target_link_libraries(add_bench PRIVATE add)
target_include_directories(add_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(add_bench PUBLIC -mavx512bw)
#add_fls_benchmark(add_bench)