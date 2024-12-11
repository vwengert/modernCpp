#include <gmock/gmock.h>

#include <functiontemplates.h>
#include <list>
#include <stack.h>

struct MinimalClassForMaxTemplate
{
    int mValue = 0;
    constexpr explicit MinimalClassForMaxTemplate( const int value )
      : mValue( value )
    {
    }

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

  const auto textC = ::max( textA, textB );
  constexpr auto kVALUE_C = ::max( kVALUE_A, kVALUE_B );
  constexpr auto kDEDUCING_TEST = ::max( 3, 8 );
  const auto classC = ::max( kCLASS_A, kCLASS_B );
  constexpr auto kMIXED_VALUES1 = ::max( kVALUE_A, kFLOAT_VALUE_A );
  constexpr auto kMIXED_VALUES2 = ::max( kVALUE_B, kFLOAT_VALUE_B );

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

  constexpr auto kMAX_VALUE1 = ::max( kVALUE_A, kFLOAT_VALUE_A );
  constexpr auto kMAX_VALUE2 = ::max< int, double, int >( kFLOAT_VALUE_A, kVALUE_A );

  ASSERT_EQ( kMAX_VALUE1, kFLOAT_VALUE_A );
  ASSERT_EQ( kMAX_VALUE2, static_cast< int >( kFLOAT_VALUE_A ) );
}

class StackTest : public testing::Test
{
  protected:
    Stack< int > m_stack; // NOLINT(*-non-private-member-variables-in-classes)
};

TEST_F( StackTest, stackIsEmptyAfterCreation )
{
  ASSERT_TRUE( m_stack.empty() );
}

TEST_F( StackTest, stackIsNoLongerEmptyAfterPush )
{
  m_stack.push( 1 );
  ASSERT_TRUE( !m_stack.empty() );
}

TEST_F( StackTest, stackCanPopElementWhenNotEmpty )
{
  m_stack.push( 1 );
  m_stack.pop();

  ASSERT_TRUE( m_stack.empty() );
}

TEST_F( StackTest, stackCanReturnTopWhenNotEmpty )
{
  m_stack.push( 1 );
  m_stack.push( 2 );

  const auto top = m_stack.top();
  ASSERT_EQ( 2, top );
}

TEST_F( StackTest, stackCanReturnFirstAfterPopAndTopWhenNotEmpty )
{
  m_stack.push( 1 );
  m_stack.push( 2 );

  m_stack.pop();
  const auto top = m_stack.top();
  ASSERT_EQ( 1, top );
}

TEST_F( StackTest, stackCanBeCreatedWithListInsteadVector )
{
  Stack< int, std::list< int > > stack;
  stack.push( 1 );
  stack.push( 2 );

  const auto top = stack.top();
  ASSERT_EQ( 2, top );
}

class StackDeathTest : public testing::Test
{
  protected:
    Stack< int > m_stack; // NOLINT(*-non-private-member-variables-in-classes)
};

TEST_F( StackDeathTest, stackCanNotPopOnEmptyStack )
{
#ifdef _WIN32
  ASSERT_DEATH( { m_stack.pop(); }, "\\s*Assertion failed: !m_elems.empty\\s*" );
#else
  ASSERT_DEATH( { m_stack.pop(); }, "failed" );
#endif
}

TEST_F( StackDeathTest, stackCanNotTopOnEmptyStack )
{
#ifdef _WIN32
  ASSERT_DEATH( { m_stack.top(); }, "\\s*Assertion failed: !m_elems.empty\\s*" );
#else
  ASSERT_DEATH( { m_stack.pop(); }, "failed" );
#endif
}

template< typename T >
class Constructible
{
    static_assert( std::is_default_constructible_v< T >, "Class Constructible requires default constructible type" );
};

TEST( TemplateConcepts, check_default_constructible )
{
  constexpr auto kCONSTRUCTIBLE = Constructible< int >();
  ASSERT_NE( &kCONSTRUCTIBLE, nullptr );
}
