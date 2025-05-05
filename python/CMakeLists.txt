find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

set(FLS_BINDING_SRC
        fastlanes_bindings.cpp
        connection.cpp
)

# 1) Build the extension as "_fastlanes"
pybind11_add_module(_fastlanes ${FLS_BINDING_SRC})
target_link_libraries(_fastlanes PRIVATE FastLanes)
target_compile_features(_fastlanes PRIVATE cxx_std_20)
set_target_properties(_fastlanes PROPERTIES
        OUTPUT_NAME "_fastlanes"  # => _fastlanes.*.so
        PREFIX ""                 # drop the lib- prefix
)

# 2) Install the extension into the fastlanes/ package
install(TARGETS _fastlanes
        RUNTIME DESTINATION fastlanes  # Windows .pyd
        LIBRARY DESTINATION fastlanes  # macOS/Linux .so
        ARCHIVE DESTINATION fastlanes   # for completeness
)

# 3) Copy the pure-Python files (your __init__.py) into the wheel
install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fastlanes
        DESTINATION .
        FILES_MATCHING PATTERN "*.py"
        PATTERN "__pycache__" EXCLUDE
)


set_target_properties(_fastlanes PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/python/fastlanes
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/python/fastlanes
)