#include <decorator.h>
#include <modernLibrary.h>

#include "bridge.h"
#include "configure.h"
#include "visitor.h"

template< typename N, typename D >
class Ratio
{
  public:
    Ratio()
      : num_{}
      , denom_{}
    {
    }
    Ratio( const N& num, const D& denom )
      : num_{ num }
      , denom_{ denom }
    {
    }
    explicit operator double() const
    {
      return double( num_ ) / double( denom_ );
    }

  private:
    N num_;
    D denom_;
};

auto main() -> int
{
  const auto config = configure();
  const auto animals = createData( config );

  displayData( animals );
  doWork();
  doDecoratorWork();
  doVariantVisitorWork();

  const auto car = std::make_unique< ElectricCar >();
  car->drive();

  Ratio r{ 5, 0.1 };

  std::cout << "Ratio is: " << double( r ) << '\n';

  return 0;
}
