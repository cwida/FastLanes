add_library(fls_json
        OBJECT
        #[[]]
        fls_json.cpp)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_json PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_json>
        PARENT_SCOPE)