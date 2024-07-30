#include "mathematics.h"

#include <chrono>
#include <iostream>

using std::chrono::time_point;

const int kNUMBER = 1655;
const int kANOTHER = 843458;
time_point kSTART = std::chrono::steady_clock::now(); // NOLINT
time_point kEND = std::chrono::steady_clock::now();   // NOLINT

void doMultiply()
{
  clockTime( static_cast< func2 >( multiply0 ), "multiply0" );
  clockTime( static_cast< func2 >( multiply1 ), "multiply1" );
  clockTime3( static_cast< func3 >( mult_acc0 ), "mult_acc0" );
  clockTime3( static_cast< func3 >( mult_acc1 ), "mult_acc1" );
  clockTime3( static_cast< func3 >( mult_acc2 ), "mult_acc2" );
  clockTime3( static_cast< func3 >( mult_acc3 ), "mult_acc3" );
  clockTime3( static_cast< func3 >( mult_acc4 ), "mult_acc4" );
  clockTime( static_cast< func2 >( multiply2 ), "multiply2" );
  clockTime( static_cast< func2 >( multiply3 ), "multiply3" );
  clockTime( static_cast< func2 >( multiply4 ), "multiply4" );
}

void getStart()
{
  kSTART = std::chrono::steady_clock::now();
}

void getEnd()
{
  kEND = std::chrono::steady_clock::now();
  std::cout << "time needed for calculation: \t\t"
            << std::chrono::duration_cast< std::chrono::nanoseconds >( kEND - kSTART ).count() << " ns" << std::endl;
}

void clockTime( func2 function, std::string name )
{
  getStart();
  std::cout << name << " : " << kNUMBER << " x " << kANOTHER << " = " << function( kNUMBER, kANOTHER ) << std::endl;
  getEnd();
}

void clockTime3( func3 function, std::string name )
{
  getStart();
  std::cout << name << " : " << kNUMBER << " x " << kANOTHER << " = " << function( 0, kNUMBER, kANOTHER ) << std::endl;
  getEnd();
}

int half( int n )
{
  return n >> 1;
}

bool odd( int n )
{
  return ( n & 0x1 ) != 0;
}

int mult_acc0( int r, int n, int a ) // NOLINT
{
  if( n == 1 )
  {
    return r + a;
  }

  if( odd( n ) )
  {
    return mult_acc0( r + a, half( n ), a + a );
  }
  return mult_acc0( r, half( n ), a + a );
}

int mult_acc1( int r, int n, int a ) // NOLINT
{
  if( n == 1 )
  {
    return r + a;
  }

  if( odd( n ) )
  {
    r = r + a;
  }

  return mult_acc1( r, half( n ), a + a );
}

int mult_acc2( int r, int n, int a ) // NOLINT
{
  if( odd( n ) )
  {
    r = r + a;

    if( n == 1 )
    {
      return r;
    }
  }

  return mult_acc2( r, half( n ), a + a );
}

int mult_acc3( int r, int n, int a ) // NOLINT
{
  if( odd( n ) )
  {
    r = r + a;

    if( n == 1 )
    {
      return r;
    }
  }

  n = half( n );
  a = a + a;
  return mult_acc3( r, half( n ), a + a );
}

int mult_acc4( int r, int n, int a ) // NOLINT
{
  while( true )
  {
    if( odd( n ) )
    {
      r = r + a;

      if( n == 1 )
      {
        return r;
      }
    }

    n = half( n );
    a = a + a;
  }
}

int multiply0( int n, int a ) // NOLINT
{
  if( n == 1 )
  {
    return a;
  }

  return multiply0( n - 1, a ) + a;
}

int multiply1( int n, int a ) // NOLINT
{
  if( n == 1 )
  {
    return a;
  }

  int result = multiply1( half( n ), a + a );

  if( odd( n ) )
  {
    result = result + a;
  }

  return result;
}

int multiply2( int n, int a ) // NOLINT
{
  if( n == 1 )
  {
    return a;
  }

  return mult_acc4( a, n - 1, a );
}

int multiply3( int n, int a ) // NOLINT
{
  while( !odd( n ) )
  {
    a = a + a;
    n = half( n );
  }

  if( n == 1 )
  {
    return a;
  }

  return mult_acc4( a, n - 1, a );
}

int multiply4( int n, int a ) // NOLINT
{
  while( !odd( n ) )
  {
    a = a + a;
    n = half( n );
  }

  if( n == 1 )
  {
    return a;
  }

  return mult_acc4( a, half( n - 1 ), a + a );
}
