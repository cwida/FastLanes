add_library(fls_table
        OBJECT
        attribute.cpp
        chunk.cpp
        #[[]]
        column.cpp
        rowgroup.cpp
        stats.cpp
        table.cpp
        vector.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_table>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_table PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()