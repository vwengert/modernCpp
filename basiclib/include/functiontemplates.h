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

constexpr bool isPrime(const unsigned int p) {
  // NOLINT(*-identifier-length)
  for (unsigned int d = 2; d <= p / 2; ++d) {
    // NOLINT(*-identifier-length)
    if (p % d == 0) {
      return false;
    }
  }
  return p > 1;
}

template<typename Iterator>
auto findFirstNegativeDistance(Iterator first, Iterator last) {
  auto iter = find_if(first, last, [](const auto &value) {
    return value < 0;
  });
  return (iter != last) ? std::distance(first, iter) : -1;
}

template<typename Iterator>
auto findLastNegativeDistance(Iterator first, Iterator last) {
  auto iter = find_if(std::make_reverse_iterator(last), std::make_reverse_iterator(first),
                      [](const auto &value) {
                        return value < 0;
                      });
  return (iter != std::make_reverse_iterator(first)) ? std::distance(std::make_reverse_iterator(last), iter) : -1;
}
