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
      : item_{ std::move( item ) }
    {
      if( !item_ )
      {
        throw std::invalid_argument( "Invalid item" );
      }
    }

  protected:
    Item& item()
    {
      return *item_;
    }
    Item const& item() const
    {
      return *item_;
    }

  private:
    std::unique_ptr< Item > item_;
};

class CppBook : public Item
{
  public:
    CppBook( std::string title, double price )
      : title_{ std::move( title ) }
      , price_{ price }
    {
    }
    std::string const& title() const
    {
      return title_;
    }
    double price() const override
    {
      return price_;
    }

  private:
    std::string title_{};
    double price_{};
};

class ConferenceTicket : public Item
{
  public:
    ConferenceTicket( std::string name, double price )
      : name_{ std::move( name ) }
      , price_{ price }
    {
    }
    std::string const& name() const
    {
      return name_;
    }
    double price() const override
    {
      return price_;
    }

  private:
    std::string name_{};
    double price_{};
};

class Discounted : public DecoratedItem
{
  public:
    Discounted( double discount, std::unique_ptr< Item > item )
      : DecoratedItem( std::move( item ) )
      , factor_( 1.0 - discount )
    {
      if( !std::isfinite( discount ) || discount < 0.0 || discount > 1.0 )
      {
        throw std::invalid_argument( "Invalid discount" );
      }
    }
    double price() const override
    {
      return item().price() * factor_;
    }

  private:
    double factor_;
};

class Taxed : public DecoratedItem
{
  public:
    Taxed( double taxRate, std::unique_ptr< Item > item )
      : DecoratedItem( std::move( item ) )
      , factor_( 1.0 + taxRate )
    {
      if( !std::isfinite( taxRate ) || taxRate < 0.0 )
      {
        throw std::invalid_argument( "Invalid tax" );
      }
    }

    double price() const override
    {
      return item().price() * factor_;
    }

  private:
    double factor_;
};

class Conference
{
  public:
    Conference( std::string name, double price )
      : name_{ std::move( name ) }
      , price_{ price }
    {
    }

    std::string const& name() const
    {
      return name_;
    }

    double price() const
    {
      return price_;
    }

  private:
    std::string name_;
    double price_;
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
