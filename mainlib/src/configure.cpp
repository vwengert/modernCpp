#include "configure.h"
#include <iostream>

std::unique_ptr< AppConfigurator > configure()
{
  auto config = std::make_unique< AppConfigurator >();
  config->registerAnimal( Animal::HUMAN, &Human::create );
  config->registerAnimal( Animal::MONKEY, &Monkey::create );

  config->registerFood( Food::PIZZA, &Pizza::create );
  config->registerFood( Food::BANANA, &Banana::create );

  config->registerConcreteAnimals( Animal::HUMAN, Food::BANANA );
  config->registerConcreteAnimals( Animal::HUMAN, Food::PIZZA );
  config->registerConcreteAnimals( Animal::MONKEY, Food::PIZZA );
  config->registerConcreteAnimals( Animal::HUMAN, Food::BANANA );
  config->registerConcreteAnimals( Animal::MONKEY, Food::BANANA );
  return config;
}

std::vector< std::unique_ptr< IAnimal > > createData( const std::unique_ptr< AppConfigurator >& config )
{
  std::vector< std::unique_ptr< IAnimal > > animals;
  for( const auto& concreteAnimal : config->animals() )
  {
    animals.push_back( config->animal( concreteAnimal.first )( config->food( concreteAnimal.second )() ) );
  }

  return animals;
}

[[maybe_unused]] void displayData( const std::vector< std::unique_ptr< IAnimal > >& animals )
{
  for( const auto& animal : animals )
  {
    animal->eatFavouriteFood( std::cout );
  }
}
