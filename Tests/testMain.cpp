#include <gmock/gmock.h>

#include "mutex.h"
#include "raiitemplates.h"
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

TEST( ScopedPtrTest, Construct )
{
  object_counter::all_count = object_counter::count = 0;
  auto p = new object_counter;
  EXPECT_EQ( 1, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
  delete p;
  EXPECT_EQ( 0, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
}

TEST( ScopedPtrTest, AcquireRelease )
{
  object_counter::all_count = object_counter::count = 0;
  {
    scoped_ptr< object_counter > p( new object_counter );
    EXPECT_EQ( 1, object_counter::count );
    EXPECT_EQ( 1, object_counter::all_count );
  }
  EXPECT_EQ( 0, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
}

TEST( ScopedPtrTest, EarlyReturnNoLeak )
{
  object_counter::all_count = object_counter::count = 0;
  do
  {
    scoped_ptr< object_counter > p( new object_counter );
    break;
  } while( false );
  EXPECT_EQ( 0, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
}

TEST( ScopedPtrTest, ThrowNoLeak )
{
  object_counter::all_count = object_counter::count = 0;
  try
  {
    scoped_ptr< object_counter > p( new object_counter );
    throw 1;
  }
  catch( ... )
  {
  };
  EXPECT_EQ( 0, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
}

TEST( RAII, AcquireRelease )
{
  object_counter::all_count = object_counter::count = 0;
  {
    raii< object_counter > p( new object_counter );
    EXPECT_EQ( 1, object_counter::count );
    EXPECT_EQ( 1, object_counter::all_count );
  }
  EXPECT_EQ( 0, object_counter::count );
  EXPECT_EQ( 1, object_counter::all_count );
}

TEST( RAII, ThrowNoLeak )
{
  std::mutex m;
  try
  {
    MutexGuard lg( m );
    EXPECT_FALSE( m.try_lock() );
    throw 1;
  }
  catch( ... )
  {
  }
  EXPECT_TRUE( m.try_lock() );
  m.unlock();
}