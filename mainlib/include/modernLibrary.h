#include <string>

auto doWork() -> int;
auto isPalindrome(const std::string_view&& word) -> bool;

struct Squares {
  mutable int n = 1;
  int operator()() const { return n * n++; }
};