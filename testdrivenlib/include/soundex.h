#pragma once

#include <string>

class Soundex {
public:
  static std::string encode(const std::string &word);

  static std::string encodedDigit(char letter);
};