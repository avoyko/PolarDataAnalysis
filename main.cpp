#include <iostream>

#include "src/decoder.hpp"

#define PROJECT_NAME "main"

int main(int argc, char **argv) {
  if (argc != 1) {
    std::cout << argv[0] << "takes no arguments.\n";
    return 1;
  }
  std::cout << "Andrey really likes Discrete Maths.\n";
  return 0;
}
