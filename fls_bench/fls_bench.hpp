#ifndef FASTLANES_COMPRESSION_FLS_BENCH_FLS_BENCH_HPP
#define FASTLANES_COMPRESSION_FLS_BENCH_FLS_BENCH_HPP

/*
 * The M1 cycle counter is from Lemire repo. https://github.com/lemire/Code-used-on-Daniel-Lemire-s-blog/tree/master/2021/03/24
 * The other parts are from google benchmark repo, edited heavily. todo -> add the link
 */
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cerrno>
#include <cerrno> // for errno
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstring> // for memset
#include <ctime>
#include <dlfcn.h>
#include <exception>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <pthread.h>
#include <set>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/ioctl.h> // for ioctl
#include <tuple>
#include <unistd.h> // for syscall
#include <utility>
#include <vector>

#if defined(__linux__)
#include <asm/unistd.h>       // for __NR_perf_event_open
#include <linux/perf_event.h> // for perf event constants
#endif
/*---------------------------------------------------------------------------------------------------------------------\
 * Macros:
\---------------------------------------------------------------------------------------------------------------------*/
// The _MSVC_LANG check should detect Visual Studio 2015 Update 3 and newer.
#if __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
#define BENCHMARK_HAS_CXX11
#endif

// This _MSC_VER check should detect VS 2017 v15.3 and newer.
#if __cplusplus >= 201703L || (defined(_MSC_VER) && _MSC_VER >= 1911 && _MSVC_LANG >= 201703L)
#define BENCHMARK_HAS_CXX17
#endif

#if defined(BENCHMARK_HAS_CXX11)
#include <initializer_list>
#include <type_traits>
#include <utility>
#endif

#if defined(_MSC_VER)
#include <intrin.h> // for _ReadWriteBarrier
#endif

#ifndef BENCHMARK_HAS_CXX11
#define BENCHMARK_DISALLOW_COPY_AND_ASSIGN(TypeName)                                                                   \
	TypeName(const TypeName&);                                                                                         \
	TypeName& operator=(const TypeName&)
#else
#define BENCHMARK_DISALLOW_COPY_AND_ASSIGN(TypeName)                                                                   \
	TypeName(const TypeName&)            = delete;                                                                     \
	TypeName& operator=(const TypeName&) = delete
#endif

#ifdef BENCHMARK_HAS_CXX17
#define BENCHMARK_UNUSED FLS_BENCH_MAYBE_UNUSED
#elif defined(__GNUC__) || defined(__clang__)
#define BENCHMARK_UNUSED __attribute__((unused))
#else
#define BENCHMARK_UNUSED
#endif

#if defined(__GNUC__) || defined(__clang__)
#define BENCHMARK_ALWAYS_INLINE  __attribute__((always_inline))
#define BENCHMARK_NOEXCEPT       noexcept
#define BENCHMARK_NOEXCEPT_OP(x) noexcept(x)
#elif defined(_MSC_VER) && !defined(__clang__)
#define BENCHMARK_ALWAYS_INLINE __forceinline
#if _MSC_VER >= 1900
#define BENCHMARK_NOEXCEPT       noexcept
#define BENCHMARK_NOEXCEPT_OP(x) noexcept(x)
#else
#define BENCHMARK_NOEXCEPT
#define BENCHMARK_NOEXCEPT_OP(x)
#endif
#define __func__ __FUNCTION__
#else
#define BENCHMARK_ALWAYS_INLINE
#define BENCHMARK_NOEXCEPT
#define BENCHMARK_NOEXCEPT_OP(x)
#endif

#define BENCHMARK_INTERNAL_TOSTRING2(x) #x
#define BENCHMARK_INTERNAL_TOSTRING(x)  BENCHMARK_INTERNAL_TOSTRING2(x)

#if defined(__GNUC__) || defined(__clang__)
#define BENCHMARK_BUILTIN_EXPECT(x, y) __builtin_expect(x, y)
#define BENCHMARK_DEPRECATED_MSG(msg)  __attribute__((deprecated(msg)))
#else
#define BENCHMARK_BUILTIN_EXPECT(x, y) x
#define BENCHMARK_DEPRECATED_MSG(msg)
#define BENCHMARK_WARNING_MSG(msg)                                                                                     \
	__pragma(message(__FILE__ "(" BENCHMARK_INTERNAL_TOSTRING(__LINE__) ") : warning note: " msg))
#endif

#if defined(__GNUC__) && !defined(__clang__)
#define BENCHMARK_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#endif

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if defined(__GNUC__) || __has_builtin(__builtin_unreachable)
#define BENCHMARK_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
#define BENCHMARK_UNREACHABLE() __assume(false)
#else
#define BENCHMARK_UNREACHABLE() ((void)0)
#endif

#ifdef BENCHMARK_HAS_CXX11
#else
#endif

// clang-format off

#ifndef __has_feature
    #define __has_feature(x) 0
#endif

#if defined(__clang__)
    #if defined(__ibmxl__)
        #if !defined(COMPILER_IBMXL)
            #define COMPILER_IBMXL
        #endif
    #elif !defined(COMPILER_CLANG)
        #define COMPILER_CLANG
    #endif
#elif defined(_MSC_VER)
    #if !defined(COMPILER_MSVC)
        #define COMPILER_MSVC
    #endif
#elif defined(__GNUC__)
    #if !defined(COMPILER_GCC)
        #define COMPILER_GCC
    #endif
#endif

#if __has_feature(cxx_attributes)
    #define BENCHMARK_NORETURN [[noreturn]]
#elif defined(__GNUC__)
    #define BENCHMARK_NORETURN __attribute__((noreturn))
#elif defined(COMPILER_MSVC)
    #define BENCHMARK_NORETURN __declspec(noreturn)
#else
    #define BENCHMARK_NORETURN
#endif

#if defined(__CYGWIN__)
    #define BENCHMARK_OS_CYGWIN 1
#elif defined(_WIN32)
    #define BENCHMARK_OS_WINDOWS 1
    #if defined(__MINGW32__)
        #define BENCHMARK_OS_MINGW 1
    #endif
#elif defined(__APPLE__)
    #define BENCHMARK_OS_APPLE 1
    #include "TargetConditionals.h"
    #if defined(TARGET_OS_MAC)
        #define BENCHMARK_OS_MACOSX 1
        #if defined(TARGET_OS_IPHONE)
            #define BENCHMARK_OS_IOS 1
        #endif
    #endif
#elif defined(__FreeBSD__)
    #define BENCHMARK_OS_FREEBSD 1
#elif defined(__NetBSD__)
    #define BENCHMARK_OS_NETBSD 1
#elif defined(__OpenBSD__)
    #define BENCHMARK_OS_OPENBSD 1
#elif defined(__DragonFly__)
    #define BENCHMARK_OS_DRAGONFLY 1
#elif defined(__linux__)
    #define BENCHMARK_OS_LINUX 1
#elif defined(__native_client__)
    #define BENCHMARK_OS_NACL 1
#elif defined(__EMSCRIPTEN__)
    #define BENCHMARK_OS_EMSCRIPTEN 1
#elif defined(__rtems__)
    #define BENCHMARK_OS_RTEMS 1
#elif defined(__Fuchsia__)
    #define BENCHMARK_OS_FUCHSIA 1
#elif defined (__SVR4) && defined (__sun)
    #define BENCHMARK_OS_SOLARIS 1
#elif defined(__QNX__)
    #define BENCHMARK_OS_QNX 1
#elif defined(__MVS__)
    #define BENCHMARK_OS_ZOS 1
#endif

#if defined(__ANDROID__) && defined(__GLIBCXX__)
    #define BENCHMARK_STL_ANDROID_GNUSTL 1
#endif

#if !__has_feature(cxx_exceptions) && !defined(__cpp_exceptions) \
    && !defined(__EXCEPTIONS)
    #define BENCHMARK_HAS_NO_EXCEPTIONS
#endif

#if defined(COMPILER_CLANG) || defined(COMPILER_GCC)
    #define FLS_BENCH_MAYBE_UNUSED __attribute__((unused))
#else
    #define BENCHMARK_MAYBE_UNUSED
#endif

// clang-format on

#ifdef BENCHMARK_OS_WINDOWS
#include <shlwapi.h>
#undef StrCat // Don't let StrCat in string_util.h be renamed to lstrcatA
#include <codecvt>
#include <versionhelpers.h>
#include <windows.h>
#else
#include <fcntl.h>
#ifndef BENCHMARK_OS_FUCHSIA
#include <sys/resource.h>
#endif
#include <sys/time.h>
#include <sys/types.h> // this header must be included before 'sys/sysctl.h' to avoid compilation error on FreeBSD
#include <unistd.h>
#if defined BENCHMARK_OS_FREEBSD || defined BENCHMARK_OS_MACOSX || defined BENCHMARK_OS_NETBSD ||                      \
    defined BENCHMARK_OS_OPENBSD || defined BENCHMARK_OS_DRAGONFLY
#define BENCHMARK_HAS_SYSCTL
#include <sys/sysctl.h>
#endif
#endif
#if defined(BENCHMARK_OS_SOLARIS)
#include <kstat.h>
#endif
#if defined(BENCHMARK_OS_QNX)
#include <sys/syspage.h>
#endif

#if defined(__GNUC__) || defined(__clang__)
#define BENCHMARK_ALWAYS_INLINE  __attribute__((always_inline))
#define BENCHMARK_NOEXCEPT       noexcept
#define BENCHMARK_NOEXCEPT_OP(x) noexcept(x)
#elif defined(_MSC_VER) && !defined(__clang__)
#define BENCHMARK_ALWAYS_INLINE __forceinline
#if _MSC_VER >= 1900
#define BENCHMARK_NOEXCEPT       noexcept
#define BENCHMARK_NOEXCEPT_OP(x) noexcept(x)
#else
#define BENCHMARK_NOEXCEPT
#define BENCHMARK_NOEXCEPT_OP(x)
#endif
#define __func__ __FUNCTION__
#else
#define BENCHMARK_ALWAYS_INLINE
#define BENCHMARK_NOEXCEPT
#define BENCHMARK_NOEXCEPT_OP(x)
#endif

#if defined(BENCHMARK_OS_MACOSX)
#include <mach/mach_time.h>
#endif
// For MSVC, we want to use '_asm rdtsc' when possible (since it works
// with even ancient MSVC compilers), and when not possible the
// __rdtsc intrinsic, declared in <intrin.h>.  Unfortunately, in some
// environments, <windows.h> and <intrin.h> have conflicting
// declarations of some other intrinsics, breaking compilation.
// Therefore, we simply declare __rdtsc ourselves. See also
// http://connect.microsoft.com/VisualStudio/feedback/details/262047
#if defined(COMPILER_MSVC) && !defined(_M_IX86) && !defined(_M_ARM64)
extern "C" uint64_t __rdtsc();
#pragma intrinsic(__rdtsc)
#endif

#if !defined(BENCHMARK_OS_WINDOWS) || defined(BENCHMARK_OS_MINGW)
#include <sys/time.h>
#include <time.h>
#endif

