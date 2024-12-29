#include "gmock/gmock.h"

class SupermarketPricing
{
  public:
    double getPrice( const char* article, int quantity = 1 )
    {
      return 50 * quantity;
    }
};

using namespace testing;

class SupermarketPricingTest : public Test
{
  public:
    SupermarketPricing pricing;
};

TEST_F( SupermarketPricingTest, GetPriceOfOneItem )
{
  ASSERT_THAT( pricing.getPrice( "A" ), DoubleEq(50) );
}

TEST_F( SupermarketPricingTest, GetPriceOfTwoItems )
{
  ASSERT_THAT( pricing.getPrice( "A", 2 ), DoubleEq(100) );
}