#include "gmock/gmock.h"

class SupermarketPricing
{
  public:
    double getPrice( const char* article )
    {
      return 50;
    }
};

using namespace testing;

TEST( SupermarketPricing, GetPriceOfOneItem )
{
  SupermarketPricing pricing;
  ASSERT_THAT( pricing.getPrice( "A" ), DoubleEq(50) );
}
