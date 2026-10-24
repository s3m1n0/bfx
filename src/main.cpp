#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "lexer.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "please provide a file path\n";
    return 1;
  }
  // debug reason later switch to argv[1]
  std::string filePath = argv[1];

  std::ifstream file{filePath};

  if (!file.good()) {
    std::cerr << "Failed to open file: " << filePath << std::endl;

    return 1;
  }

  const std::string content{std::istreambuf_iterator<char>{file},
                            std::istreambuf_iterator<char>{}};

  std::vector<Token> source_tokens{parse_source_code(content)};
  for (const auto& token : source_tokens) {
    std::cout << std::format("instruction [{}] at source character [{}]\n",
                             static_cast<int>(token.instruction),
                             token.source_line);
  }
  std::cout << std::endl;

  return 0;
}