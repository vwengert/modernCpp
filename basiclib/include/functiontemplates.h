#pragma once
#include <cstring>
#include <type_traits>
#include <iostream>

inline char const* max( char const* first, char const* second )
{
  return std::strcmp( second, first ) < 0 ? first : second;
}

template< typename T1, typename T2 >
constexpr auto max( T1 first, T2 second ) -> std::common_type_t< T1, T2 >
{
  return second < first ? first : second;
}

template< typename RT, typename T1, typename T2 >
constexpr RT max( T1 first, T2 second )
{
  return second < first ? first : second;
}

template< typename T >
T* max( T* first, T* second )
{
  return *second < *first ? first : second;
}

template<typename T>
void print(std::ostream& stream, const char* /*sep*/,  const char* end, T arg)
{
  stream << arg << end;
}

template<typename T, typename... Types>
void print(std::ostream& stream, const char* sep, const char* end, T firstArg, Types... args)
{
  stream << firstArg << sep;
  print(stream, sep, end, args...);
}

template<typename T, typename... Types>
void print(std::ostream& stream, T firstArg, Types... args)
{
  print(stream, ", ", "\n", firstArg, args...);
}

template<typename... T>
constexpr auto foldSum(T... args)
{
  return (... + args);
}
