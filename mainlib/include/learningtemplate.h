#pragma once

template< typename T >
constexpr auto maxTemplate( T first, T second )
{
  return second < first ? first : second;
}

template< typename T1, typename T2, typename RT = std::decay_t< decltype( true ? T1() : T2() ) > >
constexpr RT maxTemplate( T1 first, T2 second )
{
  return second < first ? first : second;
}

template< typename T, typename Cont >
class Stack;
template< typename T, typename Cont >
std::ostream& operator<<( std::ostream& stream, Stack< T, Cont > const& stack )
{
  for( auto item : stack.m_elems )
  {
    stream << item << ' ';
  }
  stream << '\n';
  return stream;
}

template< typename T, typename Cont = std::vector< T > >
class Stack
{
  public:
    void push( T const& elem );
    void pop();
    T const& top() const;
    bool empty() const
    {
      return m_elems.empty();
    }

    friend std::ostream& operator<< < T >( std::ostream&, Stack< T > const& );

  private:
    Cont m_elems;
};

template< typename T, typename Cont >
void Stack< T, Cont >::push( T const& elem )
{
  m_elems.push_back( elem );
}

template< typename T, typename Cont >
void Stack< T, Cont >::pop()
{
  assert( !m_elems.empty() );
  m_elems.pop_back();
}

template< typename T, typename Cont >
T const& Stack< T, Cont >::top() const
{
  assert( !m_elems.empty() );
  return m_elems.back();
}
