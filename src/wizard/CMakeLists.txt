add_library(fls_wizard
        OBJECT
        #[[]]
        sampling_layout.cpp
        wizard.cpp)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_wizard PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_wizard>
        PARENT_SCOPE)