#ifndef IANIMAL_H
#define IANIMAL_H

#include <memory>

#include "ifood.h"

enum class Animal
{
  HUMAN,
  MONKEY,
};

class IAnimal
{
  public:
    virtual ~IAnimal() = default;
    IAnimal() = default;
    IAnimal( const IAnimal& ) = default;
    IAnimal( IAnimal&& ) = default;
    IAnimal& operator=( const IAnimal& ) = default;
    IAnimal& operator=( IAnimal&& ) = default;
    virtual void eatFavouriteFood( std::ostream& stream ) = 0;
    static std::unique_ptr< IAnimal > create( std::unique_ptr< IFood > food );
};

class Monkey : public IAnimal
{
  private:
    std::unique_ptr< IFood > m_food;

  public:
    explicit Monkey( std::unique_ptr< IFood > food );
    static std::unique_ptr< IAnimal > create( std::unique_ptr< IFood > food );
    void eatFavouriteFood( std::ostream& stream ) override;
};

class Human : public IAnimal
{
  private:
    std::unique_ptr< IFood > m_food;

  public:
    explicit Human( std::unique_ptr< IFood > food );
    static std::unique_ptr< IAnimal > create( std::unique_ptr< IFood > food );
    void eatFavouriteFood( std::ostream& stream ) override;
};

using aCreate = std::unique_ptr< IAnimal > ( * )( std::unique_ptr< IFood > );

#endif // IANIMAL_H