#ifdef BENCHMARK_OS_EMSCRIPTEN
#include <emscripten.h>
#endif

#ifdef __aarch64__
#define KPERF_LIST                                                                                                     \
	/*  ret, name, params */                                                                                           \
	F(int, kpc_get_counting, void)                                                                                     \
	F(int, kpc_force_all_ctrs_set, int)                                                                                \
	F(int, kpc_set_counting, uint32_t)                                                                                 \
	F(int, kpc_set_thread_counting, uint32_t)                                                                          \
	F(int, kpc_set_config, uint32_t, void*)                                                                            \
	F(int, kpc_get_config, uint32_t, void*)                                                                            \
	F(int, kpc_set_period, uint32_t, void*)                                                                            \
	F(int, kpc_get_period, uint32_t, void*)                                                                            \
	F(uint32_t, kpc_get_counter_count, uint32_t)                                                                       \
	F(uint32_t, kpc_get_config_count, uint32_t)                                                                        \
	F(int, kperf_sample_get, int*)                                                                                     \
	F(int, kpc_get_thread_counters, int, unsigned int, void*)

#define F(ret, name, ...)                                                                                              \
	typedef ret        name##proc(__VA_ARGS__);                                                                        \
	static name##proc* name;
KPERF_LIST
#undef F

#define CFGWORD_EL0A32EN_MASK       (0x10000)
#define CFGWORD_EL0A64EN_MASK       (0x20000)
#define CFGWORD_EL1EN_MASK          (0x40000)
#define CFGWORD_EL3EN_MASK          (0x80000)
#define CFGWORD_ALLMODES_MASK       (0xf0000)

#define CPMU_NONE                   0
#define CPMU_CORE_CYCLE             0x02
#define CPMU_INST_A64               0x8c
#define CPMU_INST_BRANCH            0x8d
#define CPMU_SYNC_DC_LOAD_MISS      0xbf
#define CPMU_SYNC_DC_STORE_MISS     0xc0
#define CPMU_SYNC_DTLB_MISS         0xc1
#define CPMU_SYNC_ST_HIT_YNGR_LD    0xc4
#define CPMU_SYNC_BR_ANY_MISP       0xcb
#define CPMU_FED_IC_MISS_DEM        0xd3
#define CPMU_FED_ITLB_MISS          0xd4

#define KPC_CLASS_FIXED             (0)
#define KPC_CLASS_CONFIGURABLE      (1)
#define KPC_CLASS_POWER             (2)
#define KPC_CLASS_RAWPMU            (3)
#define KPC_CLASS_FIXED_MASK        (1u << KPC_CLASS_FIXED)
#define KPC_CLASS_CONFIGURABLE_MASK (1u << KPC_CLASS_CONFIGURABLE)
#define KPC_CLASS_POWER_MASK        (1u << KPC_CLASS_POWER)
#define KPC_CLASS_RAWPMU_MASK       (1u << KPC_CLASS_RAWPMU)

#define COUNTERS_COUNT              10
#define CONFIG_COUNT                8
#define KPC_MASK                    (KPC_CLASS_CONFIGURABLE_MASK | KPC_CLASS_FIXED_MASK)

#endif

#ifdef BENCHMARK_OS_WINDOWS
#include <windows.h>
#endif

#ifdef BENCHMARK_OS_ZOS
#include <unistd.h>
#endif

#include <array>
#ifdef BENCHMARK_STL_ANDROID_GNUSTL
#include <cerrno>
#endif

#ifdef BENCHMARK_OS_WINDOWS
#include <shlwapi.h>
#undef StrCat // Don't let StrCat in string_util.h be renamed to lstrcatA
#include <codecvt>
#include <versionhelpers.h>
#include <windows.h>
#else
#include <fcntl.h>
#ifndef BENCHMARK_OS_FUCHSIA
#include <sys/resource.h>
#endif
#include <sys/time.h>
#include <sys/types.h> // this header must be included before 'sys/sysctl.h' to avoid compilation error on FreeBSD
#include <unistd.h>
#if defined BENCHMARK_OS_FREEBSD || defined BENCHMARK_OS_MACOSX || defined BENCHMARK_OS_NETBSD ||                      \
    defined BENCHMARK_OS_OPENBSD || defined BENCHMARK_OS_DRAGONFLY
#define BENCHMARK_HAS_SYSCTL
#include <sys/sysctl.h>
#endif
#endif
#if defined(BENCHMARK_OS_SOLARIS)
#include <kstat.h>
#endif
#if defined(BENCHMARK_OS_QNX)
#include <sys/syspage.h>
#endif

#define SOURCE_DIR                  "${CMAKE_SOURCE_DIR}"
#define CMAKE_OSX_ARCHITECTURES     "${CMAKE_OSX_ARCHITECTURES}"
#define CMAKE_HOST_SYSTEM_PROCESSOR "${CMAKE_HOST_SYSTEM_PROCESSOR}"
#define CMAKE_SYSTEM_PROCESSOR      "${CMAKE_SYSTEM_PROCESSOR}"
#define CMAKE_HOST_SYSTEM_NAME      "${CMAKE_HOST_SYSTEM_NAME}"
#define CMAKE_SYSTEM_NAME           "${CMAKE_SYSTEM_NAME}"
#define CMAKE_C_COMPILER            "${CMAKE_C_COMPILER}"
#define CMAKE_CXX_COMPILER          "${CMAKE_CXX_COMPILER}"
#define CMAKE_CXX_COMPILER_ID       "${CMAKE_CXX_COMPILER_ID}"
#define CMAKE_CXX_COMPILER_VERSION  "${CMAKE_CXX_COMPILER_VERSION}"
#define CMAKE_CROSSCOMPILING        "${CMAKE_CROSSCOMPILING}"
#define CMAKE_CXX_FLAGS_DEBUG       "${CMAKE_CXX_FLAGS_DEBUG}"
#define CMAKE_CXX_FLAGS_RELEASE     "${CMAKE_CXX_FLAGS_RELEASE}"
#define CMAKE_BUILD_TYPE            "${CMAKE_BUILD_TYPE}"
#define CMAKE_TOOLCHAIN_FILE        "${CMAKE_TOOLCHAIN_FILE}"

#define TARGET_NAME                 "${TARGET_NAME}"
#define TARGET_COMPILE_OPTIONS      "${TARGET_COMPILE_OPTIONS}"

/*---------------------------------------------------------------------------------------------------------------------\
 * Lib:
\---------------------------------------------------------------------------------------------------------------------*/
namespace benchmark {
/* From: https://github.com/WojciechMula/toys/blob/master/000helpers/linux-perf-events.h
 * Now api has been added to be compatible with the rest of fls_bench.
 */
#if defined(__linuxm__)
namespace perf {
template <int TYPE = PERF_TYPE_HARDWARE>
class LinuxEvents {

	int             fd;
	perf_event_attr attribs;
	bool            running;

public:
	LinuxEvents(int config)
	    : fd(0) {
		memset(&attribs, 0, sizeof(attribs));
		attribs.type           = TYPE;
		attribs.size           = sizeof(attribs);
		attribs.config         = config;
		attribs.disabled       = 1;
		attribs.exclude_kernel = 1;
		attribs.exclude_hv     = 1;

		const int           pid   = 0;  // the current process
		const int           cpu   = -1; // all CPUs
		const int           group = -1; // no group
		const unsigned long flags = 0;
		fd                        = syscall(__NR_perf_event_open, &attribs, pid, cpu, group, flags);
		if (fd == -1) { report_error("perf_event_open"); }

		running = false;
	}

	~LinuxEvents() { close(fd); }

	void start() {
		if (ioctl(fd, PERF_EVENT_IOC_RESET, 0) == -1) { report_error("ioctl(PERF_EVENT_IOC_RESET)"); }

		if (ioctl(fd, PERF_EVENT_IOC_ENABLE, 0) == -1) { report_error("ioctl(PERF_EVENT_IOC_ENABLE)"); }
	}

	unsigned long end() {
		if (ioctl(fd, PERF_EVENT_IOC_DISABLE, 0) == -1) { report_error("ioctl(PERF_EVENT_IOC_DISABLE)"); }

		unsigned long result;
		if (read(fd, &result, sizeof(result)) == -1) { report_error("read"); }

		return result;
	}

