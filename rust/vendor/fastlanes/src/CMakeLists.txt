#######################################################################
# 1. Public‑header interface target
#######################################################################
# Anything that needs to include <fastlanes.h> or other public headers
# simply links to this target (no actual link flags are added, only
# the include path)
add_library(fls_headers INTERFACE)

# Build tree                     → FastLanes/include
# When installed with CMake      → <install‑prefix>/include
# The install path is picked up automatically by `install(EXPORT …)`.
# --------------------------------------------------------------------
# IMPORTANT: we declare this *before* we descend into the sub‑directories
# so that every target created later can already link against it.
# --------------------------------------------------------------------

# NOTE: `${CMAKE_CURRENT_SOURCE_DIR}` here is …/src
# so the public headers are expected in …/include next to the src folder.
# Adjust the path if your layout is different.

target_include_directories(fls_headers
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
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


# Public usage requirements
# ‑ Anyone linking to FastLanes gets include path *and* dependent libs
# ‑ We link the header interface so *this* target can see its own headers
# ‑ Add your other internal/external dependencies here (primitives, ALP …)

target_link_libraries(FastLanes
        PUBLIC
        FastLanes::headers   # <fastlanes.h> etc.
)

add_library(FastLanes::core ALIAS FastLanes)

# Optional Include‑What‑You‑Use support --------------------------------------------------------------
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

#######################################################################
# 5. Usage in sub‑directories (example)
#######################################################################
# ---- src/c_api/CMakeLists.txt ----
#   add_library(fls_c_api STATIC c_api_connector.cpp)
#   target_link_libraries(fls_c_api
#       PUBLIC
#           FastLanes::headers   # gets the include path
#           FastLanes::core      # links against the main library if needed
#   )
# --------------------------------------------------------------------
# Repeat the same pattern for other component libraries/executables.
#######################################################################
