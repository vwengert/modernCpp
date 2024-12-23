#include <gmock/gmock.h>

#include <functiontemplates.h>
#include <list>
#include <stack.h>
#include <node.h>
#include <customeroverloader.h>
#include <unordered_set>

using namespace testing;

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

  EXPECT_EQ( textC, textA );
  EXPECT_EQ( kVALUE_C, kVALUE_B );
  EXPECT_EQ( kDEDUCING_TEST, 8 );
  EXPECT_LT( kCLASS_A, classC );
  EXPECT_EQ( kMIXED_VALUES1, kFLOAT_VALUE_A );
  ASSERT_THAT( kMIXED_VALUES2, Eq(kVALUE_B) );
}

TEST( learningTemplate, usingMaxTemplateWithSpecifiedRT )
{
  constexpr auto kVALUE_A = 3;
  constexpr auto kFLOAT_VALUE_A = 5.2;

  constexpr auto kMAX_VALUE1 = ::max( kVALUE_A, kFLOAT_VALUE_A );
  constexpr auto kMAX_VALUE2 = ::max< int, double, int >( kFLOAT_VALUE_A, kVALUE_A );

  EXPECT_EQ( kMAX_VALUE1, kFLOAT_VALUE_A );
  ASSERT_THAT( kMAX_VALUE2, Eq(static_cast< int >( kFLOAT_VALUE_A )) );
}

class StackTest : public Test
{
  protected:
    Stack< int > m_stack; // NOLINT(*-non-private-member-variables-in-classes)
};

TEST_F( StackTest, stackIsEmptyAfterCreation )
{
  ASSERT_THAT( m_stack.empty(), Eq(true) );
}

TEST_F( StackTest, stackIsNoLongerEmptyAfterPush )
{
  m_stack.push( 1 );
  ASSERT_THAT( !m_stack.empty(), Eq(true) );
}

TEST_F( StackTest, stackCanPopElementWhenNotEmpty )
{
  m_stack.push( 1 );
  m_stack.pop();

  ASSERT_THAT( m_stack.empty(), Eq(true
  ) );
}

TEST_F( StackTest, stackCanReturnTopWhenNotEmpty )
{
  m_stack.push( 1 );
  m_stack.push( 2 );

  const auto top = m_stack.top();
  ASSERT_THAT( top, Eq(2) );
}

TEST_F( StackTest, stackCanReturnFirstAfterPopAndTopWhenNotEmpty )
{
  m_stack.push( 1 );
  m_stack.push( 2 );

  m_stack.pop();
  const auto top = m_stack.top();
  ASSERT_THAT( top, Eq(1) );
}

TEST_F( StackTest, stackCanBeCreatedWithListInsteadVector )
{
  Stack< int, std::list< int > > stack;
  stack.push( 1 );
  stack.push( 2 );

  const auto top = stack.top();
  ASSERT_THAT( top, Eq(2) );
}

class StackDeathTest : public Test
{
  protected:
    Stack< int > m_stack; // NOLINT(*-non-private-member-variables-in-classes)
};

TEST_F( StackDeathTest, stackCanNotPopOnEmptyStack ) // NOLINT(*-err58-cpp, *-function-cognitive-complexity)
{
#ifdef _WIN32
  // NOLINTNEXTLINE(*-avoid-goto, *-pro-type-vararg, *-err33-c)
  ASSERT_DEATH( { m_stack.pop(); }, "\\s*Assertion failed: !m_elems.empty\\s*" );
#else
  ASSERT_DEATH( { m_stack.pop(); }, "failed" );
#endif
}

TEST_F( StackDeathTest, stackCanNotTopOnEmptyStack ) // NOLINT(*-err58-cpp, *-function-cognitive-complexity)
{
#ifdef _WIN32
  // NOLINTNEXTLINE(*-avoid-goto, *-pro-type-vararg, *-err33-c)
  ASSERT_DEATH( { m_stack.top(); }, "\\s*Assertion failed: !m_elems.empty\\s*" );
#else
  ASSERT_DEATH( { m_stack.pop(); }, "failed" );
#endif
}

constexpr auto kFIVE = 5;
constexpr auto kTWO_POINT_ZERO_ONE = 2.01;

TEST( VariadicTemplate, printListWithFiveIntegers )
{
  std::stringstream stream;
  print( stream, 1, 2, 3, 4, kFIVE );
  ASSERT_THAT( stream.str(), Eq("1, 2, 3, 4, 5\n") );
}

TEST( VariadicTemplate, printListWithFiveDifferentTypes )
{
  std::stringstream stream;
  print( stream, 1, kTWO_POINT_ZERO_ONE, '3', "4", kFIVE );
  ASSERT_THAT( stream.str(), Eq("1, 2.01, 3, 4, 5\n" ) );
}

TEST( VariadicTemplate, printListWithFiveDifferentTypesAndCustomSeparators )
{
  std::stringstream stream;
  print( stream, " - ", ";", 1, kTWO_POINT_ZERO_ONE, '3', "4", kFIVE );
  ASSERT_THAT( stream.str(), Eq("1 - 2.01 - 3 - 4 - 5;" ) );
}

TEST( VariadicTemplate, foldSumWithFiveIntegers )
{
  constexpr auto kSUM = foldSum( 1, 2, 3, 4, 5 );
  ASSERT_THAT( kSUM, Eq(15) );
}

TEST( VariadicTemplate, foldSumWithFiveDifferentTypes )
{
  constexpr auto kSUM = foldSum( 1, 2.01, 3.0, 4, 5U );
  ASSERT_THAT( kSUM, Eq(15.01) );
}

