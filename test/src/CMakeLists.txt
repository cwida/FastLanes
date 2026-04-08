# On MSVC (and clang-cl), large heap allocations can touch guard pages whose
# transient 0xc0000005 exceptions are caught by GoogleTest's SEH wrapper,
# causing spurious test failures.  This small static library installs a VEH
# handler that commits those pages before GTest intercepts the fault.
# On non-MSVC toolchains the source compiles to an empty translation unit.
add_library(msvc_heap_guard OBJECT msvc_heap_guard.cpp)

# Helper: apply MSVC-specific linker/runtime settings to a test target.
#  - Static builds:  /WHOLEARCHIVE so all symbols are pulled in.
#  - Shared builds:  copy the DLL next to the test executable.
function(fls_msvc_test_setup TARGET)
    if (NOT MSVC)
        return()
    endif ()
    if (NOT FLS_BUILD_SHARED_LIBS)
        target_link_options(${TARGET} PRIVATE /WHOLEARCHIVE:$<TARGET_FILE:FastLanes>)
    else ()
        add_custom_command(
                TARGET ${TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${TARGET}>
                $<TARGET_FILE_DIR:${TARGET}>
                COMMAND_EXPAND_LISTS
        )
    endif ()
endfunction()

add_subdirectory(dataset_tests)
add_subdirectory(expression_tests)
add_subdirectory(fls_reader_tests)
add_subdirectory(primitive_tests)
add_subdirectory(quick_fuzz_tests)
add_subdirectory(unit_tests)

