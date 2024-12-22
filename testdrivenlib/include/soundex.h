#pragma once

#include <string>
#include <unordered_map>

constexpr size_t kMAX_CODE_LENGTH{4};
const std::string kNOT_A_DIGIT{"*"};
const std::unordered_map<char, std::string> kENCODINGS{
  {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
  {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
  {'d', "3"}, {'t', "3"},
  {'l', "4"},
  {'m', "5"}, {'n', "5"},
  {'r', "6"}
};

class Soundex {
public:
  static std::string encode(const std::string &word) {
    return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
  }

  static std::string encodedDigit(const char letter) {
    const auto it = kENCODINGS.find(lower(letter));
    return it == kENCODINGS.end() ? kNOT_A_DIGIT : it->second;
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

  static void encodeHead(std::string &encoding, const std::string &word) {
    encoding += encodedDigit(word.front());
  }

  static void encodeTail(std::string &encoding, const std::string &word) {
    for (const auto letter: word) {
      if (isComplete(encoding)) {
        break;
      }
      encodeLetter(encoding, letter);
    }
  }

  static void encodeLetter(std::string &encoding, const char letter) {
    if (const auto digit = encodedDigit(letter);
      digit != kNOT_A_DIGIT && digit != lastDigit(encoding)) {
      encoding += digit;
    }
  }

  static std::string encodedDigits(const std::string &word) {
    std::string encoding;
    encodeHead(encoding, word);
    encodeTail(encoding, tail(word));
    return encoding;
  }

  static bool isComplete(const std::string &encoding) {
    return encoding.length() == kMAX_CODE_LENGTH;
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
