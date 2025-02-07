#include "CppUTest/CommandLineTestRunner.h"

// NOLINTBEGIN

TEST_GROUP( FirstTestGroup ){};

TEST( FirstTestGroup, FirstTest )
{
  STRCMP_EQUAL( "Hello", "Hello" );
}

TEST( FirstTestGroup, SecondTest )
{
  LONGS_EQUAL( 1, 1 );
}

TEST_GROUP( SecondTestGroup ){};

TEST( SecondTestGroup, FirstTest )
{
  STRCMP_EQUAL( "Hello", "Hello" );
}

int main( int ac, char** av )
{
  return CommandLineTestRunner::RunAllTests( ac, av );
}

// NOLINTEND