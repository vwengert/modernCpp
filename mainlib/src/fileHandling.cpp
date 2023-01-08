#include "fileHandling.h"

#include <array>
#include <iostream>

using Destroyer = std::function<void(std::FILE*)>;
void closeFile(std::FILE* file) { std::fclose(file); }

std::unique_ptr<std::FILE, std::function<void(std::FILE*)>> getFileInMode(
    const char* name, const char* mode) {
  FILE* file;

  if (const auto err = fopen_s(&file, name, mode); err != 0) {
    std::array<char, 256> buffer;
    strerror_s(buffer.data(), 255, err);
    std::string error = "Cannot open file " + std::string(name) +
                        " with error " + buffer.data();
    std::cerr << error;
    throw std::invalid_argument(error);
  }
  auto ptr = std::unique_ptr<std::FILE, Destroyer>(file, &closeFile);

  return ptr;
}