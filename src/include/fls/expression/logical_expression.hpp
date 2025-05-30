#ifndef FLS_EXPRESSION_LOGICAL_EXPRESSION_HPP
#define FLS_EXPRESSION_LOGICAL_EXPRESSION_HPP

#include "fls/common/common.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/std/string.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Scanner;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
 * LogicalExpression
\*--------------------------------------------------------------------------------------------------------------------*/
class LogicalExpr {
public:
	virtual ~LogicalExpr();
	virtual void                 to_physical(PhysicalExpr& expr, Scanner& rowgroup) const;
	[[nodiscard]] virtual string to_string() const {
		return "nothing";
	};
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * InvalidExp
\*--------------------------------------------------------------------------------------------------------------------*/
class InvalidExpr final : public LogicalExpr {
public:
	explicit InvalidExpr();
	~InvalidExpr() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& rowgroup) const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * Column
\*--------------------------------------------------------------------------------------------------------------------*/
class ColumnExpr final : public LogicalExpr {
	n_t m_col_idx;

public:
	explicit ColumnExpr(n_t idx);
	~ColumnExpr() override = default;

public:
	void                 to_physical(PhysicalExpr& expr, Scanner& rowgroup) const override;
	[[nodiscard]] string to_string() const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * V -> Value
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class Value final : public LogicalExpr {
	PT m_value;

public:
	explicit Value(const PT& val); // NOLINT
	~Value() override = default;

public:
	void                 to_physical(PhysicalExpr& expr, Scanner& rowgroup) const override;
	[[nodiscard]] string to_string() const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * BinaryExpression
\*--------------------------------------------------------------------------------------------------------------------*/
class BinaryExpr : public LogicalExpr {
public:
	up<LogicalExpr> m_e1, m_e2;

public:
	template <typename EXPRESSION1, typename EXPRESSION2>
	BinaryExpr(EXPRESSION1 e1, EXPRESSION2 e2)
	    : m_e1(make_unique<EXPRESSION1>(std::move(e1)))
	    , m_e2(make_unique<EXPRESSION2>(std::move(e2))) {
	}
	~BinaryExpr() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& scanner) const override {
		FLS_UNREACHABLE();
	}
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * EQ
\*--------------------------------------------------------------------------------------------------------------------*/
class EQ final : public BinaryExpr {
public:
	template <typename EXPRESSION1, typename EXPRESSION2>
	EQ(EXPRESSION1 e1, EXPRESSION2 e2)
	    : BinaryExpr(e1, e2) {
	}
	~EQ() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& scanner) const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * GT
\*--------------------------------------------------------------------------------------------------------------------*/
class GT final : public BinaryExpr {
public:
	template <typename EXPRESSION1, typename EXPRESSION2>
	GT(EXPRESSION1 e1, EXPRESSION2 e2)
	    : BinaryExpr(e1, e2) {
	}
	~GT() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& scanner) const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * LT
\*--------------------------------------------------------------------------------------------------------------------*/
class LT final : public BinaryExpr {
public:
	template <typename EXPRESSION1, typename EXPRESSION2>
	LT(EXPRESSION1 e1, EXPRESSION2 e2)
	    : BinaryExpr(e1, e2) {
	}
	~LT() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& scanner) const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * AND
\*--------------------------------------------------------------------------------------------------------------------*/
class AND final : public BinaryExpr {
public:
	template <typename EXPRESSION1, typename EXPRESSION2>
	AND(EXPRESSION1 e1, EXPRESSION2 e2)
	    : BinaryExpr(e1, e2) {
	}
	~AND() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& scanner) const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * CONSTANT
\*--------------------------------------------------------------------------------------------------------------------*/
class ConstantExp final : public BinaryExpr {
public:
	template <typename EXPRESSION1, typename EXPRESSION2>
	ConstantExp(EXPRESSION1 e1, EXPRESSION2 e2)
	    : BinaryExpr(e1, e2) {
	}
	~ConstantExp() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& scanner) const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * HardcodedExpr
\*--------------------------------------------------------------------------------------------------------------------*/
class HardcodedExpr final : public LogicalExpr {
public:
	explicit HardcodedExpr()  = default;
	~HardcodedExpr() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& rowgroup) const override {
	}
	[[nodiscard]] string to_string() const override;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * EqualExpr
\*--------------------------------------------------------------------------------------------------------------------*/
class EqualityExpr final : public LogicalExpr {
public:
	explicit EqualityExpr(n_t col_idx, n_t main_col_idx);
	~EqualityExpr() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& rowgroup) const override {
	}
	[[nodiscard]] string to_string() const override;

public:
	n_t col_idx;
	n_t main_col_idx;
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * DictExpr
\*--------------------------------------------------------------------------------------------------------------------*/
class Dict final : public LogicalExpr {
public:
	explicit Dict(n_t col_idx, n_t main_col_idx);
	~Dict() override = default;

public:
	void to_physical(PhysicalExpr& expr, Scanner& rowgroup) const override {
	}
	[[nodiscard]] string to_string() const override;

public:
	n_t dict_col_idx;
	n_t codes_col_idx;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_LOGICAL_EXPRESSION_HPP