	unsigned long now() {
		if (!running) {
			if (ioctl(fd, PERF_EVENT_IOC_RESET, 0) == -1) { report_error("ioctl(PERF_EVENT_IOC_RESET)"); }

			if (ioctl(fd, PERF_EVENT_IOC_ENABLE, 0) == -1) { report_error("ioctl(PERF_EVENT_IOC_ENABLE)"); }

			running = true;
			return 0;
		} else {
			if (ioctl(fd, PERF_EVENT_IOC_DISABLE, 0) == -1) { report_error("ioctl(PERF_EVENT_IOC_DISABLE)"); }

			unsigned long result;
			if (read(fd, &result, sizeof(result)) == -1) { report_error("read"); }

			running = false;
			return result;
		}
	}

private:
	void report_error(const std::string& context) {
		throw std::runtime_error(context + ": " + std::string(strerror(errno)));
	}
};

} // namespace perf

perf::LinuxEvents<PERF_TYPE_HARDWARE> cycles(PERF_COUNT_HW_CPU_CYCLES);
#endif

// NOTE: only i386 and x86_64 have been well tested.
// PPC, sparc, alpha, and ia64 are based on
//    http://peter.kuscsik.com/wordpress/?p=14
// with modifications by m3b.  See also
//    https://setisvn.ssl.berkeley.edu/svn/lib/fftw-3.0.1/kernel/cycle.h
namespace cycleclock {

#if defined(__aarch64__)
#if defined(__APPLE__)
static uint64_t g_counters[COUNTERS_COUNT];
static uint64_t g_config[COUNTERS_COUNT];
#endif
#endif

FLS_BENCH_MAYBE_UNUSED static uint64_t get_counters() {
#if defined(__aarch64__)
#if defined(__APPLE__)
	static bool WARNED = false;
	if (kpc_get_thread_counters(0, COUNTERS_COUNT, g_counters)) {
		if (!WARNED) {
			printf("kpc_get_thread_counters failed, run as sudo?\n");
			WARNED = true;
		}
		return 1;
	}
	// g_counters[3 + 2] gives you the number of instructions 'decoded'
	// whereas g_counters[1] might give you the number of instructions 'retired'.
	return g_counters[0 + 2];
#endif
#endif
	return 0;
}

FLS_BENCH_MAYBE_UNUSED static void configure_rdtsc() {
#if defined(__aarch64__)
#if defined(__APPLE__)
	if (kpc_set_config(KPC_MASK, g_config)) {
		printf("kpc_set_config failed\n");
		return;
	}

	if (kpc_force_all_ctrs_set(1)) {
		printf("kpc_force_all_ctrs_set failed\n");
		return;
	}

	if (kpc_set_counting(KPC_MASK)) {
		printf("kpc_set_counting failed\n");
		return;
	}

	if (kpc_set_thread_counting(KPC_MASK)) {
		printf("kpc_set_thread_counting failed\n");
		return;
	}
#endif
#endif
}

static void Init() {
#if defined(__aarch64__)
#if defined(__APPLE__)
	void* kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY);
	if (!kperf) {
		printf("kperf = %p\n", kperf);
		return;
	}
#define F(ret, name, ...)                                                                                              \
	name = (name##proc*)(dlsym(kperf, #name));                                                                         \
	if (!name) {                                                                                                       \
		printf("%s = %p\n", #name, (void*)name);                                                                       \
		return;                                                                                                        \
	}
	KPERF_LIST
#undef F

	if (kpc_get_counter_count(KPC_MASK) != COUNTERS_COUNT) {
		printf("wrong fixed counters count\n");
		return;
	}

	if (kpc_get_config_count(KPC_MASK) != CONFIG_COUNT) {
		printf("wrong fixed config count\n");
		return;
	}
	g_config[0] = CPMU_CORE_CYCLE | CFGWORD_EL0A64EN_MASK;
	g_config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
	g_config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
	g_config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

	configure_rdtsc();
#endif
#endif
}
static uint64_t get_counters();
// This should return the number of cycles since power-on.  Thread-safe.
inline BENCHMARK_ALWAYS_INLINE int64_t Now() {
	// #if defined(BENCHMARK_OS_MACOSX)
	//   // this goes at the top because we need ALL Macs, regardless of
	//   // architecture, to return the number of "mach time units" that
	//   // have passed since startup.  See sysinfo.cc where
	//   // InitializeSystemInfo() sets the supposed cpu clock frequency of
	//   // macs to the number of mach time units per second, not actual
	//   // CPU clock frequency (which can change in the face of CPU
	//   // frequency scaling).  Also note that when the Mac sleeps, this
	//   // counter pauses; it does not continue counting, nor does it
	//   // reset to zero.
	//   return mach_absolute_time();
	// #el
#if defined(BENCHMARK_OS_EMSCRIPTEN)
	// this goes above x86-specific code because old versions of Emscripten
	// define __x86_64__, although they have nothing to do with it.
	//        return static_cast<int64_t>(emscripten_get_now() * 1e+6);

	return std::chrono::high_resolution_clock::now().time_since_epoch().count();
#elif defined(__i386__)
	int64_t ret;
	__asm__ volatile("rdtsc" : "=A"(ret));
	return ret;
#elif defined(__x86_64__) || defined(__amd64__)
	uint64_t low, high;
	__asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
	return (high << 32) | low;
#elif defined(__powerpc__) || defined(__ppc__)
	// This returns a time-base, which is not always precisely a cycle-count.
#if defined(__powerpc64__) || defined(__ppc64__)
	int64_t tb;
	asm volatile("mfspr %0, 268" : "=r"(tb));
	return tb;
#else
	uint32_t tbl, tbu0, tbu1;
	asm volatile("mftbu %0\n"
	             "mftb %1\n"
	             "mftbu %2"
	             : "=r"(tbu0), "=r"(tbl), "=r"(tbu1));
	tbl &= -static_cast<int32_t>(tbu0 == tbu1);
	// high 32 bits in tbu1; low 32 bits in tbl  (tbu0 is no longer needed)
	return (static_cast<uint64_t>(tbu1) << 32) | tbl;
#endif
#elif defined(__sparc__)
	int64_t tick;
	asm(".byte 0x83, 0x41, 0x00, 0x00");
	asm("mov   %%g1, %0" : "=r"(tick));
	return tick;
#elif defined(__ia64__)
	int64_t itc;
	asm("mov %0 = ar.itc" : "=r"(itc));
	return itc;
#elif defined(COMPILER_MSVC) && defined(_M_IX86)
	// Older MSVC compilers (like 7.x) don't seem to support the
	// __rdtsc intrinsic properly, so I prefer to use _asm instead
	// when I know it will work.  Otherwise, I'll use __rdtsc and hope
	// the code is being compiled with a non-ancient compiler.
	_asm rdtsc
#elif defined(COMPILER_MSVC) && defined(_M_ARM64)
	// See
	// https://docs.microsoft.com/en-us/cpp/intrinsics/arm64-intrinsics?view=vs-2019
	// and https://reviews.llvm.org/D53115
	int64_t virtual_timer_value;
	virtual_timer_value = _ReadStatusReg(ARM64_CNTVCT);
	return virtual_timer_value;
#elif defined(COMPILER_MSVC)
	return __rdtsc();
#elif defined(BENCHMARK_OS_NACL)
	// Native Client validator on x86/x86-64 allows RDTSC instructions,
	// and this case is handled above. Native Client validator on ARM
	// rejects MRC instructions (used in the ARM-specific sequence below),
	// so we handle it here. Portable Native Client compiles to
	// architecture-agnostic bytecode, which doesn't provide any
	// cycle counter access mnemonics.

	// Native Client does not provide any API to access cycle counter.
	// Use clock_gettime(CLOCK_MONOTONIC, ...) instead of gettimeofday
	// because is provides nanosecond resolution (which is noticable at
	// least for PNaCl modules running on x86 Mac & Linux).
	// Initialize to always return 0 if clock_gettime fails.
	struct timespec ts = {0, 0};
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return static_cast<int64_t>(ts.tv_sec) * 1000000000 + ts.tv_nsec;
#elif defined(__aarch64__)
	// System timer of ARMv8 runs at a different frequency than the CPU's.
	// The frequency is fixed, typically in the range 1-50MHz.  It can be
	// read at CNTFRQ special register.  We assume the OS has set up
	// the virtual timer properly.
	//  int64_t virtual_timer_value;
	//  asm volatile("mrs %0, cntvct_el0" : "=r"(virtual_timer_value));
	//  return virtual_timer_value;
#if defined(__APPLE__)
	return get_counters();
#else
	return cycles.now();
#endif

#elif defined(__ARM_ARCH)
	// V6 is the earliest arch that has a standard cyclecount
	// Native Client validator doesn't allow MRC instructions.
#if (__ARM_ARCH >= 6)
	uint32_t pmccntr;
	uint32_t pmuseren;
	uint32_t pmcntenset;
	// Read the user mode perf monitor counter access permissions.
	asm volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
	if (pmuseren & 1) // Allows reading perfmon counters for user mode code.
	{
		asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
		if (pmcntenset & 0x80000000ul) // Is it counting?
		{
			asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
			// The counter is set up to count every 64th cycle
			return static_cast<int64_t>(pmccntr) * 64; // Should optimize to << 6
		}
	}
#endif
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return static_cast<int64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
#elif defined(__mips__) || defined(__m68k__)
	// mips apparently only allows rdtsc for superusers, so we fall
	// back to gettimeofday.  It's possible clock_gettime would be better.
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return static_cast<int64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
#elif defined(__s390__) // Covers both s390 and s390x.
	// Return the CPU clock.
	uint64_t tsc;
#if defined(BENCHMARK_OS_ZOS) && defined(COMPILER_IBMXL)
	// z/OS XL compiler HLASM syntax.
	asm(" stck %0" : "=m"(tsc) : : "cc");
#else
	asm("stck %0" : "=Q"(tsc) : : "cc");
#endif
	return tsc;
#elif defined(__riscv) // RISC-V
	// Use RDCYCLE (and RDCYCLEH on riscv32)
#if __riscv_xlen == 32
	uint32_t cycles_lo, cycles_hi0, cycles_hi1;
	// This asm also includes the PowerPC overflow handling strategy, as above.
	// Implemented in assembly because Clang insisted on branching.
	asm volatile("rdcycleh %0\n"
	             "rdcycle %1\n"
	             "rdcycleh %2\n"
	             "sub %0, %0, %2\n"
	             "seqz %0, %0\n"
	             "sub %0, zero, %0\n"
	             "and %1, %1, %0\n"
	             : "=r"(cycles_hi0), "=r"(cycles_lo), "=r"(cycles_hi1));
	return (static_cast<uint64_t>(cycles_hi1) << 32) | cycles_lo;
#else
	uint64_t cycles;
	asm volatile("rdcycle %0" : "=r"(cycles));
	return cycles;
#endif
#elif defined(__e2k__) || defined(__elbrus__)
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return static_cast<int64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
#else
	// The soft failover to a generic implementation is automatic only for ARM.
	// For other platforms the developer is expected to make an attempt to create
	// a fast implementation and use generic version if nothing better is available.
#error You need to define CycleTimer for your OS and CPU
	//    return
	// std::chrono::high_resolution_clock::now().time_since_epoch().count();

#endif
}
} // end namespace cycleclock

namespace timer {
inline uint64_t Now() { return std::chrono::high_resolution_clock::now().time_since_epoch().count(); }
} // namespace timer

const int kNumMillisPerSecond = 1000;
const int kNumMicrosPerMilli  = 1000;
const int kNumMicrosPerSecond = kNumMillisPerSecond * 1000;
const int kNumNanosPerMicro   = 1000;
const int kNumNanosPerSecond  = kNumNanosPerMicro * kNumMicrosPerSecond;

#ifdef BENCHMARK_OS_WINDOWS
// Window's Sleep takes milliseconds argument.
void SleepForMilliseconds(int milliseconds) { Sleep(milliseconds); }
void SleepForSeconds(double seconds) { SleepForMilliseconds(static_cast<int>(kNumMillisPerSecond * seconds)); }
#else // BENCHMARK_OS_WINDOWS
static void SleepForMicroseconds(int microseconds) {
#ifdef BENCHMARK_OS_ZOS
	// z/OS does not support nanosleep. Instead call sleep() and then usleep() to
	// sleep for the remaining microseconds because usleep() will fail if its
	// argument is greater than 1000000.
	div_t sleepTime = div(microseconds, kNumMicrosPerSecond);
	int seconds = sleepTime.quot;
	while (seconds != 0) {
		seconds = sleep(seconds);
	}
	while (usleep(sleepTime.rem) == -1 && errno == EINTR)
		;
#else
	struct timespec sleep_time;
	sleep_time.tv_sec  = microseconds / kNumMicrosPerSecond;
	sleep_time.tv_nsec = (microseconds % kNumMicrosPerSecond) * kNumNanosPerMicro;
	while (nanosleep(&sleep_time, &sleep_time) != 0 && errno == EINTR)
		; // Ignore signals and wait for the full interval to elapse.
#endif
}

static void SleepForMilliseconds(int milliseconds) { SleepForMicroseconds(milliseconds * kNumMicrosPerMilli); }

FLS_BENCH_MAYBE_UNUSED static void SleepForSeconds(double seconds) {
	SleepForMicroseconds(static_cast<int>(seconds * kNumMicrosPerSecond));
}
#endif // BENCHMARK_OS_WINDOWS

namespace internal {
// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

// That gcc wants both of these prototypes seems mysterious. VC, for
// its part, can't decide which to use (another mystery). Matching of
// template overloads: the final frontier.
#ifndef COMPILER_MSVC
template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];
#endif

#define arraysize(array) (sizeof(::benchmark::internal::ArraySizeHelper(array)))

} // namespace internal

// kilo, Mega, Giga, Tera, Peta, Exa, Zetta, Yotta.
const char kBigSIUnits[] = "kMGTPEZY";
// Kibi, Mebi, Gibi, Tebi, Pebi, Exbi, Zebi, Yobi.
const char kBigIECUnits[] = "KMGTPEZY";
// milli, micro, nano, pico, femto, atto, zepto, yocto.
const char kSmallSIUnits[] = "munpfazy";

// We require that all three arrays have the same size.
static_assert(arraysize(kBigSIUnits) == arraysize(kBigIECUnits), "SI and IEC unit arrays must be the same size");
static_assert(arraysize(kSmallSIUnits) == arraysize(kBigSIUnits),
              "Small SI and Big SI unit arrays must be the same size");

static const int64_t kUnitsSize = arraysize(kBigSIUnits);

static void ToExponentAndMantissa(
    double val, double thresh, int precision, double one_k, std::string* mantissa, int64_t* exponent) {
	std::stringstream mantissa_stream;

	if (val < 0) {
		mantissa_stream << "-";
		val = -val;
	}

	// Adjust threshold so that it never excludes things which can't be rendered
	// in 'precision' digits.
	const double adjusted_threshold = std::max(thresh, 1.0 / std::pow(10.0, precision));
	const double big_threshold      = adjusted_threshold * one_k;
	const double small_threshold    = adjusted_threshold;
	// Values in ]simple_threshold,small_threshold[ will be printed as-is
	const double simple_threshold = 0.01;

	if (val > big_threshold) {
		// Positive powers
		double scaled = val;
		for (size_t i = 0; i < arraysize(kBigSIUnits); ++i) {
			scaled /= one_k;
			if (scaled <= big_threshold) {
				mantissa_stream << scaled;
				*exponent = i + 1;
				*mantissa = mantissa_stream.str();
				return;
			}
		}
		mantissa_stream << val;
		*exponent = 0;
	} else if (val < small_threshold) {
		// Negative powers
		if (val < simple_threshold) {
			double scaled = val;
			for (size_t i = 0; i < arraysize(kSmallSIUnits); ++i) {
				scaled *= one_k;
				if (scaled >= small_threshold) {
					mantissa_stream << scaled;
					*exponent = -static_cast<int64_t>(i + 1);
					*mantissa = mantissa_stream.str();
					return;
				}
			}
		}
		mantissa_stream << val;
		*exponent = 0;
	} else {
		mantissa_stream << val;
		*exponent = 0;
	}
	*mantissa = mantissa_stream.str();
}

static std::string ExponentToPrefix(int64_t exponent, bool iec) {
	if (exponent == 0) { return ""; }

	const int64_t index = (exponent > 0 ? exponent - 1 : -exponent - 1);
	if (index >= kUnitsSize) { return ""; }

	const char* array = (exponent > 0 ? (iec ? kBigIECUnits : kBigSIUnits) : kSmallSIUnits);
	if (iec) {
		return array[index] + std::string("i");
	} else {
		return std::string(1, array[index]);
	}
}

static std::string ToBinaryStringFullySpecified(double value, double threshold, int precision, double one_k = 1024.0) {
	std::string mantissa;
	int64_t     exponent;
	ToExponentAndMantissa(value, threshold, precision, one_k, &mantissa, &exponent);
	return mantissa + ExponentToPrefix(exponent, false);
}

FLS_BENCH_MAYBE_UNUSED static void AppendHumanReadable(int n, std::string* str) {
	std::stringstream ss;
	// Round down to the nearest SI prefix.
	ss << ToBinaryStringFullySpecified(n, 1.0, 0);
	*str += ss.str();
}

FLS_BENCH_MAYBE_UNUSED static std::string HumanReadableNumber(double n, double one_k = 1024.0) {
	// 1.1 means that figures up to 1.1k should be shown with the next unit down;
	// this softens edge effects.
	// 1 means that we should show one decimal place of precision.
	return ToBinaryStringFullySpecified(n, 1.1, 1, one_k);
}

static std::string StrFormatImp(const char* msg, va_list args) {
	// we might need a second shot at this, so pre-emptivly make a copy
	va_list args_cp;
	va_copy(args_cp, args);

	// TODO(ericwf): use std::array for first attempt to avoid one memory
	// allocation guess what the size might be
	std::array<char, 256> local_buff;
	std::size_t           size = local_buff.size();
	// 2015-10-08: vsnprintf is used instead of snd::vsnprintf due to a limitation
	// in the android-ndk
	auto ret = vsnprintf(local_buff.data(), size, msg, args_cp);

	va_end(args_cp);

	// handle empty expansion
	if (ret == 0) return std::string {};
	if (static_cast<std::size_t>(ret) < size) { return std::string(local_buff.data()); }

	// we did not provide a long enough buffer on our first attempt.
	// add 1 to size to account for null-byte in size cast to prevent overflow
	size          = static_cast<std::size_t>(ret) + 1;
	auto buff_ptr = std::unique_ptr<char[]>(new char[size]);
	// 2015-10-08: vsnprintf is used instead of snd::vsnprintf due to a limitation
	// in the android-ndk
	ret = vsnprintf(buff_ptr.get(), size, msg, args);
	return std::string(buff_ptr.get());
}

#if defined(__MINGW32__)
__attribute__((format(__MINGW_PRINTF_FORMAT, 1, 2)))
#elif defined(__GNUC__)
__attribute__((format(printf, 1, 2)))
#endif

static std::string
StrFormat(const char* format, ...) {
	va_list args;
	va_start(args, format);
	std::string tmp = StrFormatImp(format, args);
	va_end(args);
	return tmp;
}

inline std::ostream& StrCatImp(std::ostream& out) { return out; }

template <class First, class... Rest>
inline std::ostream& StrCatImp(std::ostream& out, First&& f, Rest&&... rest) {
	out << std::forward<First>(f);
	return StrCatImp(out, std::forward<Rest>(rest)...);
}

template <class... Args>
inline std::string StrCat(Args&&... args) {
	std::ostringstream ss;
	StrCatImp(ss, std::forward<Args>(args)...);
	return ss.str();
}

std::vector<std::string> StrSplit(const std::string& str, char delim);

#ifdef BENCHMARK_STL_ANDROID_GNUSTL
/*
 * GNU STL in Android NDK lacks support for some C++11 functions, including
 * stoul, stoi, stod. We reimplement them here using C functions strtoul,
 * strtol, strtod. Note that reimplemented functions are in benchmark::
 * namespace, not std:: namespace.
 */
unsigned long stoul(const std::string& str, size_t* pos = nullptr, int base = 10);
int           stoi(const std::string& str, size_t* pos = nullptr, int base = 10);
double        stod(const std::string& str, size_t* pos = nullptr);
#else
using std::stod;
using std::stoi;
using std::stoul;
#endif

class CPUInfo {
public:
	struct CacheInfo {
		std::string type;
		int         level;
		int         size;
		int         num_sharing;
	};

