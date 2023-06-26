#include "common/Compat.hpp"
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#ifdef __linux__
#include <asm/unistd.h>
#include <linux/perf_event.h>
extern "C" {
#include "jevents.h"
}
#endif

#define GLOBAL 1

extern bool writeHeader;

struct PerfEvents {
	const size_t printFieldWidth = 10;
	size_t       counters;

#ifdef __linux__
	struct read_format {
		uint64_t value        = 0; /* The value of the event */
		uint64_t time_enabled = 0; /* if PERF_FORMAT_TOTAL_TIME_ENABLED */
		uint64_t time_running = 0; /* if PERF_FORMAT_TOTAL_TIME_RUNNING */
		uint64_t id           = 0; /* if PERF_FORMAT_ID */
	};
#endif
	struct event {
#ifdef __linux__
		struct perf_event_attr pe;
		int                    fd;
		read_format            prev;
		read_format            data;
#endif
		double readCounter() {

#ifdef __linux__
			return (data.value - prev.value) * (double)(data.time_enabled - prev.time_enabled) /
			       (data.time_running - prev.time_running);
#else
			return 0;
#endif
		}
	};
	std::unordered_map<std::string, std::vector<event>> events;
	std::vector<std::string>                            ordered_names;

	PerfEvents() {
		if (GLOBAL) {
			counters = 1;
		} else {
			counters = std::thread::hardware_concurrency();
		}
#ifdef __linux__
		char*       cpustr = get_cpu_str();
		std::string cpu(cpustr);
		// see https://download.01.org/perfmon/mapfile.csv for cpu strings
		if (cpu == "GenuineIntel-6-57-core") {
			// Knights Landing
			add("cycles", "cpu/cpu-cycles/");
			add("LLC-misses", "cpu/cache-misses/");
			add("l1-misses", "MEM_UOPS_RETIRED.L1_MISS_LOADS");
			// e.add("l1-hits", "mem_load_retired.l1_hit");
			add("stores", "MEM_UOPS_RETIRED.ALL_STORES");
			add("loads", "MEM_UOPS_RETIRED.ALL_LOADS");
			add("instr.", "instructions");
		} else if (cpu == "GenuineIntel-6-55-core") {
			// Skylake X
			add("cycles", "cpu/cpu-cycles/");
			add("LLC-misses", "cpu/cache-misses/");
			add("LLC-misses2", "mem_load_retired.l3_miss");
			add("l1-misses",
			    PERF_TYPE_HW_CACHE,
			    PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));
			add("instr.", "instructions");
			add("br. misses", "cpu/branch-misses/");
			add("all_rd", "offcore_requests.all_data_rd");
			add("br. misses", "cpu/branch-misses/");
			add("stores", "mem_inst_retired.all_stores");
			add("loads", "mem_inst_retired.all_loads");
			add("mem_stall", "cycle_activity.stalls_mem_any");
			// add("page-faults", "page-faults");

		} else if (cpu == "GenuineIntel-6-6A-core") {
			// TODO
			// Ice Lake
			add("cycles", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CPU_CYCLES);

		} else {
			add("cycles", PERF_TYPE_HARDWARE, PERF_COUNT_HW_CPU_CYCLES);
			add("LLC-misses",
			    PERF_TYPE_HW_CACHE,
			    PERF_COUNT_HW_CACHE_LL | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));
			add("l1-misses",
			    PERF_TYPE_HW_CACHE,
			    PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16));
			add("l1-hits",
			    PERF_TYPE_HW_CACHE,
			    PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8) |
			        (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16));
			add("stores", "cpu/mem-stores/");
			add("loads", "cpu/mem-loads/");
			add("instr.", PERF_TYPE_HARDWARE, PERF_COUNT_HW_INSTRUCTIONS);
			add("br. misses", PERF_TYPE_HARDWARE, PERF_COUNT_HW_BRANCH_MISSES);
		}
		add("task-clock", PERF_TYPE_SOFTWARE, PERF_COUNT_SW_TASK_CLOCK);
