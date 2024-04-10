#include <gmock/gmock.h>

#include "singleton.h"

TEST( ModernTests, singletonReturnsConfiguration )
{
  ASSERT_TRUE( Singleton::instance()->configuration() == "Configuration" );
}

TEST( ModernTests, palindromIsFalseWhenNoPalindrom )
{
  ASSERT_FALSE( false );
  ASSERT_FALSE( false );
}

struct object_counter
{
    static inline int count;
    static inline int all_count;
    object_counter()
    {
      ++count;
      ++all_count;
    }
    ~object_counter()
    {
      --count;
    }
};

TEST( ScopedPtrTest, Construct )
{
  object_counter::all_count = 0;
  object_counter::count = 0;
  auto p = new object_counter;
  EXPECT_EQ( 1, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
  delete p;
  EXPECT_EQ( 0, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
}