	enum Scaling { UNKNOWN, ENABLED, DISABLED };

	static inline std::string ToString(Scaling v) {
		switch (v) {
		case UNKNOWN:
			return "UNKNOWN";
		case ENABLED:
			return "ENABLED";
		case DISABLED:
			return "DISABLED";
		default:
			return "UNKNOWN";
		}
	}

	// Getters
	static const CPUInfo& getInstance() {
		static const CPUInfo info;
		return info;
	}
	int                           getNumCpus() const { return num_cpus; };
	double                        getCyclesPerSecond() const { return cycles_per_second; };
	const std::vector<CacheInfo>& getCaches() const { return caches; };
	const std::vector<double>&    getLoadAvg() const { return load_avg; };
	std::string                   getScaling() const { return ToString(scaling); };

	int                    num_cpus;
	Scaling                scaling;
	double                 cycles_per_second;
	std::vector<CacheInfo> caches;
	std::vector<double>    load_avg;

private:
	// private constructor
	CPUInfo();

	BENCHMARK_DISALLOW_COPY_AND_ASSIGN(CPUInfo);
};

static void PrintImp(std::ostream& out) { out << std::endl; }

template <class First, class... Rest>
void PrintImp(std::ostream& out, First&& f, Rest&&... rest) {
	out << std::forward<First>(f);
	PrintImp(out, std::forward<Rest>(rest)...);
}

template <class... ARGS>
BENCHMARK_NORETURN void PrintErrorAndDie(ARGS&&... args) {
	PrintImp(std::cerr, std::forward<ARGS>(args)...);
	std::exit(EXIT_FAILURE);
}

#ifdef BENCHMARK_HAS_SYSCTL

/// ValueUnion - A type used to correctly alias the byte-for-byte output of
/// `sysctl` with the result type it's to be interpreted as.
struct ValueUnion {
	union DataT {
		uint32_t uint32_value;
		uint64_t uint64_value;
		// For correct aliasing of union members from bytes.
		char bytes[8];
	};
	using DataPtr = std::unique_ptr<DataT, decltype(&std::free)>;

	// The size of the data union member + its trailing array size.
	size_t  Size;
	DataPtr Buff;

public:
	ValueUnion()
	    : Size(0)
	    , Buff(nullptr, &std::free) {}

	explicit ValueUnion(size_t buff_size)
	    : Size(sizeof(DataT) + buff_size)
	    , Buff(::new(std::malloc(Size)) DataT(), &std::free) {}

