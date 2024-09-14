add_library(ffor
        OBJECT
        ffor_exp.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:ffor>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET ffor PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()