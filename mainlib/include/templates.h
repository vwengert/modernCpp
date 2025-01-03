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

template< typename... F >
struct overload_set;

template< typename F1 >
struct overload_set< F1 > : public F1
{
    overload_set( F1&& f1 )
      : F1( std::move( f1 ) )
    {
    }
    overload_set( const F1& f1 )
      : F1( f1 )
    {
    }
    using F1::operator();
};

template< typename F1, typename... F >
struct overload_set< F1, F... > : public F1, public overload_set< F... >
{
    overload_set( F1&& f1, F&&... f )
      : F1( std::move( f1 ) )
      , overload_set< F... >( std::forward< F >( f )... )
    {
    }
    overload_set( const F1& f1, F&&... f )
      : F1( f1 )
      , overload_set< F... >( std::forward< F >( f )... )
    {
    }
    using F1::operator();
};

template< typename... F >
auto overload( F&&... f )
{
  return overload_set< F... >( std::forward< F >( f )... );
}