	ValueUnion(ValueUnion&& other) = default;
	explicit    operator bool() const { return bool(Buff); }
	char*       data() const { return Buff->bytes; }
	std::string GetAsString() const { return {data()}; }
	int64_t     GetAsInteger() const {
        if (Size == sizeof(Buff->uint32_value)) {
            return static_cast<int32_t>(Buff->uint32_value);
        } else if (Size == sizeof(Buff->uint64_value)) {
            return static_cast<int64_t>(Buff->uint64_value);
        }
        BENCHMARK_UNREACHABLE();
	}
	uint64_t GetAsUnsigned() const {
		if (Size == sizeof(Buff->uint32_value)) {
			return Buff->uint32_value;
		} else if (Size == sizeof(Buff->uint64_value)) {
			return Buff->uint64_value;
		}
		BENCHMARK_UNREACHABLE();
	}
	template <class T, int N>
	std::array<T, N> GetAsArray() {
		const int ArrSize = sizeof(T) * N;
		//    CHECK_LE(ArrSize, Size);
		std::array<T, N> arr;
		std::memcpy(arr.data(), data(), ArrSize);
		return arr;
	}
};

static ValueUnion GetSysctlImp(std::string const& name) {
#if defined       BENCHMARK_OS_OPENBSD
    int mib[2];

    mib[0] = CTL_HW;
    if ((Name == "hw.ncpu") || (Name == "hw.cpuspeed")) {
        ValueUnion buff(sizeof(int));

        if (Name == "hw.ncpu") {
            mib[1] = HW_NCPU;
        } else {
            mib[1] = HW_CPUSPEED;
        }

        if (sysctl(mib, 2, buff.data(), &buff.Size, nullptr, 0) == -1) { return ValueUnion(); }
        return buff;
    }
    return ValueUnion();
#else
	size_t cur_buff_size = 0;
	if (sysctlbyname(name.c_str(), nullptr, &cur_buff_size, nullptr, 0) == -1) { return {}; }

	ValueUnion buff(cur_buff_size);
	if (sysctlbyname(name.c_str(), buff.data(), &buff.Size, nullptr, 0) == 0) { return buff; }
	return {};
#endif
}

FLS_BENCH_MAYBE_UNUSED static bool GetSysctl(std::string const& name, std::string* out) {
	out->clear();
	auto buff = GetSysctlImp(name);
	if (!buff) { return false; }
	out->assign(buff.data());
	return true;
}

template <class TP, class = typename std::enable_if<std::is_integral<TP>::value>::type>
bool GetSysctl(std::string const& name, TP* Out) {
	*Out      = 0;
	auto buff = GetSysctlImp(name);
	if (!buff) { return false; }
	*Out = static_cast<TP>(buff.GetAsUnsigned());
	return true;
}

template <class TP, size_t N>
bool GetSysctl(std::string const& name, std::array<TP, N>* Out) {
	auto buff = GetSysctlImp(name);
	if (!buff) { return false; }
	*Out = buff.GetAsArray<TP, N>();
	return true;
}
#endif

template <class ARG_T>
bool ReadFromFile(std::string const& fname, ARG_T* arg) {
	*arg = ARG_T();
	std::ifstream f(fname.c_str());
	if (!f.is_open()) { return false; }
	f >> *arg;
	return f.good();
}

static CPUInfo::Scaling CpuScaling(int num_cpus) {
	// We don't have a valid CPU count, so don't even bother.
	if (num_cpus <= 0) { return CPUInfo::Scaling::UNKNOWN; }
#ifdef BENCHMARK_OS_QNX
	return CPUInfo::Scaling::UNKNOWN;
#endif
#ifndef BENCHMARK_OS_WINDOWS
	// On Linux, the CPUfreq subsystem exposes CPU information as files on the
	// local file system. If reading the exported files fails, then we may not be
	// running on Linux, so we silently ignore all the read errors.
	std::string res;
	for (int cpu = 0; cpu < num_cpus; ++cpu) {
		std::string governor_file = StrCat("/sys/devices/system/cpu/cpu", cpu, "/cpufreq/scaling_governor");
		if (ReadFromFile(governor_file, &res) && res != "performance") { return CPUInfo::Scaling::ENABLED; }
	}
	return CPUInfo::Scaling::DISABLED;
#endif
	return CPUInfo::Scaling::UNKNOWN;
}

static int CountSetBitsInCPUMap(std::string val) {
	auto count_bits = [](std::string Part) {
		using CPUMask = std::bitset<sizeof(std::uintptr_t) * CHAR_BIT>;
		Part          = "0x" + Part;
		CPUMask mask(benchmark::stoul(Part, nullptr, 16));
		return static_cast<int>(mask.count());
	};
	size_t pos;
	int    total = 0;
	while ((pos = val.find(',')) != std::string::npos) {
		total += count_bits(val.substr(0, pos));
		val = val.substr(pos + 1);
	}
	if (!val.empty()) { total += count_bits(val); }
	return total;
}

FLS_BENCH_MAYBE_UNUSED
static std::vector<CPUInfo::CacheInfo> GetCacheSizesFromKVFS() {
	std::vector<CPUInfo::CacheInfo> res;
	std::string                     dir = "/sys/devices/system/cpu/cpu0/cache/";
	int                             idx = 0;
	while (true) {
		CPUInfo::CacheInfo info;
		std::string        f_path = StrCat(dir, "index", idx++, "/");
		std::ifstream      f(StrCat(f_path, "size").c_str());
		if (!f.is_open()) { break; }
		std::string suffix;
		f >> info.size;
		if (f.fail()) { PrintErrorAndDie("Failed while reading file '", f_path, "size'"); }
		if (f.good()) {
			f >> suffix;
			if (f.bad()) {
				PrintErrorAndDie("Invalid cache size format: failed to read size suffix");
			} else if (f && suffix != "K") {
				PrintErrorAndDie("Invalid cache size format: Expected bytes ", suffix);
			} else if (suffix == "K") {
				info.size *= 1024;
			}
		}
		if (!ReadFromFile(StrCat(f_path, "type"), &info.type)) {
			PrintErrorAndDie("Failed to read from file ", f_path, "type");
		}
		if (!ReadFromFile(StrCat(f_path, "level"), &info.level)) {
			PrintErrorAndDie("Failed to read from file ", f_path, "level");
		}
		std::string map_str;
		if (!ReadFromFile(StrCat(f_path, "shared_cpu_map"), &map_str)) {
			PrintErrorAndDie("Failed to read from file ", f_path, "shared_cpu_map");
		}
		info.num_sharing = CountSetBitsInCPUMap(map_str);
		res.push_back(info);
	}

	return res;
}

#ifdef BENCHMARK_OS_MACOSX
std::vector<CPUInfo::CacheInfo> GetCacheSizesMacOSX() {
	std::vector<CPUInfo::CacheInfo> res;
	std::array<uint64_t, 4>         cache_counts {{0, 0, 0, 0}};
	GetSysctl("hw.cacheconfig", &cache_counts);

	struct {
		std::string name;
		std::string type;
		int         level;
		uint64_t    num_sharing;
	} Cases[] = {{"hw.l1dcachesize", "Data", 1, cache_counts[1]},
	             {"hw.l1icachesize", "Instruction", 1, cache_counts[1]},
	             {"hw.l2cachesize", "Unified", 2, cache_counts[2]},
	             {"hw.l3cachesize", "Unified", 3, cache_counts[3]}};
	for (auto& c : Cases) {
		int val;
		if (!GetSysctl(c.name, &val)) { continue; }
		CPUInfo::CacheInfo info;
		info.type        = c.type;
		info.level       = c.level;
		info.size        = val;
		info.num_sharing = static_cast<int>(c.num_sharing);
		res.push_back(std::move(info));
	}
	return res;
}
#elif defined(BENCHMARK_OS_WINDOWS)
std::vector<CPUInfo::CacheInfo> GetCacheSizesWindows() {
	std::vector<CPUInfo::CacheInfo> res;
	DWORD buffer_size = 0;
	using PInfo = SYSTEM_LOGICAL_PROCESSOR_INFORMATION;
	using CInfo = CACHE_DESCRIPTOR;

	using UPtr = std::unique_ptr<PInfo, decltype(&std::free)>;
	GetLogicalProcessorInformation(nullptr, &buffer_size);
	UPtr buff((PInfo*)malloc(buffer_size), &std::free);
	if (!GetLogicalProcessorInformation(buff.get(), &buffer_size))
		PrintErrorAndDie("Failed during call to GetLogicalProcessorInformation: ", GetLastError());

	PInfo* it = buff.get();
	PInfo* end = buff.get() + (buffer_size / sizeof(PInfo));

	for (; it != end; ++it) {
		if (it->Relationship != RelationCache) { continue; }
		using BitSet = std::bitset<sizeof(ULONG_PTR) * CHAR_BIT>;
		BitSet B(it->ProcessorMask);
		// To prevent duplicates, only consider caches where CPU 0 is specified
		if (!B.test(0)) { continue; }
		CInfo* Cache = &it->Cache;
		CPUInfo::CacheInfo C;
		C.num_sharing = static_cast<int>(B.count());
		C.level = Cache->Level;
		C.size = Cache->Size;
		switch (Cache->Type) {
		case CacheUnified:
			C.type = "Unified";
			break;
		case CacheInstruction:
			C.type = "Instruction";
			break;
		case CacheData:
			C.type = "Data";
			break;
		case CacheTrace:
			C.type = "Trace";
			break;
		default:
			C.type = "Unknown";
			break;
		}
		res.push_back(C);
	}
	return res;
}
#elif BENCHMARK_OS_QNX
std::vector<CPUInfo::CacheInfo> GetCacheSizesQNX() {
	std::vector<CPUInfo::CacheInfo> res;
	struct cacheattr_entry* cache = SYSPAGE_ENTRY(cacheattr);
	uint32_t const elsize = SYSPAGE_ELEMENT_SIZE(cacheattr);
	int num = SYSPAGE_ENTRY_SIZE(cacheattr) / elsize;
	for (int i = 0; i < num; ++i) {
		CPUInfo::CacheInfo info;
		switch (cache->flags) {
		case CACHE_FLAG_INSTR:
			info.type = "Instruction";
			info.level = 1;
			break;
		case CACHE_FLAG_DATA:
			info.type = "Data";
			info.level = 1;
			break;
		case CACHE_FLAG_UNIFIED:
			info.type = "Unified";
			info.level = 2;
			break;
		case CACHE_FLAG_SHARED:
			info.type = "Shared";
			info.level = 3;
			break;
		default:
			continue;
			break;
		}
		info.size = cache->line_size * cache->num_lines;
		info.num_sharing = 0;
		res.push_back(std::move(info));
		cache = SYSPAGE_ARRAY_ADJ_OFFSET(cacheattr, cache, elsize);
	}
	return res;
}
#endif

static std::vector<CPUInfo::CacheInfo> GetCacheSizes() {
#ifdef BENCHMARK_OS_MACOSX
	return GetCacheSizesMacOSX();
#elif defined(BENCHMARK_OS_WINDOWS)
	return GetCacheSizesWindows();
#elif defined(BENCHMARK_OS_QNX)
	return GetCacheSizesQNX();
#else
	return GetCacheSizesFromKVFS();
#endif
}

FLS_BENCH_MAYBE_UNUSED std::string GetSystemName() {
#if defined(BENCHMARK_OS_WINDOWS)
	std::string    str;
	const unsigned COUNT           = MAX_COMPUTERNAME_LENGTH + 1;
	TCHAR          hostname[COUNT] = {'\0'};
	DWORD          DWCOUNT         = COUNT;
	if (!GetComputerName(hostname, &DWCOUNT)) { return std::string(""); }
#ifndef UNICODE
	str = std::string(hostname, DWCOUNT);
#else
	// Using wstring_convert, Is deprecated in C++17
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::wstring                                wStr(hostname, DWCOUNT);
	str = converter.to_bytes(wStr);
#endif
	return str;
#else // defined(BENCHMARK_OS_WINDOWS)
#ifndef HOST_NAME_MAX
#ifdef BENCHMARK_HAS_SYSCTL // BSD/Mac Doesnt have HOST_NAME_MAX defined
#define HOST_NAME_MAX 64
#elif defined(BENCHMARK_OS_NACL)
#define HOST_NAME_MAX 64
#elif defined(BENCHMARK_OS_QNX)
#define HOST_NAME_MAX 154
#elif defined(BENCHMARK_OS_RTEMS)
#define HOST_NAME_MAX 256
#else
#warning "HOST_NAME_MAX not defined. using 64"
#define HOST_NAME_MAX 64
#endif
#endif // def HOST_NAME_MAX
	char hostname[HOST_NAME_MAX];
	int retVal = gethostname(hostname, HOST_NAME_MAX);
	if (retVal != 0) { return std::string(""); }
	return std::string(hostname);
#endif // Catch-all POSIX block.
}

static int GetNumCPUs() {
#ifdef BENCHMARK_HAS_SYSCTL
	int NumCPU = -1;
	if (GetSysctl("hw.ncpu", &NumCPU)) { return NumCPU; }
	fprintf(stderr, "Err: %s\n", strerror(errno));
	std::exit(EXIT_FAILURE);
#elif defined(BENCHMARK_OS_WINDOWS)
	SYSTEM_INFO sysinfo;
	// Use memset as opposed to = {} to avoid GCC missing initializer false
	// positives.
	std::memset(&sysinfo, 0, sizeof(SYSTEM_INFO));
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors; // number of logical
	// processors in the current
	// group
#elif defined(BENCHMARK_OS_SOLARIS)
	// Returns -1 in case of a failure.
	int NumCPU = sysconf(_SC_NPROCESSORS_ONLN);
	if (NumCPU < 0) { fprintf(stderr, "sysconf(_SC_NPROCESSORS_ONLN) failed with error: %s\n", strerror(errno)); }
	return NumCPU;
#elif defined(BENCHMARK_OS_QNX)
	return static_cast<int>(_syspage_ptr->num_cpu);
#else
	int           NumCPUs = 0;
	int           MaxID   = -1;
	std::ifstream f("/proc/cpuinfo");
	if (!f.is_open()) {
		std::cerr << "failed to open /proc/cpuinfo\n";
		return -1;
	}
	const std::string Key = "processor";
	std::string       ln;
	while (std::getline(f, ln)) {
		if (ln.empty()) { continue; }
		size_t      SplitIdx = ln.find(':');
		std::string value;
#if defined(__s390__)
		// s390 has another format in /proc/cpuinfo
		// it needs to be parsed differently
		if (SplitIdx != std::string::npos) { value = ln.substr(Key.size() + 1, SplitIdx - Key.size() - 1); }
#else
		if (SplitIdx != std::string::npos) { value = ln.substr(SplitIdx + 1); }
#endif
		if (ln.size() >= Key.size() && ln.compare(0, Key.size(), Key) == 0) {
			NumCPUs++;
			if (!value.empty()) {
				int CurID = benchmark::stoi(value);
				MaxID     = std::max(CurID, MaxID);
			}
		}
	}
	if (f.bad()) {
		std::cerr << "Failure reading /proc/cpuinfo\n";
		return -1;
	}
	if (!f.eof()) {
		std::cerr << "Failed to read to end of /proc/cpuinfo\n";
		return -1;
	}
	f.close();

	if ((MaxID + 1) != NumCPUs) {
		fprintf(stderr,
		        "CPU ID assignments in /proc/cpuinfo seem messed up."
		        " This is usually caused by a bad BIOS.\n");
	}
	return NumCPUs;
#endif
	BENCHMARK_UNREACHABLE();
}

static double GetCPUCyclesPerSecond(CPUInfo::Scaling scaling) {
	// Currently, scaling is only used on linux path here,
	// suppress diagnostics about it being unused on other paths.
	(void)scaling;

#if defined BENCHMARK_OS_LINUX || defined BENCHMARK_OS_CYGWIN
	long freq;

	// If the kernel is exporting the tsc frequency use that. There are issues
	// where cpuinfo_max_freq cannot be relied on because the BIOS may be
	// exporintg an invalid p-state (on x86) or p-states may be used to put the
	// processor in a new mode (turbo mode). Essentially, those frequencies
	// cannot always be relied upon. The same reasons apply to /proc/cpuinfo as
	// well.
	if (ReadFromFile("/sys/devices/system/cpu/cpu0/tsc_freq_khz", &freq)
	    // If CPU scaling is disabled, use the the *current* frequency.
	    // Note that we specifically don't want to read cpuinfo_cur_freq,
	    // because it is only readable by root.
	    || (scaling == CPUInfo::Scaling::DISABLED &&
	        ReadFromFile("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq", &freq))
	    // Otherwise, if CPU scaling may be in effect, we want to use
	    // the *maximum* frequency, not whatever CPU speed some random processor
	    // happens to be using now.
	    || ReadFromFile("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", &freq)) {
		// The value is in kHz (as the file name suggests).  For example, on a
		// 2GHz warpstation, the file contains the value "2000000".
		return freq * 1000.0;
	}

	const double error_value = -1;
	double       bogo_clock  = error_value;

	std::ifstream f("/proc/cpuinfo");
	if (!f.is_open()) {
		std::cerr << "failed to open /proc/cpuinfo\n";
		return error_value;
	}

	auto startsWithKey = [](std::string const& Value, std::string const& Key) {
		if (Key.size() > Value.size()) { return false; }
		auto Cmp = [&](char X, char Y) {
			return std::tolower(X) == std::tolower(Y);
		};
		return std::equal(Key.begin(), Key.end(), Value.begin(), Cmp);
	};

	std::string ln;
	while (std::getline(f, ln)) {
		if (ln.empty()) { continue; }
		size_t      SplitIdx = ln.find(':');
		std::string value;
		if (SplitIdx != std::string::npos) { value = ln.substr(SplitIdx + 1); }
		// When parsing the "cpu MHz" and "bogomips" (fallback) entries, we only
		// accept positive values. Some environments (virtual machines) report zero,
		// which would cause infinite looping in WallTime_Init.
		if (startsWithKey(ln, "cpu MHz")) {
			if (!value.empty()) {
				double cycles_per_second = benchmark::stod(value) * 1000000.0;
				if (cycles_per_second > 0) { return cycles_per_second; }
			}
		} else if (startsWithKey(ln, "bogomips")) {
			if (!value.empty()) {
				bogo_clock = benchmark::stod(value) * 1000000.0;
				if (bogo_clock < 0.0) { bogo_clock = error_value; }
			}
		}
	}
	if (f.bad()) {
		std::cerr << "Failure reading /proc/cpuinfo\n";
		return error_value;
	}
	if (!f.eof()) {
		std::cerr << "Failed to read to end of /proc/cpuinfo\n";
		return error_value;
	}
	f.close();
	// If we found the bogomips clock, but nothing better, we'll use it (but
	// we're not happy about it); otherwise, fallback to the rough estimation
	// below.
	if (bogo_clock >= 0.0) { return bogo_clock; }

#elif defined BENCHMARK_HAS_SYSCTL
	constexpr auto* FreqStr =
#if defined(BENCHMARK_OS_FREEBSD) || defined(BENCHMARK_OS_NETBSD)
	    "machdep.tsc_freq";
#elif defined BENCHMARK_OS_OPENBSD
	    "hw.cpuspeed";
#elif defined BENCHMARK_OS_DRAGONFLY
	    "hw.tsc_frequency";
#else
	    "hw.cpufrequency";
#endif
	unsigned long long hz = 0;
#if defined BENCHMARK_OS_OPENBSD
	if (GetSysctl(FreqStr, &hz)) { return hz * 1000000; }
#else
	if (GetSysctl(FreqStr, &hz)) { return hz; }
#endif
	fprintf(stderr, "Unable to determine clock rate from sysctl: %s: %s\n", FreqStr, strerror(errno));

#elif defined BENCHMARK_OS_WINDOWS
	// In NT, read MHz from the registry. If we fail to do so or we're in win9x
	// then make a crude estimate.
	DWORD data, data_size = sizeof(data);
	if (IsWindowsXPOrGreater() && SUCCEEDED(SHGetValueA(HKEY_LOCAL_MACHINE,
	                                                    "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
	                                                    "~MHz",
	                                                    nullptr,
	                                                    &data,
	                                                    &data_size)))
		return static_cast<double>((int64_t)data * (int64_t)(1000 * 1000)); // was mhz
#elif defined(BENCHMARK_OS_SOLARIS)
	kstat_ctl_t* kc = kstat_open();
	if (!kc) {
		std::cerr << "failed to open /dev/kstat\n";
		return -1;
	}
	kstat_t* ksp = kstat_lookup(kc, (char*)"cpu_info", -1, (char*)"cpu_info0");
	if (!ksp) {
		std::cerr << "failed to lookup in /dev/kstat\n";
		return -1;
	}
	if (kstat_read(kc, ksp, NULL) < 0) {
		std::cerr << "failed to read from /dev/kstat\n";
		return -1;
	}
	kstat_named_t* knp = (kstat_named_t*)kstat_data_lookup(ksp, (char*)"current_clock_Hz");
	if (!knp) {
		std::cerr << "failed to lookup data in /dev/kstat\n";
		return -1;
	}
	if (knp->data_type != KSTAT_DATA_UINT64) {
		std::cerr << "current_clock_Hz is of unexpected data type: " << knp->data_type << "\n";
		return -1;
	}
	double clock_hz = knp->value.ui64;
	kstat_close(kc);
	return clock_hz;
#elif defined(BENCHMARK_OS_QNX)
	return static_cast<double>((int64_t)(SYSPAGE_ENTRY(cpuinfo)->speed) * (int64_t)(1000 * 1000));
#endif
	// If we've fallen through, attempt to roughly estimate the CPU clock rate.
	const int estimate_time_ms = 1000;
	cycleclock::Init();
	const auto start_ticks = cycleclock::Now();
	SleepForMilliseconds(estimate_time_ms);
	return static_cast<double>(cycleclock::Now() - start_ticks);
}

static std::vector<double> GetLoadAvg() {
#if (defined BENCHMARK_OS_FREEBSD || defined(BENCHMARK_OS_LINUX) || defined BENCHMARK_OS_MACOSX ||                     \
     defined BENCHMARK_OS_NETBSD || defined BENCHMARK_OS_OPENBSD || defined BENCHMARK_OS_DRAGONFLY) &&                 \
    !defined(__ANDROID__)
	constexpr int       kMaxSamples = 3;
	std::vector<double> res(kMaxSamples, 0.0);
	const int           nelem = getloadavg(res.data(), kMaxSamples);
	if (nelem < 1) {
		res.clear();
	} else {
		res.resize(nelem);
	}
	return res;
#else
	return {};
#endif
}

