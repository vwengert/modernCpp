#include "visitor.h"
#include <iostream>

///
/// \brief Element::Element
/// \param amount
/// \param price
/// \param title
///
Element::Element( int amount, float price, std::string&& title )
  : m_amount{ amount }
  , m_price{ price }
  , m_title{ title }
{
}

void Element::changeAmount( int amount )
{
  m_amount = amount;
}

int Element::getAmount() const
{
  return m_amount;
}

float Element::getPrice() const
{
  return m_price;
}

std::string Element::getTitle()
{
  return m_title;
}

///
/// \brief Book::Book
/// \param amount
/// \param price
/// \param title
///
Book::Book( int amount, float price, std::string&& title )
  : Element( amount, price, std::move( title ) )
{
}

std::string Book::isbn() const
{
  return m_isbn;
}

void Book::setIsbn( const std::string& isbn )
{
  m_isbn = isbn;
}

std::string Book::author() const
{
  return m_author;
}

void Book::setAuthor( const std::string& author )
{
  m_author = author;
}

std::string Book::getPublisher() const
{
  return m_publisher;
}

void Book::setPublisher( const std::string& value )
{
  m_publisher = value;
}

void Book::acceptVisitor( Visitor& visitor )
{
  visitor.visitBook( *this );
}

///
/// \brief Movie::Movie
/// \param amount
/// \param price
/// \param title
///
Movie::Movie( int amount, float price, std::string&& title )
  : Element( amount, price, std::move( title ) )
{
}

void Movie::acceptVisitor( Visitor& visitor )
{
  visitor.visitMovie( *this );
}

///
/// \brief Game::Game
/// \param amount
/// \param price
/// \param title
///
Game::Game( int amount, float price, std::string&& title )
  : Element( amount, price, std::move( title ) )
{
}

void Game::acceptVisitor( Visitor& visitor )
{
  visitor.visitGame( *this );
}

///
/// \brief CalculatePriceVisitor::visitBook
/// \param book
///
void CalculatePriceVisitor::visitBook( Book& book )
{
  std::cout << "Preis Book: " << book.getPrice() << " from " << book.getTitle() << '\n';
}

void CalculatePriceVisitor::visitMovie( Movie& movie )
{
  std::cout << "Preis Movie: " << movie.getPrice() << " from " << movie.getTitle() << '\n';
}

void CalculatePriceVisitor::visitGame( Game& game )
{
  std::cout << "Preis Game: " << game.getPrice() << " from " << game.getTitle() << '\n';
}

///
/// \brief VisitorWorker::VisitorWorker
///
VisitorWorker::VisitorWorker()
{
  // NOLINTBEGIN(*magic-numbers)
  m_elements.push_back( new Book{ 13, 2.4, std::string( "Herr der Ringe" ) } );
  m_elements.push_back( new Movie{ 3, 4.1, std::string( "Spiderman" ) } );
  m_elements.push_back( new Game{ 1, 12.3, std::string( "DCS" ) } );
  m_elements.push_back( new Movie{ 1, 1.24, std::string( "The Rock" ) } );
  m_elements.push_back( new Book{ 12, 3.1, std::string( "Goetz von Berlichingen" ) } );
  // NOLINTEND(*magic-numbers)
}

VisitorWorker::~VisitorWorker()
{
  for( auto* elem : m_elements )
  {
    delete elem;
  }
  m_elements.clear();
}

std::vector< Element* > VisitorWorker::getElements()
{
  return m_elements;
}

void VisitorWorker::showPrices()
{
  CalculatePriceVisitor calculator;

  for( auto* element : m_elements )
  {
    element->acceptVisitor( calculator );
  }
}
