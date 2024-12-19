#pragma once

template<typename T>
struct AccumTraits;

template<>
struct AccumTraits<char> {
  using AccT = int;
};

template<>
struct AccumTraits<int> {
  using AccT = long; // NOLINT(*-runtime-int)
};

template<>
struct AccumTraits<unsigned int> {
  using AccT = unsigned long; // NOLINT(*-runtime-int)
};

template<>
struct AccumTraits<float> {
  using AccT = double;
};


template<typename T>
auto accum(T const *beg, T const *end) {
  using AccT = typename AccumTraits<T>::AccT;
  AccT total{};
  while (beg != end) {
    total += *beg;
    ++beg; // NOLINT(*-pro-bounds-pointer-arithmetic)
  }
  return total;
}
