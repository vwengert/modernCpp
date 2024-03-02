#include "modernLibrary.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "abstractfabric.h"
#include "factory.h"
#include "mathematics.h"
#include "passkey.h"
#include "singleton.h"
#include "visitor.h"

template <typename T, typename U>
class MyPair {
  T data01_;
  U data02_;

 public:
  MyPair(const T& t, const U& u) : data01_{t}, data02_{u} {}
  void print(std::ostream& os) const {
    os << data01_ << " : " << data02_ << std::endl;
  }
};

template< typename Range >
void printRange( Range const& range )
{
  using std::begin;
  using std::end;
  for( auto pos = begin( range ); pos != end( range ); ++pos )
  {
    pos->get()->print( std::cout );
  }
}

template< typename T >
struct Widget
{
    T value;
};

template< typename T >
void swap( Widget< T >& lhs, Widget< T >& rhs )
{
  using std::swap;
  swap( lhs.value, rhs.value );
}

auto doWork() -> int {
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
  std::vector<std::unique_ptr<MyPair<std::string, int>>> vec;
  vec.emplace_back(std::make_unique<MyPair<std::string, int>>("Januar", -5));
  vec.emplace_back(std::make_unique<MyPair<std::string, int>>("Februar", -1));
  vec.emplace_back(std::make_unique<MyPair<std::string, int>>("March", 2));
  vec.emplace_back(std::make_unique<MyPair<std::string, int>>("April", 5));
  vec.emplace_back(std::make_unique<MyPair<std::string, int>>("Mai", 13));

  printRange( vec );

  return 0;
}
