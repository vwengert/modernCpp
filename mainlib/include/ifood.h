#ifndef IFOOD_H
#define IFOOD_H

#include <memory>
#include <string>

enum class Food
{
  PIZZA,
  BANANA,
};

class IFood
{
  public:
    virtual std::string name() = 0;
    virtual ~IFood() = default;
    IFood() = default;
    IFood( const IFood& ) = default;
    IFood( IFood&& ) = default;
    IFood& operator=( const IFood& ) = default;
    IFood& operator=( IFood&& ) = default;
    static std::unique_ptr< IFood > create();
};

class Banana : public IFood
{
  public:
    std::string name() override;
    static std::unique_ptr< IFood > create();
};

class Pizza : public IFood
{
  public:
    std::string name() override;
    static std::unique_ptr< IFood > create();
};

using fCreate = std::unique_ptr< IFood > ( * )();

#endif // IFOOD_H
