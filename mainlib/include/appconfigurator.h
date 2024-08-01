#ifndef APPCONFIGURATOR_H
#define APPCONFIGURATOR_H

#include <map>
#include <vector>

#include "ianimal.h"

using Animals = std::vector< std::pair< Animal, Food > >;

class AppConfigurator
{
  public:
    AppConfigurator();
    void registerAnimal( Animal animal, aCreate creater );
    void registerFood( Food food, fCreate creater );
    void registerConcreteAnimals( Animal animal, Food food );
    [[nodiscard]] Animals animals() const;
    [[nodiscard]] fCreate food( Food food ) const;
    [[nodiscard]] aCreate animal( Animal animal ) const;

  private:
    std::map< Animal, aCreate > m_animalRegister;
    std::map< Food, fCreate > m_foodRegister;
    Animals m_concreteAnimals;
};

#endif // APPCONFIGURATOR_H
