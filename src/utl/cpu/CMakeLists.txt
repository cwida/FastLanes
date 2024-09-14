add_library(cpu
        OBJECT
        ftr.cpp
        arch.cpp
        info.cpp)
if (ENABLE_IWYU)
    set_target_properties(cpu PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:cpu>
        PARENT_SCOPE)