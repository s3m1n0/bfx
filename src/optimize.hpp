#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include <stddef.h>

#include <vector>

#include "lexer.hpp"

enum class IRInstructions {
  // basic instructions
  AddPointer,
  MovePointer,

  // io
  Input,
  Output,

  // loop basics
  LoopStart,
  LoopEnd,

  // optimization
  ClearPointer,     // [-]
  MovePointerValue  // [->+<]
};

struct IR {
  IRInstructions instruction;
  int value;
};

class Optimization {
 public:
  const std::vector<IR>& get_ir() const { return m_ir; }
  Optimization(const std::vector<Token>& instructions);
  void combine_instructions();
  void recognize_loops_patterns();

 private:
  std::vector<IR> m_ir{};
};

#endif
