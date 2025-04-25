#ifndef FLS_TABLE_CHUNK_HPP
#define FLS_TABLE_CHUNK_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/expression/data_type.hpp"
#include "fls/expression/selection_ds.hpp"
#include "fls/std/span.hpp"
#include "fls/std/variant.hpp"
#include "fls/std/vector.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class TypedCol;
class PhysicalExpr;
/*--------------------------------------------------------------------------------------------------------------------*/
using null_map_span = span<bool>;
using byte_span_t   = span<uint8_t>;
using ofs_span_t    = span<ofs_t>;
using length_span_t = span<len_t>;

/*--------------------------------------------------------------------------------------------------------------------*/
class BaseVector {
public:
	null_map_span null_map_span;
	bool          should_be_stored {false};
};

/*--------------------------------------------------------------------------------------------------------------------*/
class VariableSizeVector : public BaseVector {
public:
	ofs_span_t ofs_span;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * Typed vector
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class TypedVector : public BaseVector {
public:
	explicit TypedVector(const col_pt& col_pt);

public:
	void point_to(n_t vec_idx);
	/// size in bytes
	[[nodiscard]] static constexpr sz_t Size() {
		return sizeof(PT) * CFG::VEC_SZ;
	}

public:
	const PT* m_data;
	n_t       m_vec_idx;
};

using vec_str   = TypedVector<str_pt>;
using flt_vec_t = TypedVector<flt_pt>;
using dbl_vec_t = TypedVector<dbl_pt>;
using i08_vec_t = TypedVector<i08_pt>;
using i16_vec_t = TypedVector<i16_pt>;
using i32_vec_t = TypedVector<i32_pt>;
using vec_i64   = TypedVector<i64_pt>;
using u08_vec_t = TypedVector<u08_pt>;
using u16_vec_t = TypedVector<u16_pt>;
using u32_vec_t = TypedVector<u32_pt>;
using u64_vec_t = TypedVector<u64_pt>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * Constant vector
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class ConstantVector {
public:
	explicit ConstantVector(const PT& value); // NOLINT

public:
	PT value;
};
using str_constant_vec_t = ConstantVector<str_pt>;
using flt_constant_vec_t = ConstantVector<flt_pt>;
using dbl_constant_vec_t = ConstantVector<dbl_pt>;
using i08_constant_vec_t = ConstantVector<i08_pt>;
using i16_constant_vec_t = ConstantVector<i16_pt>;
using i32_constant_vec_t = ConstantVector<i32_pt>;
using constant_vec_i64   = ConstantVector<i64_pt>;
using u08_constant_vec_t = ConstantVector<u08_pt>;
using u16_constant_vec_t = ConstantVector<u16_pt>;
using u32_constant_vec_t = ConstantVector<u32_pt>;
using u64_constant_vec_t = ConstantVector<u64_pt>;
/*--------------------------------------------------------------------------------------------------------------------*\
 * physical_vector
\*--------------------------------------------------------------------------------------------------------------------*/
using fls_vec = variant<std::monostate,
                        up<u08_vec_t>,
                        up<u16_vec_t>,
                        up<u32_vec_t>,
                        up<u64_vec_t>,
                        up<i08_vec_t>,
                        up<i16_vec_t>,
                        up<i32_vec_t>,
                        up<vec_i64>,
                        up<flt_vec_t>,
                        up<dbl_vec_t>,
                        up<vec_str>,
                        up<u08_constant_vec_t>,
                        up<u16_constant_vec_t>,
                        up<u32_constant_vec_t>,
                        up<u64_constant_vec_t>,
                        up<i08_constant_vec_t>,
                        up<i16_constant_vec_t>,
                        up<i32_constant_vec_t>,
                        up<constant_vec_i64>,
                        up<flt_constant_vec_t>,
                        up<dbl_constant_vec_t>,
                        up<str_constant_vec_t>,
                        up<class ListVector>,
                        up<class StructVector>,
                        up<SelectionDS>>;

using fls_chunk = vector<fls_vec>;

/*--------------------------------------------------------------------------------------------------------------------*\
 * list vector
\*--------------------------------------------------------------------------------------------------------------------*/
class ListVector : public VariableSizeVector {
public:
	fls_vec child;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * struct vector
\*--------------------------------------------------------------------------------------------------------------------*/
class StructVector : public BaseVector {
public:
	fls_chunk table;
};

} // namespace fastlanes
#endif // FLS_TABLE_CHUNK_HPP
