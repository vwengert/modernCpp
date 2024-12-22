#include <gmock/gmock.h>

class Soundex
{
  public:
    std::string encode( const std::string& word )
    {
      return "A";
    }
};

using testing::Eq;

TEST( SoundexEncoding, RetainsSoleLetterOfOneLetterWord )
{
  Soundex soundx;
  auto encoded = soundx.encode( "A" );
  ASSERT_THAT( encoded, Eq("A") );
}
