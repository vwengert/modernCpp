#include "factory.h"

#include <memory>
#include <vector>
#include <iostream>

enum class ShapeType {
    TRIANGLE,
    SQUARE,
    CIRCLE
};


ShapeFactory::CallBackMap ShapeFactory::s_objects;

ShapeFactory::ShapeFactory() = default;

void ShapeFactory::RegisterObject(const ShapeType& type,
                                  CreateObjectCallback&& cb) {
  s_objects[type] = std::move<>(cb);
}

void ShapeFactory::UnregisterObject( const ShapeType& type )
{
    s_objects.erase( type );
}

std::unique_ptr<Shape> ShapeFactory::CreateSingleObject(const ShapeType& type) {
    if (auto it = s_objects.find(type); it != s_objects.end()) {
      return (it->second)();
    }

    return nullptr;
}

void factoryDoWork()
{
    registerObject<Triangle>( ShapeType::TRIANGLE );
    registerObject<Square>( ShapeType::SQUARE );
    registerObject<Circle>( ShapeType::CIRCLE );

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back( std::unique_ptr<Shape>( ShapeFactory::CreateSingleObject( ShapeType::TRIANGLE ) ) );
    shapes.push_back( std::unique_ptr<Shape>( ShapeFactory::CreateSingleObject( ShapeType::SQUARE ) ) );
    shapes.push_back( std::unique_ptr<Shape>( ShapeFactory::CreateSingleObject( ShapeType::CIRCLE ) ) );

    for( const auto& shape : shapes ) {
        std::cout << "Shape: " << shape->getName() << '\n';
    }
}
