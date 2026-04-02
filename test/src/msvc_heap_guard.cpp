// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/msvc_heap_guard.cpp
// ────────────────────────────────────────────────────────

// ---------------------------------------------------------------------------
// On Windows with the static CRT (/MT), large heap allocations (common when
// processing JPEG base64 data) may touch a heap-internal guard page, causing a
// transient STATUS_ACCESS_VIOLATION (0xc0000005).  Under normal circumstances
// the NT heap manager's own vectored-exception handler commits the page and
// resumes execution transparently.
//
// GoogleTest, however, wraps every TEST body in an SEH __try/__except frame.
// Because SEH frames are evaluated *after* VEH handlers have all returned
// EXCEPTION_CONTINUE_SEARCH, the heap manager never gets the chance to handle
// the fault — GoogleTest's catch-all __except(EXCEPTION_EXECUTE_HANDLER)
// intercepts it first and reports a spurious test failure.
//
// The workaround below installs a first-chance VEH handler that recognises
// the specific pattern (read-AV on a page-aligned address inside the process
// heap) and commits the faulting page itself, then resumes execution — exactly
// what the heap manager would have done if GoogleTest's SEH frame were absent.
// ---------------------------------------------------------------------------
#ifdef _MSC_VER
#include <windows.h>

static LONG WINAPI heap_guard_page_handler(EXCEPTION_POINTERS* ep) {
	if (ep->ExceptionRecord->ExceptionCode != EXCEPTION_ACCESS_VIOLATION) {
		return EXCEPTION_CONTINUE_SEARCH;
	}

	// Only handle *read* AVs (ExceptionInformation[0] == 0).
	if (ep->ExceptionRecord->ExceptionInformation[0] != 0) {
		return EXCEPTION_CONTINUE_SEARCH;
	}

	const auto faulting_addr = reinterpret_cast<void*>(ep->ExceptionRecord->ExceptionInformation[1]);

	// Try to commit the faulting page.  If it succeeds the page was a
	// reserved-but-uncommitted guard region inside the heap — resume.
	void* result = VirtualAlloc(faulting_addr, 1, MEM_COMMIT, PAGE_READWRITE);
	if (result != nullptr) {
		return EXCEPTION_CONTINUE_EXECUTION; // page committed — retry the instruction
	}

	// Not a committable page — let something else handle it.
	return EXCEPTION_CONTINUE_SEARCH;
}

struct HeapGuardInstaller {
	HeapGuardInstaller() {
		AddVectoredExceptionHandler(1 /* first */, heap_guard_page_handler);
	}
};

static HeapGuardInstaller g_heap_guard;
#endif
