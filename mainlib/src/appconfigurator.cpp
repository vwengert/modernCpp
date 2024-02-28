#include "appconfigurator.h"

AppConfigurator::AppConfigurator() {
}

void AppConfigurator::registerAnimal(Animal animal, aCreate f) {
    animalRegister.insert({animal, f});
}

void AppConfigurator::registerFood(Food food, fCreate f) {
    foodRegister.insert({food, f});
}

void AppConfigurator::registerConcreteAnimals(Animal a, Food f) {
    concreteAnimals.push_back({a, f});
}

Animals AppConfigurator::animals() const {
    return concreteAnimals;
}

fCreate AppConfigurator::food(Food f) const {
    return foodRegister.at(f);
}

aCreate AppConfigurator::animal(Animal a) const {
    return animalRegister.at(a);
}