#endif

		registerAll();
	}

	void add(std::string name, uint64_t type, uint64_t eventID) {
		if (getenv("EXTERNALPROFILE")) return;
#ifdef __linux__

		ordered_names.push_back(name);
		auto& eventsPerThread = events[name];
		eventsPerThread.assign(counters, event());
		for (auto& event : eventsPerThread) {
			auto& pe = event.pe;
			memset(&pe, 0, sizeof(struct perf_event_attr));
			pe.type           = type;
			pe.size           = sizeof(struct perf_event_attr);
			pe.config         = eventID;
			pe.disabled       = true;
			pe.inherit        = 1;
			pe.inherit_stat   = 0;
			pe.exclude_kernel = true;
			pe.exclude_hv     = true;
			pe.read_format    = PERF_FORMAT_TOTAL_TIME_ENABLED | PERF_FORMAT_TOTAL_TIME_RUNNING;
		}
#else
		compat::unused(name, type, eventID);
#endif
	}
	void add(std::string name, std::string str) {
		if (getenv("EXTERNALPROFILE")) return;
#ifdef __linux__
		ordered_names.push_back(name);
		auto& eventsPerThread = events[name];
		eventsPerThread.assign(counters, event());
		for (auto& event : eventsPerThread) {
			auto& pe = event.pe;
			memset(&pe, 0, sizeof(struct perf_event_attr));
			if (resolve_event(const_cast<char*>(str.c_str()), &pe) < 0)
				std::cerr << "Error resolving perf event " << str << std::endl;
			pe.disabled       = true;
			pe.inherit        = 1;
			pe.inherit_stat   = 0;
			pe.exclude_kernel = true;
			pe.exclude_hv     = true;
			pe.read_format    = PERF_FORMAT_TOTAL_TIME_ENABLED | PERF_FORMAT_TOTAL_TIME_RUNNING;
		}
#else
		compat::unused(name, str);
#endif
	}

	void registerAll() {
		for (auto& ev : events) {
			size_t i = 0;
			for (auto& event : ev.second) {

#ifdef __linux__
				if (GLOBAL)
					event.fd = syscall(__NR_perf_event_open, &event.pe, 0, -1, -1, 0);
				else
					event.fd = syscall(__NR_perf_event_open, &event.pe, 0, i, -1, 0);
				if (event.fd < 0) std::cerr << "Error opening perf event " << ev.first << std::endl;
#else
				compat::unused(event);
#endif
				++i;
			}
		}
	}

	void startAll() {
		for (auto& ev : events) {
			for (auto& event : ev.second) {
#ifdef __linux__
				ioctl(event.fd, PERF_EVENT_IOC_ENABLE, 0);
				if (read(event.fd, &event.prev, sizeof(uint64_t) * 3) != sizeof(uint64_t) * 3)
					std::cerr << "Error reading counter " << ev.first << std::endl;
#else
				compat::unused(event);
#endif
			}
		}
	}

	~PerfEvents() {
		for (auto& ev : events)
			for (auto& event : ev.second)
#ifdef __linux__
				close(event.fd);
#else
				compat::unused(event);
#endif
	}

	void readAll() {
		for (auto& ev : events)
			for (auto& event : ev.second) {
#ifdef __linux__
				if (read(event.fd, &event.data, sizeof(uint64_t) * 3) != sizeof(uint64_t) * 3)
					std::cerr << "Error reading counter " << ev.first << std::endl;
				ioctl(event.fd, PERF_EVENT_IOC_DISABLE, 0);
#else
				compat::unused(event);
#endif
			}
	}

	void printHeader(std::ostream& out) {
		for (auto& name : ordered_names)
			out << std::setw(printFieldWidth) << name << ",";
	}

	void printAll(std::ostream& out, double n) {
		for (auto& name : ordered_names) {
			double aggr = 0;
			for (auto& event : events[name])
				aggr += event.readCounter();
			out << std::setw(printFieldWidth) << aggr / n << ",";
		}
	}

	double operator[](std::string index) {
		double aggr = 0;
		for (auto& event : events[index])
			aggr += event.readCounter();
		return aggr;
	};

	void timeAndProfile(
	    std::string name, uint64_t count, std::function<void()> fn, uint64_t repetitions = 1, bool mem = false);
};

inline double gettime() {
	struct timeval now_tv;
	gettimeofday(&now_tv, NULL);
	return ((double)now_tv.tv_sec) + ((double)now_tv.tv_usec) / 1000000.0;
}

size_t getCurrentRSS() {
	long  rss = 0L;
	FILE* fp  = NULL;
	if ((fp = fopen("/proc/self/statm", "r")) == NULL) return (size_t)0L; /* Can't open? */
	if (fscanf(fp, "%*s%ld", &rss) != 1) {
		fclose(fp);
		return (size_t)0L; /* Can't read? */
	}
	fclose(fp);
	return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);
}

void PerfEvents::timeAndProfile(
    std::string name, uint64_t count, std::function<void()> fn, uint64_t repetitions, bool mem) {
	using namespace std;
	// warmup round
	double warumupStart = gettime();
	for (size_t i {0}; i < 5; ++i) {
		fn();
	}

	uint64_t memStart = 0;
	if (mem) memStart = getCurrentRSS();
	startAll();
	double start        = gettime();
	size_t performedRep = 10;
	for (size_t i {0}; i < performedRep; ++i) {
		fn();
	}
	double end = gettime();
	readAll();
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	if (writeHeader) {
		std::cout << setw(20) << "name"
		          << "," << setw(printFieldWidth) << " time(ms)"
		          << "," << setw(printFieldWidth) << " CPUs"
		          << "," << setw(printFieldWidth) << " IPC"
		          << "," << setw(printFieldWidth) << " GHz"
		          << "," << setw(printFieldWidth) << " Bandwidth"
		          << ",";
		printHeader(std::cout);
		std::cout << std::endl;
	}

	auto runtime = end - start;
	std::cout << setw(20) << name << "," << setw(printFieldWidth) << (runtime * 1e3 / performedRep) << ",";
#ifdef __linux__
	if (!getenv("EXTERNALPROFILE")) {
		std::cout << setw(printFieldWidth) << ((*this)["task-clock"] / (runtime * 1e9)) << ",";
		std::cout << setw(printFieldWidth) << ((*this)["instr."] / (*this)["cycles"]) << ",";
		std::cout << setw(printFieldWidth)
		          << ((*this)["cycles"] /
		              (this->events["cycles"][0].data.time_enabled - this->events["cycles"][0].prev.time_enabled))
		          << ",";
		std::cout << setw(printFieldWidth) << ((((*this)["all_rd"] * 64.0) / (1024 * 1024)) / (end - start)) << ",";
	}
#endif
	// std::cout <<
	// (((e["all_requests"]*64.0)/(1024*1024))/(e.events["cycles"][0].data.time_enabled/1e9))
	// << " allMB/s,";

	printAll(std::cout, count * performedRep);
	if (mem) std::cout << (getCurrentRSS() - memStart) / (1024.0 * 1024) << "MB";
	std::cout << std::endl;
	writeHeader = false;
}
