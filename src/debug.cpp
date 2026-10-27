#include <iostream>

#include "optimize.hpp"

void print_ir(const IR& ir) {
  switch (ir.instruction) {
    case IRInstructions::AddPointer:
      std::cout << "AddPointer(" << ir.value << ")";
      break;

    case IRInstructions::MovePointer:
      std::cout << "MovePointer(" << ir.value << ")";
      break;

    case IRInstructions::Input:
      std::cout << "Input";
      break;

    case IRInstructions::Output:
      std::cout << "Output";
      break;

    case IRInstructions::LoopStart:
      std::cout << "LoopStart";
      break;

    case IRInstructions::Loopend:
      std::cout << "LoopEnd";
      break;

    case IRInstructions::ClearPointer:
      std::cout << "ClearPointer";
      break;

    case IRInstructions::MovePointerValue:
      std::cout << "MovePointerValue(" << ir.value << ")";
      break;
  }
}