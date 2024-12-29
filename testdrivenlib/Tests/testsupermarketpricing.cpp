#include "gmock/gmock.h"

class SupermarketPricing
{
  public:
    double getPrice( const char* article, const int quantity = 1 ) const
    {
      return m_price * quantity;
    }

    void setPrice( const int price )
    {
      m_price = price;
    }

  private:
    int m_price{ 0 };
};

using namespace testing;

class SupermarketPricingTest : public Test
{
  public:
    SupermarketPricing pricing;

    void SetUp() override
    {
      pricing.setPrice( 50 );
    }
};

TEST_F( SupermarketPricingTest, GetPriceOfOneItem )
{
  ASSERT_THAT( pricing.getPrice( "A" ), DoubleEq(50) );
}

TEST_F( SupermarketPricingTest, GetPriceOfTwoItems )
{
  ASSERT_THAT( pricing.getPrice( "A", 2 ), DoubleEq(100) );
}

TEST_F( SupermarketPricingTest, SetPriceOfItemAndGetThePriveOfThreeItems )
{
  pricing.setPrice( 30 );
  ASSERT_THAT( pricing.getPrice( "A", 3 ), DoubleEq(90) );
}
