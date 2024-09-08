#pragma once

#include <array>
#include <cassert>

template< typename T, std::size_t Maxsize >
class NonTypeStack
{
  public:
    NonTypeStack();
    void push( T const& elem );
    void pop();
    T const& top() const;
    bool empty() const
    {
      return m_numElems == 0;
    }
    std::size_t size() const
    {
      return m_numElems;
    }

  private:
    std::array< T, Maxsize > m_elems;
    std::size_t m_numElems{ 0 };
};

template< typename T, std::size_t Maxsize >
NonTypeStack< T, Maxsize >::NonTypeStack()
{
}

template< typename T, std::size_t Maxsize >
void NonTypeStack< T, Maxsize >::push( T const& elem )
{
  assert( m_numElems < Maxsize );
  m_elems[ m_numElems ] = elem;
  ++m_numElems;
}

template< typename T, std::size_t Maxsize >
void NonTypeStack< T, Maxsize >::pop()
{
  assert( !empty() );
  --m_numElems;
}

template< typename T, std::size_t Maxsize >
T const& NonTypeStack< T, Maxsize >::top() const
{
  assert( !empty() );
  return m_elems[ m_numElems - 1 ];
}
