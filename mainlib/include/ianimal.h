#ifndef IANIMAL_H
#define IANIMAL_H

#include <memory>

#include "ifood.h"

enum class Animal {
    HUMAN,
    MONKEY,
};


class IAnimal {
public:
    virtual void eatFavouriteFood(std::ostream &stream) = 0;
    static std::unique_ptr<IAnimal> create(std::unique_ptr<IFood> food);
};


class Monkey : public IAnimal {
private:
    std::unique_ptr<IFood> _food;

public:
    Monkey(std::unique_ptr<IFood> food);
    static std::unique_ptr<IAnimal> create(std::unique_ptr<IFood> food);
    void eatFavouriteFood(std::ostream &stream) override;
};

class Human : public IAnimal {
private:
    std::unique_ptr<IFood> _food;

public:
    Human(std::unique_ptr<IFood> food);
    static std::unique_ptr<IAnimal> create(std::unique_ptr<IFood> food);
    void eatFavouriteFood(std::ostream &stream) override;
};

using aCreate = std::unique_ptr<IAnimal> (*)(std::unique_ptr<IFood>);

void registerAnimal(Animal animal, aCreate f);

#endif// IANIMAL_H
