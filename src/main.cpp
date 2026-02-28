#include <iostream>

template< typename T >
T min( T a, T b ) // NOLINT
{
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return ( a < b ) ? a : b;
}

template< typename T, typename... Args >
T min( T a, Args... args ) // NOLINT
{
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return min( a, min( args... ) );
}

template< typename T, typename... Args >
T sum( T a, Args... args ) // NOLINT
{
  if constexpr( sizeof...( args ) == 0 )
  {
    return a;
  }
  else
  {
    return a + sum( args... );
  }
}

int main()
{
  std::cout << "min(42.0, 7.5)=" << ::min< double >( 42.0, 7.5, 3.0, 7.0, 5., 4.0 ) << std::endl; // NOLINT
  std::cout << "sum(1, 2, 3, 4, 5)=" << ::sum( 1, 2, 3, 4, 5 ) << std::endl;                      // NOLINT
  return 0;
}