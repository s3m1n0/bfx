#include "runtime.hpp"

#include <array>
#include <iostream>

void simple_runtime(const std::vector<IR>& ir) {
  std::array<int, 30'000> memory{0};
  size_t pointer{0};
  for (int i{0}; i < ir.size(); i++) {
    IR instruction{ir[i]};
    switch (instruction.instruction) {
      case IRInstructions::AddPointer:
        memory[pointer] = (memory[pointer] + instruction.value) % 256;
        break;
      case IRInstructions::MovePointer:
        pointer = (pointer + instruction.value) % 30'000;
        break;
      case IRInstructions::Output:
        std::cout << static_cast<char>(memory[pointer]);
        break;
      case IRInstructions::Input: {
        char input;
        if (std::cin.get(input)) {
          memory[pointer] = static_cast<unsigned char>(input);
        }
        break;
      }
      case IRInstructions::LoopStart: {
        if (memory[pointer] == 0) i = instruction.value;
        break;
      }
      case IRInstructions::LoopEnd: {
        if (memory[pointer] != 0) i = instruction.value;
        break;
      }
    }
  }
  std::cout << std::endl;
}
