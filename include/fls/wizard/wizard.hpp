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
class Footer;
/*--------------------------------------------------------------------------------------------------------------------*/
enum class ExpressionChoosingStrategy : uint8_t {
	INVALID                = 0,
	BEST_COMPRESSION_RATIO = 1,
};

class Wizard {
public:
	Wizard() = delete;

public:
	static up<Footer> Spell(const Connection& fls);
	static void       ChooseExpr(ExpressionChoosingStrategy strategy, RowgroupEncodingResult& result, Footer& plan);

private:
	static void constant_check(const Rowgroup& rowgroup, Footer& footer);
	static void equality_check(const Rowgroup& rowgroup, Footer& compression_plan);
	static void expression_check(const Rowgroup& rowgroup, Footer& compression_plan);
	static void map_1t1_check(const Rowgroup& rowgroup, Footer& compression_plan);
};
} // namespace fastlanes

#endif // FLS_WIZARD_WIZARD_HPP
