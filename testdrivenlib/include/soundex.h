#pragma once

#include <string>
#include <unordered_map>

constexpr size_t kMAX_CODE_LENGTH{4};

class Soundex {
public:
  static std::string encode(const std::string &word) {
    return zeroPad(head(word) + encodedDigits(word));
  }

private:
  static std::string head(const std::string &word) {
    return word.substr(0, 1);
  }

  static std::string encodedDigits(const std::string &word) {
    if (word.length() > 1) {
      return encodedDigit(word[1]);
    }
    return "";
  }

  static std::string encodedDigit(const char letter) {
    const std::unordered_map<char, std::string> encodings{
      {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
      {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
      {'d', "3"}, {'t', "3"},
      {'l', "4"},
      {'m', "5"}, {'n', "5"},
      {'r', "6"}
    };
    const auto it = encodings.find(letter);
    return it == encodings.end() ? "" : it->second;
  }

  static std::string zeroPad(const std::string &word) {
    auto zerosNeeded = kMAX_CODE_LENGTH - word.length();
    return word + std::string(zerosNeeded, '0');
  }
};
