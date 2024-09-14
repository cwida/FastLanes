cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Compiler flags for the different targets
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-sign-compare -Wno-unused-result -Wno-unused-parameter")


project(jevents)

add_library(jevents
        json.c
        jsmn.c
        jevents.c
        resolve.c
        cache.c
        cpustr.c
        rawevent.c
        perf-iter.c
        interrupts.c
        rdpmc.c
        measure.c
        perf_event_open.c
        session.c
        )

target_include_directories(jevents PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:.>
        PRIVATE src)

add_executable(listevents listevents.c)
target_link_libraries(listevents jevents)