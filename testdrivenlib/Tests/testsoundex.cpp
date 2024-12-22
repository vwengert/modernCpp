#include <gmock/gmock.h>

class Soundex
{
  public:
    std::string encode( const std::string& word ) const
    {
      return zeroPad( word );
    }

  private:
    std::string zeroPad( const std::string& word ) const
    {
      return word + "000";
    }
};

using testing::Eq;

class SoundexEncoding : public testing::Test
{
  public:
    Soundex soundx;
};

TEST_F( SoundexEncoding, RetainsSoleLetterOfOneLetterWord )
{
  const auto encoded = soundx.encode( "A" );
  ASSERT_THAT( encoded, Eq("A000") );
}

TEST_F( SoundexEncoding, PadsWithZerosToEnsureThreeDigits )
{
  const auto encoded = soundx.encode( "I" );
  ASSERT_THAT( encoded, Eq("I000") );
}
