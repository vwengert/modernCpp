#pragma once
#include <cstring>
#include <type_traits>
#include <bitset>

inline char const *max(char const *first, char const *second) {
  return std::strcmp(second, first) < 0 ? first : second;
}

template<typename T1, typename T2>
constexpr auto max(T1 first, T2 second) -> std::common_type_t<T1, T2> {
  return second < first ? first : second;
}

template<typename RT, typename T1, typename T2>
constexpr RT max(T1 first, T2 second) {
  return second < first ? first : second;
}

template<typename T>
T *max(T *first, T *second) {
  return *second < *first ? first : second;
}

template<typename T>
void print(std::ostream &stream, const char * /*sep*/, const char *end, T arg) {
  stream << arg << end;
}

template<typename T, typename... Types>
void print(std::ostream &stream, const char *sep, const char *end, T firstArg, Types... args) {
  stream << firstArg << sep;
  print(stream, sep, end, args...);
}

template<typename T, typename... Types>
void print(std::ostream &stream, T firstArg, Types... args) {
  print(stream, ", ", "\n", firstArg, args...);
}

template<typename... T>
constexpr auto foldSum(T... args) {
  return (... + args);
}

template<typename T1, typename... TN>
constexpr bool isHomogeneous(T1 /*unused*/, TN... /*unused*/) {
  return (std::is_same_v<T1, TN> && ...);
}

template<std::size_t... Idx, typename C>
void printIdx(std::ostream &stream, C const &container) {
  ((stream << container[Idx] << ' '), ...) << '\n';
}

template<typename T, int N, int M>
bool less(T (&first)[N], T (&second)[M]) // NOLINT(*-avoid-c-arrays)
{
  for (int i = 0; i < N && i < M; ++i) {
    if (first[i] < second[i]) {
      return true;
    }
    if (second[i] < first[i]) {
      return false;
    }
  }
  return N < M;
}

template<unsigned long N> // NOLINT(*-runtime-int)
void printBitset(std::ostream &stream, std::bitset<N> const &bitset) {
  stream << bitset.template to_string<char, std::char_traits<char>, std::allocator<char> >();
}

constexpr bool isPrime(unsigned int p) {
  for (unsigned int d = 2; d <= p / 2; ++d) {
    if (p % d == 0) {
      return false;
    }
  }
  return p > 1;
}
