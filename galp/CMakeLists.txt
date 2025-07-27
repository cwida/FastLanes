enable_language(CUDA)

# ────────────────────────────────────────────────
# 0. Global settings
# ────────────────────────────────────────────────
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --expt-relaxed-constexpr") #todo FIX ME

# ────────────────────────────────────────────────
# 1. CUDA Toolkit
# ────────────────────────────────────────────────
find_package(CUDAToolkit REQUIRED)

# ────────────────────────────────────────────────
# 2. nvCOMP (required)
# ────────────────────────────────────────────────
find_package(nvcomp CONFIG REQUIRED)

get_target_property(NVCOMP_VERSION nvcomp::nvcomp VERSION)
get_target_property(NVCOMP_INC_DIRS nvcomp::nvcomp INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(NVCOMP_LIBS nvcomp::nvcomp INTERFACE_LINK_LIBRARIES)

message(STATUS "nvCOMP version ..........: ${NVCOMP_VERSION}")
message(STATUS "nvCOMP include dirs .....: ${NVCOMP_INC_DIRS}")
message(STATUS "nvCOMP libs .............: ${NVCOMP_LIBS}")

# ────────────────────────────────────────────────
# 3. Thrust / CCCL – prefer toolkit copy, fall back to CCCL ≥ 2.3
# ────────────────────────────────────────────────
find_path(THRUST_INCLUDE_DIR
        NAMES thrust/version.h
        thrust/device_uvector.h
        HINTS ${CUDAToolkit_INCLUDE_DIRS})

if (NOT THRUST_INCLUDE_DIR)
    message(FATAL_ERROR "Need Thrust ≥ 2.2 (with device_uvector.h) in CUDA Toolkit")
endif ()

add_library(Thrust::Thrust INTERFACE IMPORTED)
target_include_directories(Thrust::Thrust INTERFACE ${THRUST_INCLUDE_DIR})

# ────────────────────────────────────────────────
# 4. User-tunable options & warnings
# ────────────────────────────────────────────────
option(USE_CLANG_FOR_HOST "Use clang++-14 for all .cpp files" ON)
option(GALP_VERBOSE_BUILD "Print every compile/link command" OFF)
if (GALP_VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif ()

set(COMMON_WARNINGS "")
set(CLANG_ONLY_WARNINGS
        -Wno-c++98-compat-local-type-template-args
        -Wno-c++98-compat-pedantic
        -Wno-c++98-compat
        -Wno-padded
        -Wno-float-equal
        -Wno-global-constructors
        -Wno-exit-time-destructors
        -Wno-float-conversion
        -Wno-sign-conversion
        -Wno-implicit-int-float-conversion
        -Wno-unused-parameter
        -Wno-unused-variable
)

macro(apply_warnings tgt)
    target_compile_options(${tgt} PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:${COMMON_WARNINGS}>
            $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Clang>>:${CLANG_ONLY_WARNINGS}>
            $<$<COMPILE_LANGUAGE:CUDA>:${COMMON_WARNINGS}>)
endmacro()

add_compile_definitions(FLS_GALP_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# ────────────────────────────────────────────────
# 5. GALP core static library
# ────────────────────────────────────────────────
add_subdirectory(src)

# ────────────────────────────────────────────────
# 8. tests
# ────────────────────────────────────────────────
add_subdirectory(test)

## ────────────────────────────────────────────────
## 7. Benchmarks
## ────────────────────────────────────────────────
add_subdirectory(benchmark)

