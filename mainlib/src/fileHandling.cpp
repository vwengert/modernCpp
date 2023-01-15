#include "fileHandling.h"

#include <array>
#include <cstring>
#include <iostream>

#ifdef __unix
#define fopen_s(pFile, filename, mode) \
  ((*(pFile)) = fopen((filename), (mode))) == NULL
#define strerror_s(buffer, length, errorcode) \
  strerror_r(errorcode, buffer, length)
#endif
#ifdef __win
using std::FILE
#endif

    using Destroyer = std::function<void(FILE*)>;
void closeFile(FILE* file) { std::fclose(file); }

std::unique_ptr<FILE, std::function<void(FILE*)>> openFileInMode(
    const char* name, const char* mode) {
  FILE* file;

  if (const auto err = fopen_s(&file, name, mode); err != 0) {
    char buffer[256];
    strerror_s(buffer, 255, err);
    std::string error =
        "Cannot open file " + std::string(name) + " with error " + buffer;
    std::cerr << error;
    throw std::invalid_argument(error);
  }
  auto ptr = std::unique_ptr<FILE, Destroyer>(file, &closeFile);

  return ptr;
}
