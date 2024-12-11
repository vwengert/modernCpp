#include "basicLibrary.h"
#include "functiontemplates.h"

#include <iostream>

auto doBasicWork() -> int
{
  constexpr auto kFIRST = 5;
  constexpr auto kSECOND = 3;
  constexpr auto kTHIRD = 5.1;
  const int* kPtrFirst = &kFIRST;
  const int* kPtrSecond = &kSECOND;
  int const& kFirstRef = kFIRST;
  const std::string firstWord = "Hello";
  const std::string secondWord = "World";
  const auto* kPtrFirstWord = "hello";
  const auto* kPtrSecondWord = "world";

  std::cout << "Basic Library\n";
  std::cout << "Max from " << kFIRST << " and " << kSECOND << " is " << ::max( kFIRST, kSECOND ) << '\n';
  std::cout << "Max from " << firstWord << " and " << secondWord << " is " << ::max( firstWord, secondWord ) << '\n';
  std::cout << "Max from " << kFIRST << " and " << kTHIRD << " is " << ::max( kFIRST, kTHIRD ) << '\n';
  std::cout << "Max from " << kSECOND << " and " << kFirstRef << " is " << ::max< long double >( kFirstRef, kSECOND )
            << '\n';
  std::cout << "Max from " << *kPtrFirst << " and " << *kPtrSecond << " is " << *::max( kPtrFirst, kPtrSecond ) << '\n';
  std::cout << "Max from " << kPtrFirstWord << " and " << kPtrSecondWord << " is "
            << ::max( kPtrFirstWord, kPtrSecondWord ) << '\n';
  return 0;
}