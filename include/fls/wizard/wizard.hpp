#ifndef FLS_WIZARD_WIZARD_HPP
#define FLS_WIZARD_WIZARD_HPP

#include <cstdint>
#include <fls/common/alias.hpp>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Plan;
class Connection;
class RowGroupView;
class RowgroupEncodingResult;
class CorrelationGraph;
class Rowgroup;
struct TableDescriptorT;
/*--------------------------------------------------------------------------------------------------------------------*/
enum class ExpressionChoosingStrategy : uint8_t {
	INVALID                = 0,
	BEST_COMPRESSION_RATIO = 1,
};

class Wizard {
public:
	Wizard() = delete;

public:
	static up<TableDescriptorT> Spell(const Connection& fls);
};
} // namespace fastlanes

#endif // FLS_WIZARD_WIZARD_HPP
