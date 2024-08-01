#include "appconfigurator.h"

AppConfigurator::AppConfigurator()
{
}

void AppConfigurator::registerAnimal( Animal animal, aCreate creater )
{
  m_animalRegister.insert( { animal, creater } );
}

void AppConfigurator::registerFood( Food food, fCreate creater )
{
  m_foodRegister.insert( { food, creater } );
}

void AppConfigurator::registerConcreteAnimals( Animal animal, Food food )
{
  m_concreteAnimals.push_back( { animal, food } );
}

Animals AppConfigurator::animals() const
{
  return m_concreteAnimals;
}

fCreate AppConfigurator::food( Food food ) const
{
  return m_foodRegister.at( food );
}

aCreate AppConfigurator::animal( Animal animal ) const
{
  return m_animalRegister.at( animal );
}
