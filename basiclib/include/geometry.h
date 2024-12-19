#pragma once

template<typename GeoObj>
void myDraw( std::ostream& stream, GeoObj const& obj )
{
  obj.draw( stream );
}