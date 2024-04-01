#include "modernLibrary.h"

#include <cassert>
#include <iostream>

#include "abstractfabric.h"
#include "bridge.h"
#include "factory.h"
#include "mathematics.h"
#include "passkey.h"
#include "singleton.h"
#include "templates.h"
#include "visitor.h"

auto doWork() -> int
{
  Widget< std::string > w1{ "Hello" };
  Widget< std::string > w2{ "World" };
  swap( w1, w2 );

  assert( w1.value == "World" );
  assert( w2.value == "Hello" );

  std::cout << Singleton::instance()->configuration() << '\n';
  factoryDoWork();
  abstractFactoryDoWork();

  SecretFactory sf;
  Secret s = sf.getSecret( "moo!" );

  VisitorWorker worker;
  worker.showPrices();

  doMultiply();
  std::vector< std::unique_ptr< MyPair< std::string, int > > > vec;
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Januar", -5 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Februar", -1 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "March", 2 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "April", 5 ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Mai", 13 ) );

  printRange( vec );

  const auto car = std::make_unique< ElectricCar >();
  car->drive();

  Ratio t{ 5, 0.1 };
  std::cout << "Ratio is: " << double( t ) << '\n';
  std::cout << "Sum of 5, 8, 9, 7: " << sum( 5, 8, 9, 7 ) << '\n';

  auto g = makeGroup( 3, 5.0, std::string( "xyz" ) );
  std::cout << "int: " << int( g ) << '\n';
  std::cout << "double: " << double( g ) << '\n';
  std::cout << "string: " << std::string( g ) << '\n';

  return 0;
}
