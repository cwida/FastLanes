add_subdirectory(fls_generated)
add_subdirectory(fls)

add_library(primitives
        STATIC
        primitives.cpp
        ${FLS_GENERATED_OBJECT_FILES})

