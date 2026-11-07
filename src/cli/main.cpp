#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "../lexer.hpp"
#include "../optimize.hpp"
#include "../runtime.hpp"

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

  std::vector<Token> source_tokens = parse_source_file(file);
  Optimization ir(source_tokens);
  SimpleRuntime runtime{};
  runtime.run(ir);

  return 0;
}