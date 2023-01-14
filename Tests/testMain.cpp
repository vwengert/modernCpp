#include <gmock/gmock.h>
#include <modernLibrary.h>

TEST(ModernTests, palindromIsTrueWhenPalindrom) {
  ASSERT_TRUE(isPalindrome("Otto"));
  ASSERT_TRUE(isPalindrome("regallager"));
}

TEST(ModernTests, palindromIsFalseWhenNoPalindrom) {
  ASSERT_FALSE(isPalindrome("keinPalindrom"));
  ASSERT_FALSE(isPalindrome("hallo"));
}