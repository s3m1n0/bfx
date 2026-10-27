#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "lexer.hpp"
#include "optimize.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "please provide a file path\n";
    return 1;
  }
  // debug reason later switch to argv[1]
  std::string file_path = argv[1];

  std::ifstream file{file_path};

  if (!file.good()) {
    std::cerr << "Failed to open file: " << file_path << std::endl;

    return 1;
  }

  const std::string content{std::istreambuf_iterator<char>{file},
                            std::istreambuf_iterator<char>{}};

  std::vector<Token> source_tokens{parse_source_code(content)};
  std::vector<IR> ir{parse_instruction_tokens(source_tokens)};
  optimize_instructions(ir);

  return 0;
}