#include <format>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

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

  std::cout << content << std::endl;

  return 0;
}