add_library(fls_types
        OBJECT
        bool.cpp
        #[[]]
        date.cpp
        integer.cpp
        timestamp.cpp
        validitymask.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_types>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_stt PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_link_libraries(fls_types
        PUBLIC
        FastLanes::headers
)
