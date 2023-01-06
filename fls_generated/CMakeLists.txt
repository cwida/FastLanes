# Describe property
define_property(GLOBAL PROPERTY FLS_ALL_BENCHMARK_TARGETS
                BRIEF_DOCS "Global list of elements"
                FULL_DOCS "Global list of elements")
# Initialize property
set_property(GLOBAL PROPERTY FLS_ALL_BENCHMARK_TARGETS "")

# Macro for add values into the list
macro(add_fls_benchmark var)
	set_property(GLOBAL APPEND PROPERTY FLS_ALL_BENCHMARK_TARGETS "${var}")
endmacro(add_fls_benchmark)
#-----------------------------------------------------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11")
#-----------------------------------------------------------------------------------------------------------------------
add_library(test_bench_helper OBJECT
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_rsum_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_unrsum_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_ffor_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_unffor_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_pack_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_unpack_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_transpose_src.cpp
            helper/scalar_av_uf1/helper_scalar_av_1024_uf1_untranspose_src.cpp)

target_compile_definitions(test_bench_helper PRIVATE IS_SCALAR)
target_compile_options(test_bench_helper PRIVATE "")
#-----------------------------------------------------------------------------------------------------------------------
# always add fallback implementations. not important for benchmarking
add_compile_definitions(FLS_FALLBACK)
add_subdirectory(fallback)
#-----------------------------------------------------------------------------------------------------------------------
if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	add_subdirectory(wasm)
else()
	if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64" OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
		add_subdirectory(arm64v8)
		add_compile_definitions(FLS_ARM64V8)
	elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
		add_subdirectory(x86_64)
		add_compile_definitions(FLS_X86_64)
	else()
	endif()
endif()
#-----------------------------------------------------------------------------------------------------------------------
#add_library(fls_generated SHARED
#            ${FLS_GENERATED_OBJECT_FILES}
#            fls_generated.cpp)
#-----------------------------------------------------------------------------------------------------------------------
cmake_print_properties(
		TARGETS fls_generated
		PROPERTIES COMPILE_DEFINITIONS
		PROPERTIES COMPILE_OPTIONS
		PROPERTIES COMPILE_FEATURES)
#-----------------------------------------------------------------------------------------------------------------------
get_property(BENCHMARK_LIST GLOBAL PROPERTY FLS_ALL_BENCHMARK_TARGETS)
message(STATUS "BENCHMARK LIST: ${BENCHMARK_LIST}")

foreach(i IN LISTS BENCHMARK_LIST)
	list(APPEND add_custom_target_args COMMAND $<TARGET_FILE:${i}>)
endforeach()

add_custom_target(fls_benchmark_all
                  ${add_custom_target_args}
                  )
