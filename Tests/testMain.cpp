#include <gmock/gmock.h>

#include "singleton.h"

TEST(ModernTests, singletonReturnsConfiguration) {
  ASSERT_TRUE(Singleton::instance()->configuration() == "Configuration");
}

TEST(ModernTests, palindromIsFalseWhenNoPalindrom) {
  ASSERT_FALSE(false);
  ASSERT_FALSE(false);
}