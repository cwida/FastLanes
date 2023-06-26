#pragma once
#include "common/runtime/Types.hpp"
#include "vectorwise/Operators.hpp"

struct ExperimentConfig{
  typedef vectorwise::pos_t (vectorwise::Hashjoin::*joinFun)();
  bool useSimdJoin = false;
  bool useSimdHash = false;
  bool useSimdSel = false;
  bool useSimdProj = false;
  vectorwise::primitives::F2 hash_int32_t_col();
  vectorwise::primitives::F3 hash_sel_int32_t_col();
  vectorwise::primitives::F2 rehash_int32_t_col();
  vectorwise::primitives::F3 rehash_sel_int32_t_col();
  vectorwise::primitives::F4 proj_sel_minus_int64_t_val_int64_t_col();
  vectorwise::primitives::F4 proj_sel_plus_int64_t_col_int64_t_val();
  vectorwise::primitives::F3 proj_multiplies_int64_t_col_int64_t_col();
  vectorwise::primitives::F4 proj_multiplies_sel_int64_t_col_int64_t_col();
  vectorwise::primitives::F3 sel_less_int32_t_col_int32_t_val();
  vectorwise::primitives::F4 selsel_greater_equal_int32_t_col_int32_t_val();
  vectorwise::primitives::F4 selsel_less_int64_t_col_int64_t_val();
  vectorwise::primitives::F4 selsel_greater_equal_int64_t_col_int64_t_val();
  vectorwise::primitives::F4 selsel_less_equal_int64_t_col_int64_t_val();
  joinFun joinAll();
  joinFun joinSel();
};

extern ExperimentConfig conf;
