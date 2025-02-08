#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>

class Visitor;

class Element
{
  public:
    explicit Element( int amount, float price, std::string&& title );
    virtual ~Element() = default;
    void changeAmount( int amount );
    int getAmount();
    float getPrice();
    std::string getTitle();
    virtual void acceptVisitor( Visitor& visitor ) = 0;

  private:
    int m_amount;
    float m_price;
    std::string m_title;
};

class Book : public Element
{
  public:
    explicit Book( int amount, float price, std::string&& title );
    std::string isbn() const;
    void setIsbn( const std::string& isbn );

    std::string author() const;
    void setAuthor( const std::string& author );

    std::string getPublisher() const;
    void setPublisher( const std::string& value );

  private:
    std::string m_isbn;
    std::string m_author;
    std::string publisher;

    void acceptVisitor( Visitor& visitor ) override;
};

class Movie : public Element
{
  public:
    explicit Movie( int amount, float price, std::string&& title );

  public:
    void acceptVisitor( Visitor& visitor ) override;
};

class Game : public Element
{
  public:
    explicit Game( int amount, float price, std::string&& title );

  public:
    void acceptVisitor( Visitor& visitor ) override;
};

class Visitor
{
  public:
    virtual void visitBook( Book& book ) = 0;
    virtual void visitMovie( Movie& movie ) = 0;
    virtual void visitGame( Game& game ) = 0;
};

class CalculatePriceVisitor : public Visitor
{
  public:
    void visitBook( Book& book ) override;
    void visitMovie( Movie& movie ) override;
    void visitGame( Game& game ) override;
};

class VisitorWorker
{
  public:
    VisitorWorker();
    ~VisitorWorker();
    std::vector< Element* > getElements();
    void showPrices();

  private:
    std::vector< Element* > m_elements;
};

struct Print
{
    void operator()( int value ) const
    {
      std::cout << "int: " << value << '\n';
    }
    void operator()( double value ) const
    {
      std::cout << "double: " << value << '\n';
    }
    void operator()( std::string const& value ) const
    {
      std::cout << "string: " << value << '\n';
    }
};

using varTypes = std::variant< int, double, std::string >;
using varList = std::vector< varTypes >;

inline varList createList()
{
  varList list{};
  list.push_back( 31 );
  list.push_back( 51.3 );
  list.push_back( "31" );
  list.push_back( "hi there" );
  list.push_back( 41 );
  return list;
}

inline void printList( varList const& list )
{
  for( auto const& v : list )
  {
    std::visit( Print{}, v );
  }
}

inline void doVariantVisitorWork()
{
  auto list = createList();
  printList( list );
}
