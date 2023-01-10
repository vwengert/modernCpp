#include "modernLibrary.h"

#include <algorithm>
#include <iostream>
#include <set>
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
  const auto file = openFileInMode(FILENAME, "wb");

  if (const auto ok = fwrite(nums.data(), sizeof(int), nums.size(), file.get());
      ok != nums.size()) {
    std::cerr << "Fehler beim Schreiben" << std::endl;
    return -1;
  }

  return 0;
}

auto loadVector() -> std::vector<int> {
  const auto file = openFileInMode(FILENAME, "rb");
  std::vector<int> gelesen{};

  const size_t sz = 4;
  gelesen.resize(sz);
  if (auto ok = fread(gelesen.data(), sizeof(int), sz, file.get()); ok != sz) {
    std::cerr << "Fehler beim Lesen" << std::endl;
    return gelesen;
  }
  return gelesen;
}

void vectors() {
  try {
    const std::vector<int> nums{10, 11, 22, 34};
    if (auto ok = saveVector(nums); ok != 0) {
      return;
    }

    const std::vector<int> gelesen = loadVector();
    if (gelesen.size() < 4) {
      return;
    }

    std::cout << nums << std::endl;
    std::cout << gelesen << std::endl;
  } catch (std::invalid_argument) {
    return;
  }

  if (remove(FILENAME) == -1) {
    std::cerr << "Fehler beim Löschen der Datei" << std::endl;
  }

  std::vector<int> v1 = {1, 2, 4, 4, 3};
  std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7};
  std::vector<int> result;

  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  std::set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(),
                      std::back_inserter(result));
  std::cout << result << std::endl;

  result.clear();
  std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::back_inserter(result));
  std::cout << result << std::endl;
}

bool isPalindrome(const std::string_view&& word) {
  std::vector<char> vec(word.begin(), word.end());
  auto second = vec.rbegin();
  size_t sz = vec.size();
  for (auto first = 0; first != sz / 2; first++) {
    std::cout << vec[first] << " : " << *second << std::endl;
    if (std::toupper(vec[first]) != std::toupper(*second)) {
      return false;
    }
    second++;
  }
  return true;
}

void palindromes() {
  std::cout << std::boolalpha;
  std::cout << isPalindrome("Otto") << std::endl;
  std::cout << isPalindrome("Volker") << std::endl;
  std::cout << isPalindrome("Reliefpfeiler") << std::endl;
}

auto doWork() -> int {
  vectors();
  palindromes();
  return 0;
}