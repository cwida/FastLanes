add_subdirectory(scalar_aav_uf1)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_generated>
        PARENT_SCOPE)