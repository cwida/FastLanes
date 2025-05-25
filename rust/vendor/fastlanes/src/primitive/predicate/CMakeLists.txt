add_library(fls_primitive_predicate
        OBJECT
        equal.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive_predicate>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_primitive_predicate PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_link_libraries(fls_primitive_predicate
        PUBLIC
        FastLanes::headers
)