// private constructor
CPUInfo::CPUInfo()
    : num_cpus(GetNumCPUs())
    , scaling(CpuScaling(num_cpus))
    , cycles_per_second(GetCPUCyclesPerSecond(scaling))
    , caches(GetCacheSizes())
    , load_avg(GetLoadAvg()) {}

struct SystemInfo {

	static std::string GetSystemName() {
#if defined(BENCHMARK_OS_WINDOWS)
		std::string    str;
		const unsigned COUNT           = MAX_COMPUTERNAME_LENGTH + 1;
		TCHAR          hostname[COUNT] = {'\0'};
		DWORD          DWCOUNT         = COUNT;
		if (!GetComputerName(hostname, &DWCOUNT)) { return std::string(""); }
#ifndef UNICODE
		str = std::string(hostname, DWCOUNT);
#else
		// Using wstring_convert, Is deprecated in C++17
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::wstring                                wStr(hostname, DWCOUNT);
		str = converter.to_bytes(wStr);
#endif
		return str;
#else // defined(BENCHMARK_OS_WINDOWS)
#ifndef HOST_NAME_MAX
#ifdef BENCHMARK_HAS_SYSCTL // BSD/Mac Doesnt have HOST_NAME_MAX defined
#define HOST_NAME_MAX 64
#elif defined(BENCHMARK_OS_NACL)
#define HOST_NAME_MAX 64
#elif defined(BENCHMARK_OS_QNX)
#define HOST_NAME_MAX 154
#elif defined(BENCHMARK_OS_RTEMS)
#define HOST_NAME_MAX 256
#else
#warning "HOST_NAME_MAX not defined. using 64"
#define HOST_NAME_MAX 64
#endif
#endif // def HOST_NAME_MAX
		char hostname[HOST_NAME_MAX];
		int ret_val = gethostname(hostname, HOST_NAME_MAX);
		if (ret_val != 0) { return std::string(""); }
		return {hostname};
#endif // Catch-all POSIX block.
	}

