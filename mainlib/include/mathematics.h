#ifndef MATHEMATICS_H
#define MATHEMATICS_H

typedef int( *func2 )( int n, int a );
typedef int( *func3 )( int r, int n, int a );

void clockTime( func2 );
void clockTime3( func3 );
int multiply0( int, int );
int multiply1( int, int );
int mult_acc0( int, int, int );
int mult_acc1( int, int, int );
int mult_acc2( int, int, int );
int mult_acc3( int, int, int );
int mult_acc4( int, int, int );
int multiply2( int, int );
int multiply3( int, int );
int multiply4( int, int );

void doMultiply();


#endif // MATHEMATICS_H
