#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP( FirstTestGroup )
{
};

TEST( FirstTestGroup, FirstTest )
{
  STRCMP_EQUAL( "Hello", "Hello" );
}

TEST( FirstTestGroup, SecondTest )
{
  LONGS_EQUAL( 1, 1 );
}

int main( int ac, char** av )
{
  return CommandLineTestRunner::RunAllTests( ac, av );
}