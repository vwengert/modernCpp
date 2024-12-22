#pragma once

#include <string>
#include <unordered_map>

constexpr size_t kMAX_CODE_LENGTH{4};
const std::string kNOT_A_DIGIT{"*"};

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
    const auto it = encodings.find(lower(letter));
    return it == encodings.end() ? kNOT_A_DIGIT : it->second;
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
      if (auto digit = encodedDigit(letter);
        digit != kNOT_A_DIGIT && digit != lastDigit(encoding)) {
        encoding += digit;
      }
    }
    return encoding;
  }

  static bool isComplete(const std::string &encoding) {
    return encoding.length() == kMAX_CODE_LENGTH - 1;
  }

  static std::string lastDigit(const std::string &encoding) {
    return encoding.empty() ? kNOT_A_DIGIT : &encoding.back();
  }

  static std::string tail(const std::string &word) {
    return word.substr(1);
  }

  static char lower(const char letter) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
  }
};
