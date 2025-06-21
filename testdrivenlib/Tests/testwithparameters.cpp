#include <gmock/gmock.h>

using namespace testing; // NOLINT(google-build-using-namespace)

class Adder
{
  public:
    static int sum( const int valA, const int valB )
    {
      return valA + valB;
    }
};

struct SumCase
{
    int a, b, expected;

    SumCase( const int anA, const int anB, const int anExpected )
      : a( anA )
      , b( anB )
      , expected( anExpected )
    {
    }
};

class AnAdder : public TestWithParam< SumCase >
{
};

TEST_P( AnAdder, GeneratesLotsOfSumsFromTwoNumbers )
{
  const SumCase input = GetParam();
  ASSERT_THAT( Adder::sum( input.a, input.b ), Eq( input.expected ) );
}
// NOLINTNEXTLINE(*avoid-c-arrays,*avoid-non-const-global-variables)
SumCase sums[] = {
  SumCase( 1, 1, 2 ),
  SumCase( 1, 2, 3 ),
  SumCase( 2, 1, 3 ),
  SumCase( 2, 2, 4 ),
};

INSTANTIATE_TEST_CASE_P( BulkTest, AnAdder, ValuesIn( sums ) );
