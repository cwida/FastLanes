add_library(page
        OBJECT
        page.cpp
        page_hdr.cpp
        page_param.cpp
        entry_point.cpp
        type.cpp
        offset.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:page>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET page PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
