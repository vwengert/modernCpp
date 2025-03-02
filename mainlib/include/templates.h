#pragma once

#include <iostream>
#include <utility>
template< typename... T >
auto sum( const T&... operand )
{
  return ( operand + ... );
}

template< typename... T >
struct Group;

template< typename T1 >
struct Group< T1 >
{
    T1 t1Val;
    Group() = default;
    explicit Group( const T1& t1Val_ )
      : t1Val( t1Val_ )
    {
    }
    explicit Group( T1&& t1Val_ )
      : t1Val( std::move( t1Val_ ) )
    {
    }
    explicit operator const T1&() const
    {
      return t1Val;
    }
    explicit operator T1&()
    {
      return t1Val;
    }
};

template< typename N, typename D >
class Ratio
{
  public:
    Ratio()
      : m_num{}
      , m_denom{}
    {
    }
    Ratio( const N& num, const D& denom )
      : m_num{ num }
      , m_denom{ denom }
    {
    }
    explicit operator double() const
    {
      return double( m_num ) / double( m_denom );
    }

  private:
    N m_num;
    D m_denom;
};

template< typename T, typename U >
class MyPair
{
    T m_data01;
    U m_data02;

  public:
    MyPair( const T& tVal, const U& uVal )
      : m_data01{ tVal }
      , m_data02{ uVal }
    {
    }
    void print( std::ostream& stream ) const
    {
      stream << m_data01 << " : " << m_data02 << std::endl;
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
    explicit overload_set( F1&& f1Val )
      : F1( std::move( f1Val ) )
    {
    }
    explicit overload_set( const F1& f1Val )
      : F1( f1Val )
    {
    }
    using F1::operator();
};

template< typename F1, typename... F >
struct overload_set< F1, F... > : public F1, public overload_set< F... >
{
    explicit overload_set( F1&& f1Val, F&&... fVals )
      : F1( std::move( f1Val ) )
      , overload_set< F... >( std::forward< F >( fVals )... )
    {
    }
    explicit overload_set( const F1& f1Val, F&&... fVals )
      : F1( f1Val )
      , overload_set< F... >( std::forward< F >( fVals )... )
    {
    }
    using F1::operator();
};

template< typename... F >
auto overload( F&&... fVals )
{
  return overload_set< F... >( std::forward< F >( fVals )... );
}
