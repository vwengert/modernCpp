#pragma once

template< typename T >
constexpr auto maxTemplate( T a, T b )
{
  return b < a ? a : b;
}

template< typename T1, typename T2, typename RT = std::decay_t< decltype( true ? T1() : T2() ) > >
constexpr RT maxTemplate( T1 a, T2 b )
{
  return b < a ? a : b;
}
