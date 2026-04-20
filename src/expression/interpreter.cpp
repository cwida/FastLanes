// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/interpreter.cpp
// ────────────────────────────────────────────────────────
#include "fls/expression/interpreter.hpp"

namespace fastlanes {

InterpreterState::InterpreterState()
    : cur_operator(0)
    , cur_operand(0)
    , n_segments(0) {
}

} // namespace fastlanes
