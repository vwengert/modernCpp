#pragma once

template<typename T>
concept GeoObj = requires( T obj )
{
  { obj.draw( std::declval< std::ostream& >() ) };
  { obj.centerOfGravity() };
};

template<typename T>
  requires GeoObj< T >
void myDraw( std::ostream& stream, T const& obj )
{
  obj.draw( stream );
}

template<typename GeoObj1, typename GeoObj2>
  requires GeoObj< GeoObj1 > && GeoObj< GeoObj2 >
void distance( std::ostream& stream, GeoObj1 const& obj1, GeoObj2 const& obj2 )
{
  stream << obj1.centerOfGravity() << " - " << obj2.centerOfGravity() << '\n';
}

template<typename T>
  requires GeoObj< T >
void drawElements( std::ostream& stream, std::vector< T > const& obj )
{
  obj.draw( stream );
}