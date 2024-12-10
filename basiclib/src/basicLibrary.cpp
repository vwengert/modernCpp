#include "basicLibrary.h"
#include "functiontemplates.h"

#include <iostream>

auto doBasicWork() -> int
{
  constexpr auto kFIRST = 3;
  constexpr auto kSECOND = 7;
  const std::string firstWord = "Hello";
  const std::string secondWord = "World";

  std::cout << "Basic Library\n";
  std::cout << "Max from " << kFIRST << " and " << kSECOND << " is " << max( kFIRST, kSECOND ) << '\n';
  std::cout << "Max from " << firstWord << " and " << secondWord << " is " << ::max( firstWord, secondWord ) << '\n';
  return 0;
}