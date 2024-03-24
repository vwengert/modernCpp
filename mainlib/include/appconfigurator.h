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
    void registerAnimal( Animal animal, aCreate f );
    void registerFood( Food food, fCreate f );
    void registerConcreteAnimals( Animal a, Food f );
    [[nodiscard]] Animals animals() const;
    [[nodiscard]] fCreate food( Food f ) const;
    [[nodiscard]] aCreate animal( Animal a ) const;

  private:
    std::map< Animal, aCreate > animalRegister;
    std::map< Food, fCreate > foodRegister;
    Animals concreteAnimals;
};

#endif // APPCONFIGURATOR_H
