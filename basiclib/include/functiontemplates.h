#pragma once
#include <cstring>
#include <type_traits>

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
