#include "modernLibrary.h"

#include <iostream>
#include <vector>

#include "fileHandling.h"

std::ostream& operator<<(std::ostream& os, const std::vector<int>& data) {
  for (auto& e : data) {
    os << e << ' ';
  }
  return os;
}
static const char* const FILENAME = "nums.dat";

int saveVector(const std::vector<int>& nums) {
  const auto file = getFileInMode(FILENAME, "wb");

  if (const auto ok = fwrite(nums.data(), sizeof(int), nums.size(), file.get());
      ok != nums.size()) {
    std::cerr << "Fehler beim Schreiben" << std::endl;
    return -1;
  }

  return 0;
}

auto loadVector() -> std::vector<int> {
  const auto file = getFileInMode(FILENAME, "rb");
  std::vector<int> gelesen{};

  const size_t sz = 4;
  gelesen.resize(sz);
  if (auto ok = fread(gelesen.data(), sizeof(int), sz, file.get()); ok != sz) {
    std::cerr << "Fehler beim Lesen" << std::endl;
    return gelesen;
  }
  return gelesen;
}

auto doWork() -> int {
  try {
    const std::vector<int> nums{10, 11, 22, 34};
    if (auto ok = saveVector(nums); ok != 0) {
      return -1;
    }

    const std::vector<int> gelesen = loadVector();
    if (gelesen.size() < 4) {
      return -1;
    }

    std::cout << nums << std::endl;
    std::cout << gelesen << std::endl;
  } catch (std::invalid_argument) {
    return -1;
  }

  return 0;
}