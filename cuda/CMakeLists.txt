cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(cuda_info LANGUAGES CXX CUDA)

# --- CUDA compiler info via CMake ---
message(STATUS "CMAKE_CUDA_COMPILER:         ${CMAKE_CUDA_COMPILER}")
message(STATUS "CMAKE_CUDA_COMPILER_ID:      ${CMAKE_CUDA_COMPILER_ID}")
message(STATUS "CMAKE_CUDA_COMPILER_VERSION: ${CMAKE_CUDA_COMPILER_VERSION}")
message(STATUS "CMAKE_CUDA_STANDARD:         ${CMAKE_CUDA_STANDARD}")
message(STATUS "CMAKE_CUDA_ARCHITECTURES:    ${CMAKE_CUDA_ARCHITECTURES}")

# --- Find the CUDA toolkit (modern CMake) ---
find_package(CUDAToolkit REQUIRED)
message(STATUS "CUDAToolkit version:       ${CUDAToolkit_VERSION}")
message(STATUS "CUDAToolkit include dirs:  ${CUDAToolkit_INCLUDE_DIRS}")
message(STATUS "CUDAToolkit libraries:     ${CUDAToolkit_LIBRARIES}")

# --- Locate nvcc and dump version ---
find_program(NVCC_EXECUTABLE nvcc REQUIRED)
message(STATUS "nvcc executable:           ${NVCC_EXECUTABLE}")
execute_process(
        COMMAND "${NVCC_EXECUTABLE}" --version
        OUTPUT_VARIABLE _nvcc_version
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "nvcc --version output:\n${_nvcc_version}")

# --- Echo common CUDA-related env vars ---
foreach (_env_var CUDA_PATH CUDA_HOME CUDA_TOOLKIT_ROOT_DIR)
    if (DEFINED ENV{${_env_var}})
        message(STATUS "${_env_var}: $ENV{${_env_var}}")
    endif ()
endforeach ()

# --- Point at your subdirectory source file ---
add_executable(cuda_info_dummy
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cuda_reader.cu
)

# --- Link against CUDA runtime ---
target_link_libraries(cuda_info_dummy PRIVATE CUDA::cudart)
set_target_properties(cuda_info_dummy PROPERTIES
        CUDA_STANDARD 11
        CUDA_STANDARD_REQUIRED YES
)
