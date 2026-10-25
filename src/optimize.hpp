#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include <stddef.h>

#include <lexer.hpp>
#include <vector>

enum class IRInstructions {
  // basic instructions
  AddPointer,
  MovePointer,

  // io
  Input,
  Output,

  // loop basics
  LoopStart,
  Loopend,

  // optimization
  ClearPointer,     // [-]
  MovePointerValue  // [->+<]
};

struct IRToken {
  IRInstructions instruction;
  size_t value;
};

std::vector<IRToken> parse_instruction_tokens(
    const std::vector<TokenInstructions>& instructions);

#endif
