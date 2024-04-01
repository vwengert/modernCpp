#include <decorator.h>
#include <modernLibrary.h>

#include "configure.h"

auto main() -> int
{
  const auto config = configure();
  const auto animals = createData( config );

  displayData( animals );
  doWork();

  return 0;
}
