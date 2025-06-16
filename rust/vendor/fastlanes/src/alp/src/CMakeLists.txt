add_library(fls_alp_primitive
        STATIC
        encoder.cpp
        falp.cpp
        fastlanes_ffor.cpp
        fastlanes_generated_unffor.cpp
        fastlanes_generated_ffor.cpp
        fastlanes_unffor.cpp
)


set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_alp_primitive>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_alp_primitive PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()


target_link_libraries(fls_alp_primitive
        PUBLIC
        FastLanes::headers
)

if (fls_alp_primitive_ENABLE_VERBOSE_OUTPUT)
    cmake_print_properties(TARGETS fls_alp_primitive PROPERTIES COMPILE_DEFINITIONS PROPERTIES COMPILE_OPTIONS)
endif ()


