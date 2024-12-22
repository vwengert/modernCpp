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
  ASSERT_THAT( soundex.encode("Ab"), Eq("A100") );
}