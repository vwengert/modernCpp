#include "basicLibrary.h"
#include "modernLibrary.h"
#include "moderncpp_version.h"
#include <algorithm>
#include <iostream>

#include <cassert>
#include <vector>

template< typename T >
class Stack
{
  private:
    std::vector< T > m_elements;

  public:
    void push( const T& element )
    {
      m_elements.push_back( element );
    }
    void pop()
    {
      assert( !m_elements.empty() && "Stack is empty" );
      m_elements.pop_back();
    }
    T const& top() const
    {
      assert( !m_elements.empty() && "Stack is empty" );
      return m_elements.back();
    }
    bool empty() const
    {
      return m_elements.empty();
    }
    size_t size() const
    {
      return m_elements.size();
    }
};

auto main() -> int
{
  std::cout << "Version: " << PROJECT_CPP_VERSION << std::endl;

  Stack< int > intStack;
  intStack.push( 10 );
  intStack.push( 20 );
  std::cout << "Top element: " << intStack.top() << std::endl;
  intStack.pop();
  std::cout << "Top element after pop: " << intStack.top() << std::endl;
  intStack.pop();

  return 0;
}
