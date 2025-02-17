#include <gmock/gmock.h>

#include "geometry.h"
#include "traits.h"

using namespace testing;

TEST( staticPolymorphism, myDraw )
{
  class Cirle
  {
    public:
      static void draw( std::ostream& stream )
      {
        stream << "Circle" << '\n';
      }

      static void centerOfGravity()
      {
      }
  };

  class Line
  {
    public:
      static void draw( std::ostream& stream )
      {
        stream << "Line" << '\n';
      }

      static void centerOfGravity()
      {
      }
  };
  std::vector< std::variant< Cirle, Line > > vec;
  vec.emplace_back( Cirle() );
  vec.emplace_back( Line() );
  std::stringstream stream;
  for(const auto& obj : vec)
  {
    std::visit( [&stream]( const auto& object ) { myDraw( stream, object ); }, obj );
  }

  ASSERT_THAT( stream.str(), Eq("Circle\nLine\n") );
}

TEST( Accumulate, numbers )
{
  const int num[ ] = { 1, 2, 3, 4, 5 }; // NOLINT(*-avoid-c-arrays)
  // NOLINTNEXTLINE(*-pro-bounds-array-to-pointer-decay, *-pro-bounds-pointer-arithmetic)
  const auto sum = accum( num, num + 5 );
  ASSERT_THAT( sum, Eq(15) );
}

TEST( Accumulate, text )
{
  constexpr char kNAME[ ] = "hello"; // NOLINT(*-avoid-c-arrays)
  constexpr int kLENGTH = sizeof( kNAME ) - 1;
  // NOLINTNEXTLINE(*-signed-char-misuse, *-str34-c, *-pro-bounds-array-to-pointer-decay, *-pro-bounds-pointer-arithmetic)
  const auto avgChar = static_cast< char >( accum( kNAME, kNAME + kLENGTH ) / kLENGTH );
  ASSERT_THAT( avgChar, Eq('j') );
}

class MultPolicy
{
  public:
    template<typename T1, typename T2>
    static void accumulate( T1& total, T2 const& value )
    {
      total *= value;
    }
};

TEST( Accumulate, withOwnPolicy )
{
  const int num[ ] = { 1, 2, 3, 4, 5 }; // NOLINT(*-avoid-c-arrays)
  // NOLINTNEXTLINE(*-pro-bounds-array-to-pointer-decay, *-pro-bounds-pointer-arithmetic)
  const auto sum = accum< int, MultPolicy >( num, num + 5, 1 );
  ASSERT_THAT( sum, Eq(120) );
}

#ifndef _WIN32
TEST( ElementType, printElementTypeVectorAndArray )
{
  const std::vector< bool > vec;
  int arr[ 5 ]; // NOLINT(*-avoid-c-arrays, *-magic-numbers)
  std::stringstream stream;
  printElementType( stream, vec );
  printElementType( stream, arr );

  ASSERT_THAT( stream.str(), Eq("Container of: b elements.\nContainer of: i elements.\n") );
}
#endif