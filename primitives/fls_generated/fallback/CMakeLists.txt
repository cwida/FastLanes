add_subdirectory(scalar_aav_uf1)

set(FLS_GENERATED_OBJECT_FILES
        ${FLS_GENERATED_OBJECT_FILES} $<TARGET_OBJECTS:fls_generated>
        PARENT_SCOPE)