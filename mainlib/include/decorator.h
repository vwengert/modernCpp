#pragma once

#include <cmath>
#include <iostream>
#include <memory>

class Item
{
  public:
    virtual ~Item() = default;
    virtual double price() const = 0; // please never use double for any kind of money!
};

class DecoratedItem : public Item
{
  public:
    explicit DecoratedItem( std::unique_ptr< Item > item )
      : m_item{ std::move( item ) }
    {
      if( !m_item )
      {
        throw std::invalid_argument( "Invalid item" );
      }
    }

  protected:
    Item& item()
    {
      return *m_item;
    }
    Item const& item() const
    {
      return *m_item;
    }

  private:
    std::unique_ptr< Item > m_item;
};

class CppBook : public Item
{
  public:
    CppBook( std::string title, double price )
      : m_title{ std::move( title ) }
      , m_price{ price }
    {
    }
    std::string const& title() const
    {
      return m_title;
    }
    double price() const override
    {
      return m_price;
    }

  private:
    std::string m_title{};
    double m_price{};
};

class ConferenceTicket : public Item
{
  public:
    ConferenceTicket( std::string name, double price )
      : m_name{ std::move( name ) }
      , m_price{ price }
    {
    }
    std::string const& name() const
    {
      return m_name;
    }
    double price() const override
    {
      return m_price;
    }

  private:
    std::string m_name{};
    double m_price{};
};

class Discounted : public DecoratedItem
{
  public:
    Discounted( double discount, std::unique_ptr< Item > item )
      : DecoratedItem( std::move( item ) )
      , m_factor( 1.0 - discount )
    {
      if( !std::isfinite( discount ) || discount < 0.0 || discount > 1.0 )
      {
        throw std::invalid_argument( "Invalid discount" );
      }
    }
    double price() const override
    {
      return item().price() * m_factor;
    }

  private:
    double m_factor;
};

class Taxed : public DecoratedItem
{
  public:
    Taxed( double taxRate, std::unique_ptr< Item > item )
      : DecoratedItem( std::move( item ) )
      , m_factor( 1.0 + taxRate )
    {
      if( !std::isfinite( taxRate ) || taxRate < 0.0 )
      {
        throw std::invalid_argument( "Invalid tax" );
      }
    }

    double price() const override
    {
      return item().price() * m_factor;
    }

  private:
    double m_factor;
};

class Conference
{
  public:
    Conference( std::string name, double price )
      : m_name{ std::move( name ) }
      , m_price{ price }
    {
    }

    std::string const& name() const
    {
      return m_name;
    }

    double price() const
    {
      return m_price;
    }

  private:
    std::string m_name;
    double m_price;
};

#if 0
template< typename T >
concept PricedItem = requires( T item ) {
  {
    item.price()
  } -> std::same_as< double >;
};

template< double discount, PricedItem Item >
class DiscountedTemplate
{
  public:
    template< typename... Args >
    explicit DiscountedTemplate( Args&&... args )
      : item_{ std::forward< Args >( args )... }
    {
    }

    double price() const
    {
      return item_.price() * ( 1.0 - discount );
    }

  private:
    Item item_;
};

template< double taxRate, PricedItem Item >
class TaxedTemplate : private Item
{
  public:
    template< typename... Args >
    explicit TaxedTemplate( Args&&... args )
      : Item{ std::forward< Args >( args )... }
    {
    }

    double price() const
    {
      return Item::price() * ( 1.0 + taxRate );
    }
};
#endif

inline void printPrice( const Item* item )
{
  std::cout << "Price of item " << item->price() << "\n";
}

inline void doDecoratorWork()
{
  std::unique_ptr< Item > item1(
    std::make_unique< Taxed >( 0.07, std::make_unique< CppBook >( "Effective C++", 19.0 ) ) );
  std::unique_ptr< Item > item2( std::make_unique< Taxed >(
    0.19, std::make_unique< Discounted >( 0.2, std::make_unique< CppBook >( "CppCon", 999.0 ) ) ) );
  std::unique_ptr< Item > item3( std::make_unique< Discounted >(
    0.2, std::make_unique< Taxed >( 0.19, std::make_unique< CppBook >( "CppCon", 999.0 ) ) ) );

  printPrice( item1.get() );
  printPrice( item2.get() );
  printPrice( item3.get() );

#if 0
  TaxedTemplate< 0.15, DiscountedTemplate< 0.19, Conference > > itemT{ "Core C++", 499.0 };
  std::cout << "Templated Price is " << itemT.price() << '\n';
#endif
}
