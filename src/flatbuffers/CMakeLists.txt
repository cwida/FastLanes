add_library(fls_flatbuffers
        OBJECT
        #[[]]
        flatbuffers.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_flatbuffers PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_flatbuffers>
        PARENT_SCOPE)