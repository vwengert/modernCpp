#include "basicLibrary.h"
#include "functiontemplates.h"

#include <iostream>

auto doBasicWork() -> int
{
  constexpr auto kFIRST = 5;
  constexpr auto kSECOND = 7;
  constexpr auto kTHIRD = 5.1;
  const std::string firstWord = "Hello";
  const std::string secondWord = "World";

  std::cout << "Basic Library\n";
  std::cout << "Max from " << kFIRST << " and " << kSECOND << " is " << ::max( kFIRST, kSECOND ) << '\n';
  std::cout << "Max from " << firstWord << " and " << secondWord << " is " << ::max( firstWord, secondWord ) << '\n';
  std::cout << "Max from " << kFIRST << " and " << kTHIRD << " is " << ::max( kFIRST, kTHIRD ) << '\n';
  return 0;
}