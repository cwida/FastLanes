find_package(Python3 COMPONENTS Interpreter Development REQUIRED)


pybind11_add_module(fastlanes_python fastlanes_bindings.cpp
        connection.cpp)
target_link_libraries(fastlanes_python PRIVATE FastLanes)
target_compile_features(fastlanes_python PRIVATE cxx_std_20)    # or 17
# Strip visibility for small wheels
target_compile_definitions(fastlanes_python PRIVATE PYBIND11_DETAILED_ERROR_MESSAGES)

