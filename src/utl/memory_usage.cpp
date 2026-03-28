// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/utl/memory_usage.cpp
// ────────────────────────────────────────────────────────
// memory_usage.cpp

#include "fls/utl/memory_usage.hpp"

#if defined(__APPLE__)
#include <mach/mach.h>
#elif defined(__linux__)
#include <fstream>
#include <unistd.h>
#elif defined(_WIN32)
#include <psapi.h>
#include <windows.h>
#endif

namespace fastlanes {

uint64_t memoryUsageBytes() {
#if defined(__APPLE__)
	mach_task_basic_info   info;
	mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
	if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, reinterpret_cast<task_info_t>(&info), &count) !=
	    KERN_SUCCESS) {
		return 0;
	}
	return static_cast<uint64_t>(info.resident_size);

#elif defined(__linux__)
	std::ifstream statm("/proc/self/statm");
	if (!statm)
		return 0;

	uint64_t total_pages = 0, rss_pages = 0;
	statm >> total_pages >> rss_pages;

	long page_size = sysconf(_SC_PAGESIZE);
	return rss_pages * static_cast<uint64_t>(page_size);

#elif defined(_WIN32)
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
		return static_cast<uint64_t>(pmc.WorkingSetSize);
	}
	return 0;

#endif
}

} // namespace fastlanes
