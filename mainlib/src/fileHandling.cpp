#include "fileHandling.h"

#include <array>
#include <iostream>

using Destroyer = std::function<void(std::FILE*)>;
void closeFile(std::FILE* file) { std::fclose(file); }

std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> openFileInMode(
    const char* name, const char* mode) {
  FILE* file;

  if (const auto err = fopen_s(&file, name, mode); err != 0) {
    std::string error = "Cannot open file " + std::string(name);
    std::cerr << error;
    throw std::invalid_argument(error);
  }
  auto ptr = std::unique_ptr<std::FILE, Destroyer>(file, &closeFile);

  return ptr;
}