#include "modernLibrary.h"

#include <iostream>

#include "abstractfabric.h"
#include "bridge.h"
#include "decorator.h"
#include "factory.h"
#include "mathematics.h"
#include "passkey.h"
#include "templates.h"
#include "visitor.h"

void doLambdaOverload()
{
  int i = 5;
  double d = 7.3;
  auto l = overload(
    []( int* i ) { std::cout << "i= " << *i << '\n'; }, []( double* d ) { std::cout << "d= " << *d << '\n'; } );

  l( &i );
  l( &d );
}

void doSomeTemplateWork()
{
  Ratio t{ 5, 0.1 };
  std::cout << "Ratio is: " << double( t ) << '\n';
  std::cout << "Sum of 5, 8, 9, 7: " << sum( 5, 8, 9, 7 ) << '\n';

  auto g = makeGroup( 3, 5.0, std::string( "xyz" ) );
  std::cout << "int: " << int( g ) << '\n';
  std::cout << "double: " << double( g ) << '\n';
  std::cout << "string: " << std::string( g ) << '\n';
}

void doSomeVectorWork()
{
  std::vector< std::unique_ptr< MyPair< std::string, int > > > vec;
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Januar", -5 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Februar", -1 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "March", 2 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "April", 5 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Mai", 13 ) );
  printRange( vec );
}

void doSecretFactory()
{
  SecretFactory sf;
  Secret s = sf.getSecret( "moo!" );
}

void doVisitorAndElectricCarWork()
{
  VisitorWorker worker;
  worker.showPrices();

  const auto car = std::make_unique< ElectricCar >();
  car->drive();
}

auto doWork() -> int
{
  factoryDoWork();
  abstractFactoryDoWork();
  doDecoratorWork();
  doVariantVisitorWork();
  doVisitorAndElectricCarWork();
  doSecretFactory();
  doMultiply();
  doSomeVectorWork();
  doSomeTemplateWork();
  doLambdaOverload();

  std::cout << '\n';

  return 0;
}
