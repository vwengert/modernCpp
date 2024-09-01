#pragma once

template< typename T >
constexpr T maxTemplate( T a, T b )
{
  return b < a ? a : b;
}