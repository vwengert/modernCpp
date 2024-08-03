#include "ianimal.h"

#include <iostream>

std::unique_ptr< IAnimal > IAnimal::create( std::unique_ptr< IFood > /*food*/ )
{
  return nullptr;
}

Monkey::Monkey( std::unique_ptr< IFood > food )
  : m_food( std::move( food ) )
{
}

std::unique_ptr< IAnimal > Monkey::create( std::unique_ptr< IFood > food )
{
  return std::make_unique< Monkey >( std::move( food ) );
}

void Monkey::eatFavouriteFood( std::ostream& stream )
{
  stream << "Monkey eats " << m_food->name() << "\n";
}

Human::Human( std::unique_ptr< IFood > food )
  : m_food( std::move( food ) )
{
}

std::unique_ptr< IAnimal > Human::create( std::unique_ptr< IFood > food )
{
  return std::make_unique< Human >( std::move( food ) );
}

void Human::eatFavouriteFood( std::ostream& stream )
{
  stream << "Human eats " << m_food->name() << "\n";
}
