#pragma once

template< typename T1, typename T2 >
constexpr auto max( const T1& first, const T2& second )
{
  return second < first ? first : second;
}
