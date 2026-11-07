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

 private:
  std::vector<IR> m_ir{};
};

// raw translation, no optimization
std::vector<IR> parse_instruction_tokens(
    const std::vector<Token>& instructions);
// in place optimization on the input vector
void combine_instructions(std::vector<IR>& ir);

#endif
