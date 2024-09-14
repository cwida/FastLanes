# Describe property
define_property(GLOBAL PROPERTY FLS_ALL_BENCHMARK_TARGETS
        BRIEF_DOCS "Global list of elements"
        FULL_DOCS "Global list of elements")
# Initialize property
set_property(GLOBAL PROPERTY FLS_ALL_BENCHMARK_TARGETS "")

# Macro for add values into the list
macro(add_fls_benchmark var)
    set_property(GLOBAL APPEND PROPERTY FLS_ALL_BENCHMARK_TARGETS "${var}")
endmacro(add_fls_benchmark)


add_compile_definitions(FLS_FALLBACK)
add_subdirectory(fallback)
#-----------------------------------------------------------------------------------------------------------------------
add_library(fls_generated
        OBJECT
        fls_generated.cpp)

set(FLS_GENERATED_OBJECT_FILES
        ${FLS_GENERATED_OBJECT_FILES} $<TARGET_OBJECTS:fls_generated>
        PARENT_SCOPE)
#-----------------------------------------------------------------------------------------------------------------------
cmake_print_properties(
        TARGETS fls_generated
        PROPERTIES COMPILE_DEFINITIONS
        PROPERTIES COMPILE_OPTIONS
        PROPERTIES COMPILE_FEATURES)
#-----------------------------------------------------------------------------------------------------------------------
get_property(BENCHMARK_LIST GLOBAL PROPERTY FLS_ALL_BENCHMARK_TARGETS)
message(STATUS "BENCHMARK LIST: ${BENCHMARK_LIST}")

foreach (i IN LISTS BENCHMARK_LIST)
    list(APPEND add_custom_target_args COMMAND $<TARGET_FILE:${i}>)
endforeach ()

add_custom_target(fls_benchmark_all
        ${add_custom_target_args}
)
