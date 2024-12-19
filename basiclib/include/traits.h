#pragma once

template<typename T>
struct AccumTraits;

template<>
struct AccumTraits<char> {
  using AccT = int;
  static constexpr AccT kZERO = 0;
};

template<>
struct AccumTraits<int> {
  using AccT = long; // NOLINT(*-runtime-int)
  static constexpr AccT kZERO = 0;
};

template<>
struct AccumTraits<unsigned int> {
  using AccT = unsigned long; // NOLINT(*-runtime-int)
  static constexpr AccT kZERO = 0;
};

template<>
struct AccumTraits<float> {
  using AccT = double;
  static constexpr AccT kZERO = 0.0;
};

class SumPolicy {
public:
  template<typename T1, typename T2>
  static void accumulate(T1 &total, T2 const &value) {
    total += value;
  }
};

template<typename T,
  typename Policy = SumPolicy,
  typename Traits = AccumTraits<T> >
auto accum(T const *beg, T const *end, T initValue = Traits::kZERO) {
  using AccT = typename AccumTraits<T>::AccT;
  AccT total = initValue;
  while (beg != end) {
    Policy::accumulate(total, *beg);
    ++beg; // NOLINT(*-pro-bounds-pointer-arithmetic)
  }
  return total;
}
