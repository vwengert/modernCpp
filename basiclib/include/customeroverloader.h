#pragma once
#include <string>

class Customer
{
  public:
    explicit Customer( const std::string& name )
      : m_name( name )
    {
    }

    std::string getName() const { return m_name; }

  private:
    std::string m_name;
};

struct CustomerEq
{
  bool operator()( Customer const& lhs, Customer const& rhs ) const
  {
    return lhs.getName() == rhs.getName();
  }
};

struct CustomerHash
{
  std::size_t operator()( Customer const& customer ) const
  {
    return std::hash< std::string >()( customer.getName() );
  }
};

template<typename... Bases>
struct Overloader : Bases...
{
  using Bases::operator()...;
};