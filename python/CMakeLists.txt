# ─────────────────────────────────────────────────────────────
# 1) macOS DWARF-in-binary: Embed debug info in the .so (no external dSYM)
# ─────────────────────────────────────────────────────────────
if (APPLE)
    # Force Xcode to keep DWARF in the binary
    set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf" CACHE STRING "" FORCE)
endif ()

# ─────────────────────────────────────────────────────────────
# 2) Binding Sources: Specify all C++ files for the pyfastlanes extension
# ─────────────────────────────────────────────────────────────
set(FLS_BINDING_SRC
        bindings/init_binding.cpp
        bindings/connection_binding.cpp
        bindings/table_reader_binding.cpp
)

# ─────────────────────────────────────────────────────────────
# 3) Extension Build: Locate pybind11 & declare the _fastlanes Python module
# ─────────────────────────────────────────────────────────────
find_package(pybind11 CONFIG QUIET)
if (NOT TARGET pybind11::pybind11)
    include(FetchContent)
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v2.13.6
    )
    FetchContent_MakeAvailable(pybind11)
endif ()

pybind11_add_module(_fastlanes ${FLS_BINDING_SRC})
target_link_libraries(_fastlanes PRIVATE FastLanes)
target_compile_features(_fastlanes PRIVATE cxx_std_20)

# ─────────────────────────────────────────────────────────────
# 4) Debug Config: Apply -gdwarf-4, -O0 & frame-pointer flags only in Debug mode
# ─────────────────────────────────────────────────────────────
target_compile_options(_fastlanes PRIVATE
        $<$<CONFIG:Debug>:-gdwarf-4 -O0 -fno-omit-frame-pointer>
)
target_link_options(_fastlanes PRIVATE
        $<$<CONFIG:Debug>:-gdwarf-4>
)

# ─────────────────────────────────────────────────────────────
# 5) Packaging Rules: Set output dirs and install targets for wheel creation
# ─────────────────────────────────────────────────────────────
set_target_properties(_fastlanes PROPERTIES
        OUTPUT_NAME "_fastlanes"
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/pyfastlanes
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/pyfastlanes
)

install(TARGETS _fastlanes
        RUNTIME DESTINATION pyfastlanes
        LIBRARY DESTINATION pyfastlanes
        ARCHIVE DESTINATION pyfastlanes
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pyfastlanes
        DESTINATION .
        FILES_MATCHING PATTERN "*.py"
        PATTERN "__pycache__" EXCLUDE
)

# ─────────────────────────────────────────────────────────────
# 6) Test Integration: Enable CTest to run pytest-based Python unit tests
# ─────────────────────────────────────────────────────────────
enable_testing()
add_test(
        NAME PythonTests
        COMMAND ${Python3_EXECUTABLE} -m pytest -q
        ${PROJECT_SOURCE_DIR}/python/tests
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
set_tests_properties(PythonTests
        PROPERTIES LABELS "python"
)