TEST( VariadicTemplate, traversNode )
{
  const auto left = &Node::left;
  const auto right = &Node::right;
  auto* root = new Node( 0 );
  root->left = new Node( 1 );
  root->left->right = new Node( 2 );
  const auto* node = traverse( root, left, right );
  ASSERT_THAT( node->mValue, Eq(2) );
}

TEST( VariadicTemplate, isHomogeneousWithSameTypes )
{
  constexpr auto kRESULT = isHomogeneous( 1, 2, 3, 4, 5 );
  ASSERT_THAT( kRESULT, Eq(true) );
}

TEST( VariadicTemplate, isNotHomogeneousWithDifferentTypes )
{
  constexpr auto kRESULT = isHomogeneous( 1, 2.01, 3, 4, 5 );
  ASSERT_THAT( kRESULT, Eq(false) );
}

TEST( VariadicTemplate, printIdxFromVector )
{
  const std::vector< std::string > vec = { "good", "times", "say", "bye" };
  std::stringstream stream;
  printIdx< 2, 0, 3 >( stream, vec );
  ASSERT_THAT( stream.str(), Eq("say good bye \n") );
}

class CustomerOverloader : public Test
{
  public:
    std::unordered_set< Customer, CustomerHash, CustomerEq > customers;
    std::unordered_set< Customer, CustomerOP, CustomerOP > customersOP;
};

TEST_F( CustomerOverloader, customerEqInsertsOnlyOneCustomer )
{
  customers.insert( Customer( "John" ) );
  customers.insert( Customer( "John" ) );

  ASSERT_THAT( customers.size(), Eq(1) );
}

TEST_F( CustomerOverloader, customerEqInsertsTwoCustomers )
{
  customers.insert( Customer( "John" ) );
  customers.insert( Customer( "Jane" ) );

  ASSERT_THAT( customers.size(), Eq(2) );
}

TEST_F( CustomerOverloader, customerOpInsertsOneCustomer )
{
  customersOP.insert( Customer( "John" ) );
  customersOP.insert( Customer( "John" ) );

  ASSERT_THAT( customersOP.size(), Eq(1) );
}

TEST_F( CustomerOverloader, customerOpInsertsTwoCustomer )
{
  customersOP.insert( Customer( "John" ) );
  customersOP.insert( Customer( "Jane" ) );

  ASSERT_THAT( customersOP.size(), Eq(2) );
}

TEST( ContainerCompare, lessWithTwoArraysTrue )
{
  int first[ ] = { 1, 2, 3 };     // NOLINT(*-avoid-c-arrays)
  int second[ ] = { 1, 2, 3, 4 }; // NOLINT(*-avoid-c-arrays)

  ASSERT_THAT( less( first, second ), Eq(true) );
}

TEST( ContainerCompare, lessWithTwoArraysFalse )
{
  int first[ ] = { 1, 2, 3, 4 }; // NOLINT(*-avoid-c-arrays)
  int second[ ] = { 1, 2, 3 };   // NOLINT(*-avoid-c-arrays)

  ASSERT_THAT( less( first, second ), Eq(false) );
}

TEST( ContainerCompare, lessWithTwoEqualArrays )
{
  int first[ ] = { 1, 2, 3 };  // NOLINT(*-avoid-c-arrays)
  int second[ ] = { 1, 2, 3 }; // NOLINT(*-avoid-c-arrays)

  EXPECT_THAT( less( first, second ), Eq(false) );
  ASSERT_THAT( less( second, first), Eq(false) ); // NOLINT(*-suspicious-call-argument)
}

TEST( Bitset, printBitsetWithFiveBits )
{
  constexpr auto kBITSET_VALUE = 0b10101;
  std::stringstream stream;
  printBitset( stream, std::bitset< kFIVE >( kBITSET_VALUE ) );
  ASSERT_THAT( stream.str(), Eq("10101") );
}

TEST( StackTemplate, stackIsEmptyAfterCreation )
{
  const StackContainer< int, std::vector > stack;
  ASSERT_THAT( stack.empty(), Eq( true) );
}

TEST( IsPrimeTest, isPrime )
{
  constexpr auto kPRIME = isPrime( 7 );
  constexpr auto kNOT_PRIME = isPrime( 8 );

  EXPECT_THAT( kPRIME, Eq( true ) );
  EXPECT_THAT( kNOT_PRIME, Eq(false) );
  ASSERT_THAT( isPrime(798522), Eq(false) );
}

TEST( FindFirstNegativeDistance, findFirstNegativeDistance )
{
  std::vector< int > vec = { 1, -2, 3, 4, -5, 6 }; // NOLINT(*-magic-numbers)
  const auto kDistance = findFirstNegativeDistance( vec.begin(), vec.end() );
  const auto kDistanceTwo = findLastNegativeDistance( vec.begin(), vec.end() );

  constexpr auto kRESERVE = 900;
  vec.reserve( kRESERVE );
  std::stringstream stream;
  for_each( vec.begin() + kDistance, vec.end() - kDistanceTwo, [&stream]( const auto& value ) {
    stream << value << ", ";
  } );

  EXPECT_EQ( kDistance, 1 );
  EXPECT_EQ( kDistanceTwo, 1 );
  ASSERT_THAT( stream.str(), Eq("-2, 3, 4, -5, ") );
}

TEST( ContainerPrintMax, printMax )
{
  const std::vector< int > vec = { 1, 2, 5, 4, 2, 3 }; // NOLINT(*-magic-numbers)
  std::stringstream stream;
  printMax( stream, vec );
  ASSERT_THAT( stream.str(), Eq("5") );
}

#ifndef _WIN32
TEST( ContainerPrintMax, printMaxEmpty )
{
  constexpr std::vector< int > kVEC;
  std::stringstream stream;
  printMax( stream, kVEC );
  ASSERT_THAT( stream.str(), Eq("empty") );
}
#endif