#######################################################################
# Usage in sub‑directories (example)
#######################################################################
#   target_link_libraries(example
#       PUBLIC
#           FastLanes::headers   # gets the include path
#           FastLanes::core      # links against the main library if needed
#   )
# --------------------------------------------------------------------
#######################################################################

#######################################################################
# 1. Public‑header interface target
#######################################################################
add_library(fls_headers INTERFACE)

target_include_directories(fls_headers
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(FastLanes::headers ALIAS fls_headers)

#######################################################################
# 2. Sub‑directories that build the individual components
#######################################################################

add_subdirectory(alp)
add_subdirectory(c_api)
add_subdirectory(cfg)
add_subdirectory(common)
add_subdirectory(cor)
add_subdirectory(csv)
add_subdirectory(detail)
add_subdirectory(encoder)
add_subdirectory(expression)
add_subdirectory(file)
add_subdirectory(filter)
add_subdirectory(flatbuffers)
add_subdirectory(footer)
add_subdirectory(io)
add_subdirectory(json)
add_subdirectory(logger)
add_subdirectory(primitive)
add_subdirectory(primitives)
add_subdirectory(printer)
add_subdirectory(reader)
add_subdirectory(std)
add_subdirectory(stt)
add_subdirectory(table)
add_subdirectory(utl)
add_subdirectory(wizard)

#######################################################################
# 3. Core FastLanes library
#######################################################################

add_library(FastLanes STATIC
        connection.cpp
        ${FASTLANES_OBJECT_FILES}
)

target_compile_features(FastLanes PUBLIC cxx_std_20)


target_link_libraries(FastLanes
        PUBLIC
        FastLanes::headers
)

add_library(FastLanes::core ALIAS FastLanes)

if (FLS_ENABLE_IWYU)
    set_property(TARGET FastLanes PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

#######################################################################
# 4. Installation
#######################################################################

install(
        TARGETS FastLanes fls_headers
        EXPORT FLSTargets           # add the two libs to the export set
        LIBRARY DESTINATION lib      # for shared libs (none in this snippet)
        ARCHIVE DESTINATION lib      # static libs (.a)
        RUNTIME DESTINATION bin      # executables, if any
)
