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

using namespace testing; // NOLINT(google-build-using-namespace)

constexpr auto kBASE_PRICE = 50;
constexpr auto kLOW_PRICE = 30;

class SupermarketPricingTest : public Test
{
  public:
    SupermarketPricing pricing;

    void SetUp() override
    {
      pricing.setPrice( "A", kBASE_PRICE );
    }
};

TEST_F( SupermarketPricingTest, GetPriceOfOneItem )
{
  ASSERT_THAT( pricing.getPrice( "A" ), DoubleEq( 50 ) );
}

TEST_F( SupermarketPricingTest, GetPriceOfTwoItems )
{
  ASSERT_THAT( pricing.getPrice( "A", 2 ), DoubleEq( 100 ) );
}

TEST_F( SupermarketPricingTest, SetPriceOfItemAndGetThePriveOfThreeItems )
{
  pricing.setPrice( "A", kLOW_PRICE );
  ASSERT_THAT( pricing.getPrice( "A", 3 ), DoubleEq( 90 ) );
}

TEST_F( SupermarketPricingTest, CompareTwoPricesToBeNotEqual )
{
  pricing.setPrice( "B", kBASE_PRICE );
  EXPECT_THAT( pricing.getPrice( "A" ), DoubleEq( pricing.getPrice( "B" ) ) );
  pricing.setPrice( "B", kLOW_PRICE );
  ASSERT_THAT( pricing.getPrice( "A" ), Ne( pricing.getPrice( "B" ) ) );
}
