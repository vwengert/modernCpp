#include <gmock/gmock.h>

#include <learningtemplate.h>

struct MinimalClassForMaxTemplate
{
    int mValue = 0;
    bool operator<( const MinimalClassForMaxTemplate& rhs ) const
    {
      return mValue < rhs.mValue;
    }
};

TEST( learningTemplate, maxTemplateReturnMaxValues )
{
  const std::string textA = "hello";
  const std::string textB = "ahhh, what";
  constexpr auto kVALUE_A = 3;
  constexpr auto kVALUE_B = 7;
  constexpr auto kFLOAT_VALUE_A = 5.2;
  constexpr auto kFLOAT_VALUE_B = 4.7;
  constexpr MinimalClassForMaxTemplate kCLASS_A( kVALUE_A );
  constexpr MinimalClassForMaxTemplate kCLASS_B( kVALUE_B );

  const auto textC = maxTemplate( textA, textB );
  constexpr auto kVALUE_C = maxTemplate( kVALUE_A, kVALUE_B );
  constexpr auto kDEDUCING_TEST = maxTemplate( 3, 8 );
  const auto classC = maxTemplate( kCLASS_A, kCLASS_B );
  constexpr auto kMIXED_VALUES1 = maxTemplate( kVALUE_A, kFLOAT_VALUE_A );
  constexpr auto kMIXED_VALUES2 = maxTemplate( kVALUE_B, kFLOAT_VALUE_B );

  ASSERT_EQ( textC, textA );
  ASSERT_EQ( kVALUE_C, kVALUE_B );
  ASSERT_EQ( kDEDUCING_TEST, 8 );
  ASSERT_LT( kCLASS_A, classC );
  ASSERT_EQ( kMIXED_VALUES1, kFLOAT_VALUE_A );
  ASSERT_EQ( kMIXED_VALUES2, kVALUE_B );
}

TEST( learningTemplate, usingMaxTemplateWithSpecifiedRT )
{
  constexpr auto kVALUE_A = 3;
  constexpr auto kFLOAT_VALUE_A = 5.2;

  constexpr auto kMAX_VALUE1 = maxSpecifiedRTTemplate( kVALUE_A, kFLOAT_VALUE_A );
  constexpr auto kMAX_VALUE2 = maxSpecifiedRTTemplate< int, double, int >( kVALUE_A, kFLOAT_VALUE_A );

  ASSERT_EQ( kMAX_VALUE1, kFLOAT_VALUE_A );
  ASSERT_EQ( kMAX_VALUE2, static_cast< int >( kFLOAT_VALUE_A ) );
}
