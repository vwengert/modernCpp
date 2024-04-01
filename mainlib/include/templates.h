#pragma once

#include <iostream>
#include <utility>
template< typename... T >
auto sum( const T&... x )
{
  return ( x + ... );
}

template< typename... T >
struct Group;

template< typename T1 >
struct Group< T1 >
{
    T1 t1_;
    Group() = default;
    explicit Group( const T1& t1 )
      : t1_( t1 )
    {
    }
    explicit Group( T1&& t1 )
      : t1_( std::move( t1 ) )
    {
    }
    explicit operator const T1&() const
    {
      return t1_;
    }
    explicit operator T1&()
    {
      return t1_;
    }
};

template< typename T1, typename... T >
struct Group< T1, T... > : Group< T... >
{
    T1 t1_;
    Group() = default;
    explicit Group( const T1& t1, T&&... t )
      : Group< T... >( std::forward< T >( t )... )
      , t1_( t1 )
    {
    }
    explicit Group( T1&& t1, T&&... t )
      : Group< T... >( std::forward< T >( t )... )
      , t1_( std::move( t1 ) )
    {
    }
    explicit operator const T1&() const
    {
      return t1_;
    }
    explicit operator T1&()
    {
      return t1_;
    }
};

template< typename... T >
auto makeGroup( T&&... t )
{
  return Group< T... >( std::forward< T >( t )... );
}

template< typename N, typename D >
class Ratio
{
  public:
    Ratio()
      : num_{}
      , denom_{}
    {
    }
    Ratio( const N& num, const D& denom )
      : num_{ num }
      , denom_{ denom }
    {
    }
    explicit operator double() const
    {
      return double( num_ ) / double( denom_ );
    }

  private:
    N num_;
    D denom_;
};

template< typename T, typename U >
class MyPair
{
    T data01_;
    U data02_;

  public:
    MyPair( const T& t, const U& u )
      : data01_{ t }
      , data02_{ u }
    {
    }
    void print( std::ostream& os ) const
    {
      os << data01_ << " : " << data02_ << std::endl;
    }
};

template< typename Range >
void printRange( Range const& range )
{
  using std::begin;
  using std::end;
  for( auto pos = begin( range ); pos != end( range ); ++pos )
  {
    pos->get()->print( std::cout );
  }
}

template< typename T >
struct Widget
{
    T value;
};

template< typename T >
void swap( Widget< T >& lhs, Widget< T >& rhs )
{
  using std::swap;
  swap( lhs.value, rhs.value );
}
