#include "factory.h"

#include <iostream>
#include <memory>
#include <vector>

enum class ShapeType
{
  TRIANGLE,
  SQUARE,
  CIRCLE
};

ShapeFactory::CallBackMap ShapeFactory::m_objects;

void ShapeFactory::registerObject( const ShapeType& type, CreateObjectCallback&& callback )
{
  m_objects[ type ] = std::move<>( callback );
}

void ShapeFactory::unregisterObject( const ShapeType& type )
{
  m_objects.erase( type );
}

std::unique_ptr< Shape > ShapeFactory::createSingleObject( const ShapeType& type )
{
  if( auto it = m_objects.find( type ); it != m_objects.end() )
  {
    return ( it->second )();
  }

  return nullptr;
}

void factoryDoWork()
{
  registerObject< Triangle >( ShapeType::TRIANGLE );
  registerObject< Square >( ShapeType::SQUARE );
  registerObject< Circle >( ShapeType::CIRCLE );

  std::vector< std::unique_ptr< Shape > > shapes;
  shapes.push_back( std::unique_ptr< Shape >( ShapeFactory::createSingleObject( ShapeType::TRIANGLE ) ) );
  shapes.push_back( std::unique_ptr< Shape >( ShapeFactory::createSingleObject( ShapeType::SQUARE ) ) );
  shapes.push_back( std::unique_ptr< Shape >( ShapeFactory::createSingleObject( ShapeType::CIRCLE ) ) );

  for( const auto& shape : shapes )
  {
    std::cout << "Shape: " << shape->getName() << '\n';
  }
}
