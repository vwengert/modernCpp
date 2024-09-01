#include <gmock/gmock.h>

#include <learningtemplate.h>

TEST( learningTemplate, maxTemplateReturnMaxValues )
{
  const std::string textA = "hello";
  const std::string textB = "ahhh, what";
  constexpr auto kVALUE_A = 1;
  constexpr auto kVALUE_B = 3;

  const auto textC = maxTemplate( textA, textB );
  constexpr auto kVALUE_C = maxTemplate( kVALUE_A, kVALUE_B );

  ASSERT_EQ( textC, textA );
  ASSERT_EQ( kVALUE_C, kVALUE_B );
}
