#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <functional>

enum class ShapeType;

class Shape
{
    public:
        virtual std::string getName() = 0;
        virtual ~Shape() = default;
};

class Triangle : public Shape
{
    public:
        std::string getName() override
        {
            return "Triangle";
        }
        ~Triangle() override = default;
        static std::unique_ptr<Shape> Create() {
          return std::make_unique<Triangle>();
        }
};

class Square : public Shape {
       public:
        std::string getName() override { return "Square"; }
        ~Square() override = default;
        static std::unique_ptr<Shape> Create() {
          return std::make_unique<Square>();
        }
};

class Circle : public Shape {
       public:
        std::string getName() override { return "Circle"; }
        ~Circle() override = default;
        static std::unique_ptr<Shape> Create() {
          return std::make_unique<Circle>();
        }
};

// responsible for creating and returning shape objects on demand...
class ShapeFactory
{
        using CreateObjectCallback = std::function<std::unique_ptr<Shape>()>;

       public:
        ShapeFactory();
        static void RegisterObject(const ShapeType& type,
                                   CreateObjectCallback&& cb);
        static void UnregisterObject( const ShapeType& type );
        static std::unique_ptr<Shape> CreateSingleObject(const ShapeType& type);

       private:
        using CallBackMap = std::map<ShapeType, CreateObjectCallback>;
        static CallBackMap s_objects;
};

template<typename T>
static inline void registerObject( const ShapeType& objectType )
{
    ShapeFactory::RegisterObject( objectType, T::Create );
}

void factoryDoWork();
