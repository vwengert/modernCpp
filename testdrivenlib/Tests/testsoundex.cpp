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

TEST_F( SoundexEncoding, IgnoresVowelLikeLetters )
{
  ASSERT_THAT( soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234") );
}

TEST_F( SoundexEncoding, CombinesDuplicateEncodings )
{
  EXPECT_THAT( soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')) );
  EXPECT_THAT( soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')) );
  EXPECT_THAT( soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')) );
  ASSERT_THAT( soundex.encode("Abfcgdt"), Eq("A123") );
}

TEST_F( SoundexEncoding, UppercasesFirstLetter )
{
  ASSERT_THAT( soundex.encode("abcd"), StartsWith("A") );
}
