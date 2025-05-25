add_subdirectory(fls_generated)
add_subdirectory(fls)

add_library(fls_primitives
        OBJECT
        #[[]]
        primitives.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitives>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_primitives PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_link_libraries(fls_primitives
        PUBLIC
        FastLanes::headers
)