	static const SystemInfo& getInstance() {
		static const SystemInfo INFO;
		return INFO;
	}

private:
	SystemInfo()
	    : m_name(GetSystemName()) {}

public:
	const std::string& getName() const { return m_name; }

private:
	std::string m_name;

	BENCHMARK_DISALLOW_COPY_AND_ASSIGN(SystemInfo);
};

static std::string LocalDateTimeString() {
	// Write the local time in RFC3339 format yyyy-mm-ddTHH:MM:SS+/-HH:MM.
	using Clock                     = std::chrono::system_clock;
	std::time_t       now           = Clock::to_time_t(Clock::now());
	const std::size_t kTzOffsetLen  = 6;
	const std::size_t kTimestampLen = 19;

	std::size_t tz_len;
	std::size_t timestamp_len;
	long int    offset_minutes;
	char        tz_offset_sign = '+';
	// tz_offset is set in one of three ways:
	// * strftime with %z - This either returns empty or the ISO 8601 time.  The
	// maximum length an
	//   ISO 8601 string can be is 7 (e.g. -03:30, plus trailing zero).
	// * snprintf with %c%02li:%02li - The maximum length is 41 (one for %c, up to
	// 19 for %02li,
	//   one for :, up to 19 %02li, plus trailing zero).
	// * A fixed string of "-00:00".  The maximum length is 7 (-00:00, plus
	// trailing zero).
	//
	// Thus, the maximum size this needs to be is 41.
	char tz_offset[41];
	// Long enough buffer to avoid format-overflow warnings
	char storage[128];

#if defined(BENCHMARK_OS_WINDOWS)
	std::tm* timeinfo_p = ::localtime(&now);
#else
	std::tm timeinfo;
	std::tm* timeinfo_p = &timeinfo;
	::localtime_r(&now, &timeinfo);
#endif

	tz_len = std::strftime(tz_offset, sizeof(tz_offset), "%z", timeinfo_p);

	if (tz_len < kTzOffsetLen && tz_len > 1) {
		// Timezone offset was written. strftime writes offset as +HHMM or -HHMM,
		// RFC3339 specifies an offset as +HH:MM or -HH:MM. To convert, we parse
		// the offset as an integer, then reprint it to a string.

		offset_minutes = ::strtol(tz_offset, NULL, 10);
		if (offset_minutes < 0) {
			offset_minutes *= -1;
			tz_offset_sign = '-';
		}

		tz_len = ::snprintf(
		    tz_offset, sizeof(tz_offset), "%c%02li:%02li", tz_offset_sign, offset_minutes / 100, offset_minutes % 100);
		((void)tz_len); // Prevent unused variable warning in optimized build.
	} else {
		// Unknown offset. RFC3339 specifies that unknown local offsets should be
		// written as UTC time with -00:00 timezone.
#if defined(BENCHMARK_OS_WINDOWS)
		// Potential race condition if another thread calls localtime or gmtime.
		timeinfo_p = ::gmtime(&now);
#else
		::gmtime_r(&now, &timeinfo);
#endif

		strncpy(tz_offset, "-00:00", kTzOffsetLen + 1);
	}

	timestamp_len = std::strftime(storage, sizeof(storage), "%Y-%m-%dT%H:%M:%S", timeinfo_p);
	// Prevent unused variable warning in optimized build.
	((void)kTimestampLen);

	std::strncat(storage, tz_offset, sizeof(storage) - timestamp_len - 1);
	return {storage};
}

class CPUInfo;
struct SystemInfo;
class BenchmarkReporter {
public:
	struct Context {
		CPUInfo const&    cpu_info;
		SystemInfo const& sys_info;
		// The number of chars in the longest benchmark name.
		size_t name_field_width;

		Context()
		    : cpu_info(CPUInfo::getInstance())
		    , sys_info(SystemInfo::getInstance()) {}
	};

	class Run {
	public:
		static const int64_t no_repetition_index = -1;
		enum RunType { RT_Iteration, RT_Aggregate };

		explicit Run(int benchmark_number, std::string& name, uint64_t iterations, double cycles_per_tuple)
		    : benchmark_number(benchmark_number)
		    , name(name)
		    , iterations(iterations)
		    , cycles_per_tuple(cycles_per_tuple)
		//                      time_unit(kNanosecond),
		//                      real_accumulated_time(0),
		//                      cpu_accumulated_time(0),
		//                      max_heapbytes_used(0),
		//                      complexity(oNone),
		//                      complexity_lambda(),
		//                      complexity_n(0),
		//                      report_big_o(false),
		//                      report_rms(false),
		//                      counters(),
		//                      has_memory_result(false),
		//                      allocs_per_iter(0.0),
		//                      max_bytes_used(0)
		{}

		std::string benchmark_name() const;
		int         benchmark_number;
		std::string name;
		uint64_t    iterations;
		RunType     run_type;
		std::string aggregate_name;
		bool        error_occurred;
		std::string error_message;

		//            TimeUnit time_unit;
		double cycles_per_tuple;

		// Memory metrics.
		bool    has_memory_result;
		double  allocs_per_iter;
		int64_t max_bytes_used;
	};

	// Construct a BenchmarkReporter with the output stream set to 'std::cout'
	// and the error stream set to 'std::cerr'
	BenchmarkReporter()
	    : output_stream_(&std::cout)
	    , error_stream_(&std::cerr) {}

	// Called once for every suite of benchmarks run.
	// The parameter "context" contains information that the
	// reporter may wish to use when generating its report, for example the
	// platform under which the benchmarks are running. The benchmark run is
	// never started if this function returns false, allowing the reporter
	// to skip runs based on the context information.
	virtual bool ReportContext(const Context& context) = 0;

	// Called once for each group of benchmark runs, gives information about
	// cpu-time and heap memory usage during the benchmark run. If the group
	// of runs contained more than two entries then 'report' contains additional
	// elements representing the mean and standard deviation of those runs.
	// Additionally if this group of runs was the last in a family of benchmarks
	// 'reports' contains additional entries representing the asymptotic
	// complexity and RMS of that benchmark family.
	virtual void ReportRuns(std::vector<Run>& report) = 0;

	// Called once and only once after ever group of benchmarks is run and
	// reported.
	virtual void Finalize() {}

	// REQUIRES: The object referenced by 'out' is valid for the lifetime
	// of the reporter.
	void SetOutputStream(std::ostream* out) {
		assert(out);
		output_stream_ = out;
	}

	// REQUIRES: The object referenced by 'err' is valid for the lifetime
	// of the reporter.
	void SetErrorStream(std::ostream* err) {
		assert(err);
		error_stream_ = err;
	}

	static std::ostream& GetOutputStream() { return std::cout; }

	static std::ostream& GetErrorStream() { return std::cerr; }

	virtual ~BenchmarkReporter();

	// Write a human readable string to 'out' representing the specified
	// 'context'.
	// REQUIRES: 'out' is non-null.
	static void PrintBasicContext(std::ostream& out, Context const& context) {
		//  CHECK(out) << "cannot be null";
		auto& Out = out;

		Out << LocalDateTimeString() << "\n";

		const CPUInfo& info = context.cpu_info;
		Out << "Run on (" << info.num_cpus << " X " << (info.cycles_per_second / 1000000.0) << " MHz CPU "
		    << ((info.num_cpus > 1) ? "s" : "") << ")\n";
		if (info.caches.size() != 0) {
			Out << "CPU Caches:\n";
			for (auto& CInfo : info.caches) {
				Out << "  L" << CInfo.level << " " << CInfo.type << " " << (CInfo.size / 1024) << " KiB";
				if (CInfo.num_sharing != 0) { Out << " (x" << (info.num_cpus / CInfo.num_sharing) << ")"; }
				Out << "\n";
			}
		}
		if (!info.load_avg.empty()) {
			Out << "Load Average: ";
			for (auto It = info.load_avg.begin(); It != info.load_avg.end();) {
				Out << StrFormat("%.2f", *It++);
				if (It != info.load_avg.end()) { Out << ", "; }
			}
			Out << "\n";
		}

		if (CPUInfo::Scaling::ENABLED == info.scaling) {
			Out << "***WARNING*** CPU scaling is enabled, the benchmark "
			       "real time measurements may be noisy and will incur extra "
			       "overhead.\n";
		}

#ifndef NDEBUG
		Out << "***WARNING*** Library was built as DEBUG. Timings may be "
		       "affected.\n";
#endif
	}

private:
	std::ostream* output_stream_;
	std::ostream* error_stream_;
};

// https://github.com/emscripten-core/emscripten/wiki/Emterpreter or use node.js
// https://stackoverflow.com/questions/32573289/text-written-to-stdout-doesnt-appear-until-program-completion
static void printRun(std::ostream& out, benchmark::BenchmarkReporter::Run& run) {
	out << run.benchmark_number << ",";
	out << run.name << ",";
	out << run.iterations << ",";
	out << run.cycles_per_tuple;
	out << '\n';
}

FLS_BENCH_MAYBE_UNUSED static std::string CsvEscape(const std::string& s) {
	std::string tmp;
	tmp.reserve(s.size() + 2);
	for (char c : s) {
		switch (c) {
		case '"':
			tmp += "\"\"";
			break;
		default:
			tmp += c;
			break;
		}
	}
	return '"' + tmp + '"';
}

static void printHeader(std::ostream& out) {
	out << "benchmark_number,";
	out << "name,";
	out << "iterations,";
	out << "cycles_per_tuple";
	out << "\n";
}

