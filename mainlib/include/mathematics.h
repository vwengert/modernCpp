#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <string>

typedef int ( *func2 )( int n, int a );
typedef int ( *func3 )( int r, int n, int a );

void clockTime( func2, const std::string& name );
void clockTime3( func3, const std::string& name );
int multiply0( int, int );
int multiply1( int, int );
int multAcc0( int, int, int );
int multAcc1( int, int, int );
int multAcc2( int, int, int );
int multAcc3( int, int, int );
int multAcc4( int, int, int );
int multiply2( int, int );
int multiply3( int, int );
int multiply4( int, int );

void doMultiply();

#endif // MATHEMATICS_H
