#pragma once

#include <string>
#include <unordered_map>

constexpr size_t kMAX_CODE_LENGTH{4};

class Soundex {
public:
  static std::string encode(const std::string &word) {
    return zeroPad(upperFront(head(word)) + encodedDigits(tail(word)));
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

private:
  static std::string zeroPad(const std::string &word) {
    const auto zerosNeeded = kMAX_CODE_LENGTH - word.length();
    return word + std::string(zerosNeeded, '0');
  }

  static std::string upperFront(const std::string &string) {
    return std::string(1, static_cast<char>(std::toupper(string.front())));
  }

  static std::string head(const std::string &word) {
    return word.substr(0, 1);
  }

  static std::string encodedDigits(const std::string &word) {
    std::string encoding;
    for (const auto letter: word) {
      if (isComplete(encoding)) {
        break;
      }
      if (encodedDigit(letter) != lastDigit(encoding)) {
        encoding += encodedDigit(letter);
      }
    }
    return encoding;
  }

  static bool isComplete(const std::string &encoding) {
    return encoding.length() == kMAX_CODE_LENGTH - 1;
  }

  static std::string::const_pointer lastDigit(const std::string &encoding) {
    return encoding.empty() ? "" : &encoding.back();
  }

  static std::string tail(const std::string &word) {
    return word.substr(1);
  }
};
