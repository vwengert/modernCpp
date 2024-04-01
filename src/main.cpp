#include <decorator.h>
#include <modernLibrary.h>

#include "configure.h"
#include "visitor.h"

auto main() -> int
{
  const auto config = configure();
  const auto animals = createData( config );

  displayData( animals );
  doWork();
  doDecoratorWork();
  doVariantVisitorWork();

  return 0;
}
