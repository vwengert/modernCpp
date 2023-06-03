#pragma once
#include <string>
#include <map>

enum class ShapeType;

class Shape
{
    public:
        virtual std::string getName() = 0;
        virtual ~Shape() {};
};

class Triangle : public Shape
{
    public:
        std::string getName() override
        {
            return "Triangle";
        }
        ~Triangle() override = default;
        static Shape* Create()
        {
            return new Triangle();
        }
};

class Square : public Shape
{
    public:
        std::string getName() override
        {
            return "Square";
        }
        ~Square() override = default;
        static Shape* Create()
        {
            return new Square();
        }
};

class Circle : public Shape
{
    public:
        std::string getName() override
        {
            return "Circle";
        }
        ~Circle() override = default;
        static Shape* Create()
        {
            return new Circle();
        }
};

// responsible for creating and returning shape objects on demand...
class ShapeFactory
{
        typedef Shape* ( *CreateObjectCallback )();
    public:
        ShapeFactory();
        static void RegisterObject( const ShapeType& type, CreateObjectCallback cb );
        static void UnregisterObject( const ShapeType& type );
        static Shape* CreateSingleObject( const ShapeType& type );
    private:
        typedef std::map<ShapeType, CreateObjectCallback> CallBackMap;
        static CallBackMap s_objects;
};

template<typename T>
static inline void registerObject( const ShapeType& objectType )
{
    ShapeFactory::RegisterObject( objectType, T::Create );
}

void factoryDoWork();
