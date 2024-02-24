#include "modernLibrary.h"

#include <iostream>
#include <memory>

#include "abstractfabric.h"
#include "factory.h"
#include "mathematics.h"
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

class Secret
{
    class ConstructorKey
    {
        friend class SecretFactory;

      private:
        ConstructorKey(){};
        ConstructorKey( ConstructorKey const& ) = default;
    };

  public:
    explicit Secret( std::string str, ConstructorKey )
      : data( std::move( str ) )
    {
    }

  private:
    void addData( std::string const& moreData );

    std::string data;
};

class SecretFactory
{
  public:
    Secret getSecret( std::string str )
    {
      return Secret{ std::move( str ), {} };
    }
};

auto doWork() -> int {
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

  for (auto const& pair : vec) {
    pair->print(std::cout);
  }

  return 0;
}
