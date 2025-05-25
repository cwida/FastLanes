cmake_minimum_required(VERSION 3.14)
project(fetch_content_example LANGUAGES CXX)

if (NOT DEFINED FASTLANES_TAG)
    message(FATAL_ERROR "You must define FASTLANES_TAG")
endif ()

include(FetchContent)
FetchContent_Declare(
        fastlanes
        GIT_REPOSITORY https://github.com/azimafroozeh/FastLanes.git
        GIT_TAG ${FASTLANES_TAG}
)
FetchContent_MakeAvailable(fastlanes)


add_compile_definitions(EXAMPLE_CMAKE_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(example example.cpp)
target_link_libraries(example PRIVATE FastLanes)
