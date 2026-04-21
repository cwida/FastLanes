# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# cmake/enable_sanitizer.cmake
# ────────────────────────────────────────────────────────
# --- cmake/enable_sanitizer.cmake ---
#
# Defines fls_enable_sanitizers(<target>) to apply
# AddressSanitizer, UBSan, and related checks on all builds
# *except* fully‐static macOS executables, which are unsupported,
# and on Win32 where Clang’s sanitizers aren’t reliably supported.
#
# RATIONALE:
#   • ASan on Apple platforms is provided only as a dynamic
#     runtime (libclang_rt.asan_osx_dynamic.dylib).
#   • Clang docs state: “Static linking of executables is
#     not supported.”
#   • On macOS-14 (Sonoma) & macOS-15 (Ventura), a truly
#     static binary with -fsanitize=address will abort at
#     startup (you see the shadow-byte legend then “ABORTING”).
#   • Linux “static” builds still load the dynamic libasan,
#     so only macOS static+ASan fails.
#   • On **Win32**, neither MSVC nor Clang-on-Windows reliably
#     supports the standard `-fsanitize=` flags by default:
#       – MSVC uses a different sanitization framework
#         (AddressSanitizer on Windows is still experimental).
#       – ODR-use of sanitizers can break the CRT linkage.
#     Disabling on Win32 avoids build errors and linkage issues.
#
# IMPACT ON CI:
#   OS         | Shared        | Static
#   -----------------------------------------
#   Ubuntu     | ✅ ASan       | ✅ ASan
#   macOS-14   | ✅ ASan       | ❌ Abort at startup
#   macOS-15   | ✅ ASan       | ❌ Abort at startup
#   Windows    | 🚫 Sanitizers | 🚫 Sanitizers
#

function(fls_enable_sanitizers target)
    # 1) Skip on static macOS
    if (APPLE AND NOT FLS_BUILD_SHARED_LIBS)
        message(STATUS
                "[Sanitizers] Skipping sanitizers for '${target}' "
                "(static build on macOS is unsupported by ASan)")
        return()
    endif ()

    # 2) Skip on Win32 due to lack of reliable -fsanitize support
    if (WIN32)
        message(STATUS
                "[Sanitizers] Skipping sanitizers for '${target}' "
                "(sanitizer flags not supported on Win32 toolchains)")
        return()
    endif ()

    # 3) Apply on all other platforms
    set(_san_flags
            -fsanitize=address
            -fsanitize=undefined
            -fsanitize=vptr
            -fsanitize=null
            -fno-sanitize-recover=all
            -fno-omit-frame-pointer
    )
    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        list(APPEND _san_flags -fsanitize=function)
    endif ()

    string(REPLACE ";" " " _san_flags_str "${_san_flags}")
    message(STATUS
            "[Sanitizers] Enabling sanitizers for '${target}': ${_san_flags_str}")

    target_compile_options(${target} PRIVATE ${_san_flags})
    target_link_options(${target} PRIVATE ${_san_flags})
endfunction()
