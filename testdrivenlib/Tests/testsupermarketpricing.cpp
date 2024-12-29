#include "gmock/gmock.h"

class SupermarketPricing
{
  public:
    double getPrice( const char* article, const int quantity = 1 ) const
    {
      return m_price.at( article ) * quantity;
    }

    void setPrice( const char* article, const int price )
    {
      m_price[ article ] = price;
    }

  private:
    std::unordered_map< std::string, double > m_price;
};

using namespace testing;

class SupermarketPricingTest : public Test
{
  public:
    SupermarketPricing pricing;

    void SetUp() override
    {
      pricing.setPrice( "A", 50 );
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
  pricing.setPrice( "A", 30 );
  ASSERT_THAT( pricing.getPrice( "A", 3 ), DoubleEq(90) );
}

TEST_F( SupermarketPricingTest, CompareTwoPricesToBeNotEqual )
{
  pricing.setPrice( "B", 50 );
  EXPECT_THAT( pricing.getPrice("A"), DoubleEq( pricing.getPrice( "B" )) );
  pricing.setPrice( "B", 30 );
  ASSERT_THAT( pricing.getPrice( "A" ), Ne(pricing.getPrice( "B" )) );
}