class CSVReporter : public BenchmarkReporter {
public:
	explicit CSVReporter(std::string path)
	    : path(std::move(path))
	    , printed_header(false) {}
	bool ReportContext(const Context& context) override {
		PrintBasicContext(GetErrorStream(), context);
		return true;
	}
	static void PrintContext() { PrintBasicContext(GetErrorStream(), benchmark::BenchmarkReporter::Context()); }
	static void WriteRuns(std::vector<Run>& reports, const std::string& path) {
#ifdef BENCHMARK_OS_EMSCRIPTEN
		// alternatives :
		// https://stackoverflow.com/questions/67174663/cannot-save-the-file-to-specific-directory-by-wasm
		std::cerr << "Modern web browsers do not allow web pages to write/open a local file in your machine.";
#else
		std::fstream file;
		file.open(path, std::fstream::out);
		printHeader(file);

		// print results for each run
		for (auto& run : reports) {
			printRun(file, run);
		}

		if (file.fail()) {
			std::cerr << "Error: " << strerror(errno) << ": " << path << "\n";
			throw std::exception();
		}

		std::cout << "benchmark result has been writen at " << path << '\n';
#endif
	}
	static void WriteContext(std::string& cmake_info, const std::string& path) {
#ifdef BENCHMARK_OS_EMSCRIPTEN
		// alternatives :
		// https://stackoverflow.com/questions/67174663/cannot-save-the-file-to-specific-directory-by-wasm
		std::cerr << "Modern web browsers do not allow web pages to write/open a local file in your machine.";
#else
		std::fstream file;
		file.open(path, std::fstream::out);
		PrintBasicContext(file, benchmark::BenchmarkReporter::Context());
		file << cmake_info;
		if (file.fail()) {
			std::cerr << "Error: " << strerror(errno) << ": " << path << "\n";
			throw std::exception();
		}

		std::cout << "benchmark metadata has been writen at " << path << '\n';
#endif
	}
	static void PrintRun(Run& run) {
		std::ostream& out = GetOutputStream();
		printRun(out, run);
	}

public:
	const std::string     path;
	bool                  printed_header;
	std::set<std::string> user_counter_names;
};

using report = benchmark::BenchmarkReporter::Run;

class Benchmark {
private:
	explicit Benchmark(std::string name)
	    : m_name(std::move(name))
	    , m_cpu_info(CPUInfo::getInstance())
	    , m_system_info(SystemInfo::getInstance())
	    , m_enable_print(false)
	    , m_result_file {' '}
	    , m_metadata_file {' '} {} //
public:
	friend class BenchmarkBuilder;
	void Run(benchmark::BenchmarkReporter::Run run) {
		if (m_enable_print) { benchmark::CSVReporter::PrintRun(run); }

		m_runs.push_back(run);
	}
	~Benchmark() {
		if (m_enable_save && !m_runs.empty()) {
			CSVReporter::WriteRuns(m_runs, m_result_file);
			CSVReporter::WriteContext(m_extra_info, m_metadata_file);
		}
	} //
private:
	std::string                                    m_name;
	const CPUInfo&                                 m_cpu_info;
	const SystemInfo&                              m_system_info;
	std::string                                    m_extra_info;
	bool                                           m_enable_save;
	bool                                           m_enable_print;
	std::string                                    m_result_file;
	std::string                                    m_metadata_file;
	std::string                                    m_dir;
	std::vector<benchmark::BenchmarkReporter::Run> m_runs;
};

class CmakeInfo;
constexpr auto METADATA_PREFIX {".metadata"};
constexpr auto CSV_PREFIX {".csv"};

class BenchmarkBuilder {
public:
	explicit BenchmarkBuilder(std::string name)
	    : m_benchmark(std::move(name)) {} //
public:
	                             operator Benchmark() const { return m_benchmark; }
	benchmark::BenchmarkBuilder& save() {
		m_benchmark.m_metadata_file = "./" + m_benchmark.m_metadata_file + METADATA_PREFIX;
		m_benchmark.m_result_file   = "./" + m_benchmark.m_metadata_file + CSV_PREFIX;
		m_benchmark.m_enable_print  = true;
		return *this;
	}
	benchmark::BenchmarkBuilder& print() {
		m_benchmark.m_enable_save = true;
		return *this;
	}
	benchmark::BenchmarkBuilder& at(const std::string& dir) {
		m_benchmark.m_metadata_file = dir + "/" + m_benchmark.m_name + METADATA_PREFIX;
		m_benchmark.m_result_file   = dir + "/" + m_benchmark.m_name + CSV_PREFIX;
		return *this;
	}
	benchmark::BenchmarkBuilder& add_extra_info(const std::string& info) {
		m_benchmark.m_extra_info += info;
		return *this;
	}

private:
	Benchmark m_benchmark; //
};

FLS_BENCH_MAYBE_UNUSED static BenchmarkBuilder create(const std::string& name) {
	cycleclock::Init();
	return BenchmarkBuilder(name);
}

class CmakeInfo {
public:
	static const CmakeInfo& getInstance() {
		static const CmakeInfo INFO;
		return INFO;
	}

public:
	const std::string source_dir                  = SOURCE_DIR;
	const std::string cmake_osx_architectures     = CMAKE_OSX_ARCHITECTURES;
	const std::string cmake_host_system_processor = CMAKE_HOST_SYSTEM_PROCESSOR;
	const std::string cmake_system_processor      = CMAKE_SYSTEM_PROCESSOR;
	const std::string cmake_host_system_name      = CMAKE_HOST_SYSTEM_NAME;
	const std::string cmake_system_name           = CMAKE_SYSTEM_NAME;
	const std::string cmake_c_compiler            = CMAKE_C_COMPILER;
	const std::string cmake_cxx_compiler          = CMAKE_CXX_COMPILER;
	const std::string cmake_cxx_compiler_id       = CMAKE_CXX_COMPILER_ID;
	const std::string cmake_cxx_compiler_version  = CMAKE_CXX_COMPILER_VERSION;
	const std::string cmake_crosscompiling        = CMAKE_CROSSCOMPILING;
	const std::string cmake_cxx_flags_debug       = CMAKE_CXX_FLAGS_DEBUG;
	const std::string cmake_cxx_flags_release     = CMAKE_CXX_FLAGS_RELEASE;
	const std::string cmake_build_type            = CMAKE_BUILD_TYPE;
	const std::string cmake_toolchain_file        = CMAKE_TOOLCHAIN_FILE;
	const std::string target_name                 = TARGET_NAME;
	const std::string target_compile_options      = TARGET_COMPILE_OPTIONS;

public:
	const std::string& getSourceDir() const { return source_dir; }
	const std::string& getCmakeOsxArchitectures() const { return cmake_osx_architectures; }
	const std::string& getCmakeHostSystemProcessor() const { return cmake_host_system_processor; }
	const std::string& getCmakeSystemProcessor() const { return cmake_system_processor; }
	const std::string& getCmakeHostSystemName() const { return cmake_host_system_name; }
	const std::string& getCmakeSystemName() const { return cmake_system_name; }
	const std::string& getCmakeCCompiler() const { return cmake_c_compiler; }
	const std::string& getCmakeCxxCompiler() const { return cmake_cxx_compiler; }
	const std::string& getCmakeCxxCompilerId() const { return cmake_cxx_compiler_id; }
	const std::string& getCmakeCxxCompilerVersion() const { return cmake_cxx_compiler_version; }
	const std::string& getCmakeCrosscompiling() const { return cmake_crosscompiling; }
	const std::string& getCmakeCxxFlagsDebug() const { return cmake_cxx_flags_debug; }
	const std::string& getCmakeCxxFlagsRelease() const { return cmake_cxx_flags_release; }
	const std::string& getCmakeBuildType() const { return cmake_build_type; }
	const std::string& get_cmakeToolchainFile() const { return cmake_toolchain_file; }
	const std::string& getTargetName() const { return target_name; }
	const std::string& getTargetCompileOptions() const { return target_compile_options; }

	static void PrintCmake() { printCmakeInfo(std::cout); }
	static void AppendCmake(const std::string& path) {
		std::fstream file;
		file.open(path, std::fstream::app);
		printCmakeInfo(file);

		if (file.fail()) {
			std::cerr << "Error: " << strerror(errno) << "\n";
			throw std::exception();
		}

		std::cout << "result has been writen at " + path;
	}
	static void printCmakeInfo(std::ostream& out) {
		const CmakeInfo& info = getInstance();
		out << info.getCmakeInfo();
	}

	// https://stackoverflow.com/a/46931770/5165633
	static std::vector<std::string> split(const std::string& s, char delim) {
		std::vector<std::string> result;
		std::stringstream        ss(s);
		std::string              item;

		while (getline(ss, item, delim)) {
			result.push_back(item);
		}

		return result;
	}

	static std::string getCmakeToolchainFile() {
		const CmakeInfo&         info = getInstance();
		std::vector<std::string> v    = split(info.get_cmakeToolchainFile(), '/');

		auto tool_chain_file_str = v[v.size() - 1];
		return tool_chain_file_str.substr(0, tool_chain_file_str.size() - 6);
	}

	static std::string getCmakeInfo() {
		std::ostringstream out;
		const CmakeInfo&   info = getInstance();
		out << "cmake info: \n";
		out << "    source_dir: " << info.getSourceDir() << '\n';
		out << "    cmake_osx_architectures" << info.getCmakeOsxArchitectures() << '\n';
		out << "    cmake_host_system_processor: " << info.getCmakeHostSystemProcessor() << '\n';
		out << "    cmake_system_processor: " << info.getCmakeSystemProcessor() << '\n';
		out << "    cmake_host_system_name: " << info.getCmakeHostSystemName() << '\n';
		out << "    cmake_system_name: " << info.getCmakeSystemName() << '\n';
		out << "    cmake_c_compiler: " << info.getCmakeCCompiler() << '\n';
		out << "    cmake_cxx_compiler: " << info.getCmakeCxxCompiler() << '\n';
		out << "    cmake_cxx_compiler_id: " << info.getCmakeCxxCompilerId() << '\n';
		out << "    cmake_cxx_compiler_version: " << info.getCmakeCxxCompilerVersion() << '\n';
		out << "    cmake_crosscompiling: " << info.getCmakeCrosscompiling() << '\n';
		out << "    cmake_cxx_flags_debug: " << info.getCmakeCxxFlagsDebug() << '\n';
		out << "    cmake_cxx_flags_release: " << info.getCmakeCxxFlagsRelease() << '\n';
		out << "    cmake_build_type: " << info.getCmakeBuildType() << '\n';
		out << "    cmake_toolchain_file: " << info.getCmakeToolchainFile() << '\n';
		out << "target info: \n";
		out << "    target_name: " << info.getTargetName() << '\n';
		out << "    target_compile_options: " << info.getTargetCompileOptions() << '\n';
		return out.str();
	}

private:
	CmakeInfo() = default;                         //
	BENCHMARK_DISALLOW_COPY_AND_ASSIGN(CmakeInfo); //
};
} // namespace benchmark
#endif
