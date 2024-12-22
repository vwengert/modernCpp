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

using namespace testing; // NOLINT(*-build-using-namespace)

class SoundexEncoding : public Test
{
  public:
    Soundex soundex;
};

TEST_F( SoundexEncoding, RetainsSoleLetterOfOneLetterWord )
{
  ASSERT_THAT( soundex.encode("A"), Eq("A000") );
}

TEST_F( SoundexEncoding, PadsWithZerosToEnsureThreeDigits )
{
  ASSERT_THAT( soundex.encode("I"), Eq("I000") );
}
