#pragma once

template< typename T >
constexpr T max( const T& first, const T& second )
{
  return second < first ? first : second;
}
