#include "mathematics.h"

#include <chrono>
#include <iostream>

const int n = 1655;
const int a = 843458;
static std::chrono::time_point start = std::chrono::steady_clock::now();
static std::chrono::time_point end = std::chrono::steady_clock::now();

void doMultiply()
{
    clockTime( ( func2 )multiply0, "multiply0" );
    clockTime( ( func2 )multiply1, "multiply1" );
    clockTime3( ( func3 )mult_acc0, "mult_acc0" );
    clockTime3( ( func3 )mult_acc1, "mult_acc1" );
    clockTime3( ( func3 )mult_acc2, "mult_acc2" );
    clockTime3( ( func3 )mult_acc3, "mult_acc3" );
    clockTime3( ( func3 )mult_acc4, "mult_acc4" );
    clockTime( ( func2 )multiply2, "multiply2" );
    clockTime( ( func2 )multiply3, "multiply3" );
    clockTime( ( func2 )multiply4, "multiply4" );
}

void getStart()
{
    start = std::chrono::steady_clock::now();
}

void getEnd()
{
    end = std::chrono::steady_clock::now();
    std::cout << "time needed for calculation: \t\t"
              << std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count() << " ns" << std::endl;
}

void clockTime( func2 function, std::string name )
{
    getStart();
    std::cout << name << " : " << n << " x " << a << " = " << function( n, a ) << std::endl;
    getEnd();
}

void clockTime3( func3 function, std::string name )
{
    getStart();
    std::cout <<  name << " : " << n << " x " << a << " = " << function( 0, n, a ) << std::endl;
    getEnd();
}

int half( int n )
{
    return n >> 1;
}

bool odd( int n )
{
    return n & 0x1;
}

int mult_acc0( int r, int n, int a )
{
    if( n == 1 ) {
        return r + a;
    }

    if( odd( n ) ) {
        return mult_acc0( r + a, half( n ), a + a );

    } else {
        return mult_acc0( r, half( n ), a + a );
    }
}

int mult_acc1( int r, int n, int a )
{
    if( n == 1 ) {
        return r + a;
    }

    if( odd( n ) ) {
        r = r + a;
    }

    return mult_acc1( r, half( n ), a + a );
}

int mult_acc2( int r, int n, int a )
{
    if( odd( n ) ) {
        r = r + a;

        if( n == 1 ) {
            return r;
        }
    }

    return mult_acc2( r, half( n ), a + a );
}

int mult_acc3( int r, int n, int a )
{
    if( odd( n ) ) {
        r = r + a;

        if( n == 1 ) {
            return r;
        }
    }

    n = half( n );
    a = a + a;
    return mult_acc3( r, half( n ), a + a );
}

int mult_acc4( int r, int n, int a )
{
    while( true ) {
        if( odd( n ) ) {
            r = r + a;

            if( n == 1 ) {
                return r;
            }
        }

        n = half( n );
        a = a + a;
    }
}

int multiply0( int n, int a )
{
    if( n == 1 ) {
        return a;
    }

    return multiply0( n - 1, a ) + a;
}

int multiply1( int n, int a )
{
    if( n == 1 ) {
        return a;
    }

    int result = multiply1( half( n ), a + a );

    if( odd( n ) ) {
        result = result + a;
    }

    return result;
}

int multiply2( int n, int a )
{
    if( n == 1 ) {
        return a;
    }

    return mult_acc4( a, n - 1, a );
}

int multiply3( int n, int a )
{
    while( !odd( n ) ) {
        a = a + a;
        n = half( n );
    }

    if( n == 1 ) {
        return a;
    }

    return mult_acc4( a, n - 1, a );
}

int multiply4( int n, int a )
{
    while( !odd( n ) ) {
        a = a + a;
        n = half( n );
    }

    if( n == 1 ) {
        return a;
    }

    return mult_acc4( a, half( n - 1 ), a + a );
}
