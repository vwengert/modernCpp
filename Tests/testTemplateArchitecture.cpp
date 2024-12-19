#include <gmock/gmock.h>

#include "geometry.h"

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


TEST( staticPolymorphism, myDraw )
{
  std::vector< std::variant< Cirle, Line > > vec;
  vec.emplace_back( Cirle() );
  vec.emplace_back( Line() );
  std::stringstream stream;
  for(const auto& obj : vec)
  {
    std::visit( [&stream]( const auto& object ) { myDraw( stream, object ); }, obj );
  }

  ASSERT_EQ( stream.str(), "Circle\nLine\n" );
}