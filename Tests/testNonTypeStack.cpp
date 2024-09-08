#include <gmock/gmock.h>

#include <nontypestack.h>

constexpr auto kSTACK_SIZE = 10;
constexpr auto kRANDOM_VALUE = 7;

TEST( NonTypeStackTest, pushOneElementInStack )
{
  NonTypeStack< int, kSTACK_SIZE > int20Stack;
  int20Stack.push( kRANDOM_VALUE );

  ASSERT_EQ( kRANDOM_VALUE, int20Stack.top() );
}

TEST( NonTypeStackDeathTest, topAssertsWhenEmpty )
{
  const NonTypeStack< int, kSTACK_SIZE > testStack;
  ASSERT_DEATH( { testStack.top(); }, "\\s*Assertion failed: !empty\\s*" );
}