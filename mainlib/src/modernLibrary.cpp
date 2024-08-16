#include "modernLibrary.h"

#include <any>
#include <future>
#include <iostream>
#include <random>
#include <set>

#include "abstractfabric.h"
#include "bridge.h"
#include "configure.h"
#include "decorator.h"
#include "factory.h"
#include "mathematics.h"
#include "passkey.h"
#include "templates.h"
#include "visitor.h"

auto doWork() -> int
{
  factoryDoWork();
  abstractFactoryDoWork();
  doDecoratorWork();
  doVariantVisitorWork();
  doVisitorAndElectricCarWork();
  doSecretFactory();
  doMultiply();
  doConfigrationStuff();
  doSomeVectorWork();
  doSomeTemplateWork();
  doLambdaOverload();
  doSomeStandardLibraryWork();

  std::cout << '\n';

  return 0;
}

constexpr int kTHREE = 3;
constexpr int kFIVE = 5;
constexpr int kSEVEN = 7;
constexpr int kEIGHT = 8;
constexpr int kNINE = 9;
constexpr int kRANDMS = 300; // 0000;
constexpr double kSEVEN_POINT_THREE = 7.3;
constexpr double kFIVE_POINT_ZERO = 5.0;
constexpr double kZERO_POINT_ONE = 0.1;

void doLambdaOverload()
{
  int integer = kFIVE;
  double dobble = kSEVEN_POINT_THREE;
  auto lmbda = overload( []( const int* integer ) { std::cout << "i= " << *integer << '\n'; },
    []( const double* dble ) { std::cout << "d= " << *dble << '\n'; } );

  lmbda( &integer );
  lmbda( &dobble );
}

void doSomeTemplateWork()
{
  const Ratio temp{ kFIVE, kZERO_POINT_ONE };
  std::cout << "Ratio is: " << static_cast< double >( temp ) << '\n';
  std::cout << "Sum of 5, 8, 9, 7: " << sum( kFIVE, kEIGHT, kNINE, kSEVEN ) << '\n';
#ifndef _WIN32
  const auto group = makeGroup( kTHREE, kFIVE_POINT_ZERO, std::string( "xyz" ) );
  std::cout << "int: " << static_cast< int >( group ) << '\n';
  std::cout << "double: " << static_cast< double >( group ) << '\n';
  std::cout << "string: " << std::string( group ) << '\n';
#endif
}

struct OutputTypesTemplate
{
    OutputTypesTemplate() = default;
    OutputTypesTemplate( const OutputTypesTemplate& ) = default;
    OutputTypesTemplate( OutputTypesTemplate&& ) = default;
    OutputTypesTemplate& operator=( const OutputTypesTemplate& ) = default;
    OutputTypesTemplate& operator=( OutputTypesTemplate&& ) = default;
    virtual ~OutputTypesTemplate() = default;

    virtual void handle() = 0;

  protected:
    template< typename T >
    static void print()
    {
      T tmp{};
      std::cout << tmp << "--\n";
    }
};

template< typename... T >
struct OutputTypesImpl final : OutputTypesTemplate
{
    void handle() override
    {
      const auto notUsed = std::initializer_list< int >{ ( print< T >(), 0 )... };
      std::cout << notUsed.size() << " not used\n";
    }
};

template< typename T >
class MyClass
{
  public:
    MyClass() = default;
    template< typename X >
    void assign( const MyClass< X >& xValue )
    {
      std::cout << "assigning: " << xValue.getValue() << '\n';
      m_value = xValue.getValue();
    }
    T getValue() const
    {
      return m_value;
    }
    template< typename U >
    explicit MyClass( const MyClass< U >& xValue )
    {
      std::cout << "template Constructor\n";
      assign( xValue );
    };

  private:
    T m_value{};
};

std::set< int > makeSortedRandoms( const size_t num_elems )
{
  std::set< int > retval;
  std::random_device rdm;
  std::mt19937 gen( rdm() );
  std::uniform_int_distribution<> dis( 0, static_cast< int >( num_elems ) - 1 );

  std::generate_n( std::inserter( retval, retval.end() ), num_elems, [ & ]() { return dis( gen ); } );
  return retval;
}

void f()
{
  std::vector< std::any > vAny{ kEIGHT, kSEVEN_POINT_THREE, std::string( "hello" ) };
  std::cout << "Size of any vector: " << vAny.size() << '\n';
  for( const auto& value : vAny )
  {
    std::cout << "Value type name: " << value.type().name() << '\n';
    const auto& type = value.type();
    if( type == typeid( int ) )
    {
      const auto anyValue = std::any_cast< int >( value );
      std::cout << "Integer: " << anyValue << '\n';
    }
    else if( type == typeid( double ) )
    {
      const auto anyValue = std::any_cast< double >( value );
      std::cout << "Double: " << anyValue << '\n';
    }
    else if( type == typeid( std::string ) )
    {
      const auto anyValue = std::any_cast< std::string >( value );
      std::cout << "String: " << anyValue << '\n';
    }
  }

  auto random = std::async( std::launch::deferred, makeSortedRandoms, kRANDMS );
  auto random1 = std::async( std::launch::deferred, makeSortedRandoms, kRANDMS );
  auto random2 = std::async( std::launch::deferred, makeSortedRandoms, kRANDMS );
  std::cout << random.get().size() << ", " << random1.get().size() << ", " << random2.get().size()
            << " different randoms\n";
  MyClass< double > xds;
  const MyClass< double > xd2{ xds };
  MyClass< int > xis{ xds };
  xds.assign( xis );
  xis.assign( xd2 );
  OutputTypesImpl< int, double > impl;
  impl.handle();
}

void doSomeStandardLibraryWork()
{
  f();
}

void doSomeVectorWork()
{
  std::vector< std::unique_ptr< MyPair< std::string, int > > > vec;
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Januar", -kFIVE ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Februar", -kEIGHT ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "March", kEIGHT ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "April", kFIVE ) );
  vec.emplace_back( std::make_unique< MyPair< std::string, int > >( "Mai", kNINE ) );
  printRange( vec );
}

void doSecretFactory()
{
  SecretFactory sfct;
  Secret scrt = sfct.getSecret( "moo!" );
}

void doVisitorAndElectricCarWork()
{
  VisitorWorker worker;
  worker.showPrices();

  const auto car = std::make_unique< ElectricCar >( std::cout );
  car->drive();
}

void doConfigrationStuff()
{
  const auto config = configure();
  const auto animals = createData( config );

  displayData( animals );
}
