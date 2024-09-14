add_library(fls_io
        OBJECT
        #[[]]
        external_memory.cpp
        file.cpp
        io.cpp
        mmap.cpp
        s3.cpp
        socket.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_io>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_io PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()