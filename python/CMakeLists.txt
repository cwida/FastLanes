# 1) Enable pybind11's modern Python finder (auto-locates headers & libpython)
set(PYBIND11_FINDPYTHON ON)

# 2) Locate pybind11 (system first, else fetch from GitHub)
find_package(pybind11 CONFIG QUIET)
if (NOT TARGET pybind11::pybind11)
    include(FetchContent)
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG        v2.13.6
    )
    FetchContent_MakeAvailable(pybind11)
endif()

# 3) Build the extension module
set(FLS_BINDING_SRC
        bindings/init_binding.cpp
        bindings/connection_binding.cpp
        bindings/table_reader_binding.cpp
)

pybind11_add_module(_fastlanes ${FLS_BINDING_SRC})
target_link_libraries(_fastlanes PRIVATE FastLanes)
target_compile_features(_fastlanes PRIVATE cxx_std_20)
set_target_properties(_fastlanes PROPERTIES
        OUTPUT_NAME "_fastlanes"
        PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/pyfastlanes
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/pyfastlanes
)

# 4) Install rules for the wheel
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

# 5) Python tests – just invoke pytest via the discovered interpreter
enable_testing()
add_test(
        NAME PythonTests
        COMMAND ${Python3_EXECUTABLE} -m pytest -q
        ${PROJECT_SOURCE_DIR}/pytest_tests
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)