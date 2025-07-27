// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/engine/enums.cuh
// ────────────────────────────────────────────────────────
#ifndef ENUMS_CUH
#define ENUMS_CUH

#include <stdexcept>
#include <string>

namespace enums {
enum class DataType {
	U32,
	U64,
	F32,
	F64,
};

enum class Kernel {
	Decompress,
	Query,
	QueryMultiColumn,
};

enum class Unpacker {
	Dummy,
	OldFls,
	SwitchCase,
	Stateless,
	StatelessBranchless,
	StatefulCache,
	StatefulLocal1,
	StatefulLocal2,
	StatefulLocal4,
	StatefulShared1,
	StatefulShared2,
	StatefulShared4,
	StatefulRegister1,
	StatefulRegister2,
	StatefulRegister4,
	StatefulRegisterBranchless1,
	StatefulRegisterBranchless2,
	StatefulRegisterBranchless4,
	StatefulBranchless,
};

enum class Patcher {
	None,
	Dummy,
	Stateless,
	Stateful,
	Naive,
	NaiveBranchless,
	PrefetchPosition,
	PrefetchAll,
	PrefetchAllBranchless,
};

enum class Print {
	PrintNothing,
	PrintDebug,
	PrintDebugExit0,
};

DataType string_to_data_type(const std::string& str);
Kernel   string_to_kernel(const std::string& str);
Unpacker string_to_unpacker(const std::string& str);
Patcher  string_to_patcher(const std::string& str);

} // namespace enums

namespace enums_nvcomp {
enum ComparisonType {
	DECOMPRESSION,
	DECOMPRESSION_QUERY,
};

ComparisonType string_to_comparison_type(const std::string& str);
std::string    comparison_type_to_string(const ComparisonType type);

enum CompressionType {
	THRUST,
	ALP,
	GALP,
	BITCOMP,
	BITCOMP_SPARSE,
	LZ4,
	ZSTD,
	DEFLATE,
	GDEFLATE,
	SNAPPY,
};

CompressionType string_to_compression_type(const std::string& str);
std::string     compression_type_to_string(const CompressionType type);
} // namespace enums_nvcomp

#endif // ENUMS_CUH
