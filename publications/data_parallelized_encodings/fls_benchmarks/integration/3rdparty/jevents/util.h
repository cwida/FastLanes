// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// publications/data_parallelized_encodings/fls_benchmarks/integration/3rdparty/jevents/util.h
// ────────────────────────────────────────────────────────
#ifdef __cplusplus
extern "C" {
#endif

#define err(x) perror(x), exit(1)
#define mb() asm volatile("" ::: "memory")
#define MB (1024*1024)
typedef unsigned long long u64;
typedef long long s64;

#ifdef __cplusplus
}
#endif
