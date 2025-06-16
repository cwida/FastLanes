add_library(dic
        OBJECT
        dic.cpp
        dic_fac.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:dic>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET dic PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
