#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>

enum class ShapeType;

class Shape
{
  public:
    Shape() = default;

    Shape( const Shape& ) = default;
    Shape& operator=( const Shape& ) = default;

    Shape( Shape&& ) = delete;
    Shape& operator=( Shape&& ) = delete;

    virtual ~Shape() = default;

    virtual std::string getName() = 0;
};

class Triangle : public Shape
{
  public:
    std::string getName() override
    {
      return "Triangle";
    }
    static std::unique_ptr< Shape > create()
    {
      return std::make_unique< Triangle >();
    }
};

class Square : public Shape
{
  public:
    std::string getName() override
    {
      return "Square";
    }
    static std::unique_ptr< Shape > create()
    {
      return std::make_unique< Square >();
    }
};

class Circle : public Shape
{
  public:
    std::string getName() override
    {
      return "Circle";
    }
    static std::unique_ptr< Shape > create()
    {
      return std::make_unique< Circle >();
    }
};

// responsible for creating and returning shape objects on demand...
class ShapeFactory
{
    using CreateObjectCallback = std::function< std::unique_ptr< Shape >() >;

  public:
    static void registerObject( const ShapeType& type, CreateObjectCallback&& callback );
    static void unregisterObject( const ShapeType& type );
    static std::unique_ptr< Shape > createSingleObject( const ShapeType& type );

  private:
    using CallBackMap = std::map< ShapeType, CreateObjectCallback >;
    static CallBackMap m_objects;
};

template< typename T >
static inline void registerObject( const ShapeType& objectType )
{
  ShapeFactory::registerObject( objectType, T::create );
}

void factoryDoWork();
