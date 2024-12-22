#include <gmock/gmock.h>
#include "soundex.h"

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

TEST_F( SoundexEncoding, ReplacesConsonantsWithAppropriateDigits )
{
  EXPECT_THAT( soundex.encode("Ab"), Eq("A100") );
  EXPECT_THAT( soundex.encode("Ac"), Eq("A200") );
  EXPECT_THAT( soundex.encode("Ad"), Eq("A300") );

  ASSERT_THAT( soundex.encode("An"), Eq("A500") );
}

TEST_F( SoundexEncoding, IgnoresNonAlphabetics )
{
  ASSERT_THAT( soundex.encode("A#"), Eq("A000") );
}

TEST_F( SoundexEncoding, ReplacesMultipleConsonantsWithDigits )
{
  ASSERT_THAT( soundex.encode("Acdl"), Eq("A234") );
}

TEST_F( SoundexEncoding, LimitsLengthToFourCharacters )
{
  ASSERT_THAT( soundex.encode("Dcdlb").length(), Eq(4U) );
}