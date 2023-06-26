add_library(
   arm64v8_scalar_av_1024_uf1_rut OBJECT
   arm64v8_scalar_av_1024_uf1_rut_src.cpp)

target_compile_definitions(arm64v8_scalar_av_1024_uf1_rut PRIVATE IS_SCALAR)
set(FLAG -Rpass-analysis=loop-vectorize)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(arm64v8_scalar_av_1024_uf1_rut PUBLIC ${FLAG})
cmake_print_properties(
   TARGETS arm64v8_scalar_av_1024_uf1_rut
   PROPERTIES COMPILE_DEFINITIONS
   PROPERTIES COMPILE_OPTIONS
)
set(ARCH_OBJECT_FILES
           ${ARCH_OBJECT_FILES}
           $<TARGET_OBJECTS:arm64v8_scalar_av_1024_uf1_rut> PARENT_SCOPE)

get_target_property(TARGET_NAME arm64v8_scalar_av_1024_uf1_rut NAME)
get_target_property(TARGET_COMPILE_OPTIONS arm64v8_scalar_av_1024_uf1_rut COMPILE_OPTIONS)
add_executable(arm64v8_scalar_av_1024_uf1_rut_test arm64v8_scalar_av_1024_uf1_rut_test.cpp)
target_link_libraries(arm64v8_scalar_av_1024_uf1_rut_test PRIVATE arm64v8_scalar_av_1024_uf1_rut)
target_link_libraries(arm64v8_scalar_av_1024_uf1_rut_test PRIVATE bitpack)
target_link_libraries(arm64v8_scalar_av_1024_uf1_rut_test
       PRIVATE catch2
       )
target_include_directories(arm64v8_scalar_av_1024_uf1_rut_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_SOURCE_DIR}/benchmark/include/benchmark.hpp ${CMAKE_CURRENT_BINARY_DIR}/benchmark.hpp)

add_executable(arm64v8_scalar_av_1024_uf1_rut_bench arm64v8_scalar_av_1024_uf1_rut_bench.cpp)
target_link_libraries(arm64v8_scalar_av_1024_uf1_rut_bench PRIVATE arm64v8_scalar_av_1024_uf1_rut)
target_link_libraries(arm64v8_scalar_av_1024_uf1_rut_bench PRIVATE bitpack)
target_include_directories(arm64v8_scalar_av_1024_uf1_rut_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

