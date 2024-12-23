#include <gmock/gmock.h>

#include "mutex.h"
#include "raiitemplates.h"
#include "singleton.h"

using namespace testing;

TEST( ModernTests, singletonReturnsConfiguration )
{
  ASSERT_THAT( Singleton::instance()->configuration(), Eq("Configuration") );
}

TEST( ScopedPtrTest, DeleteObjectReducesCountToZero )
{
  object_counter::all_count = object_counter::count = 0;
  const auto* pObjCounter = new object_counter;
  EXPECT_THAT( object_counter::all_count, Eq(1) );
  EXPECT_THAT( object_counter::count, Eq(1) );
  delete pObjCounter;
  EXPECT_THAT( object_counter::all_count, Eq(1) );

  ASSERT_THAT( object_counter::count, Eq(0) );
}

TEST( ScopedPtrTest, ObjectCountReducesToZeroLeavingBlockContext )
{
  object_counter::all_count = object_counter::count = 0; {
    scoped_ptr< object_counter > pObjCounter( new object_counter );
    EXPECT_THAT( object_counter::all_count, Eq(1) );
    EXPECT_THAT( object_counter::count, Eq(1) );
  }
  EXPECT_THAT( object_counter::all_count, Eq(1) );

  ASSERT_THAT( object_counter::count, Eq(0) );
}

TEST( ScopedPtrTest, EarlyReturnNoLeak )
{
  object_counter::all_count = object_counter::count = 0;
  while(true)
  {
    scoped_ptr< object_counter > pObjCounter( new object_counter );
    break;
  }
  EXPECT_THAT( object_counter::all_count, Eq(1) );

  ASSERT_THAT( object_counter::count, Eq(0) );
}

TEST( ScopedPtrTest, ThrowNoLeak )
{
  object_counter::all_count = object_counter::count = 0;
  try
  {
    scoped_ptr< object_counter > pObjCounter( new object_counter );
    throw 1;
  }
  catch(...)
  {
  };
  EXPECT_THAT( object_counter::all_count, Eq(1) );

  ASSERT_THAT( object_counter::count, Eq(0) );
}

TEST( RAII, AcquireRelease )
{
  object_counter::all_count = object_counter::count = 0; {
    raii< object_counter > pObjCounter( new object_counter );
    EXPECT_THAT( object_counter::all_count, Eq(1) );
    EXPECT_THAT( object_counter::count, Eq(1) );
  }
  EXPECT_THAT( object_counter::all_count, Eq(1) );

  ASSERT_THAT( object_counter::count, Eq(0) );
}

TEST( RAII, ThrowNoLeakMutexCanBeLocked )
{
  std::mutex mutex;
  try
  {
    MutexGuard mutexGuard( mutex );
    EXPECT_THAT( mutex.try_lock(), Eq(false) );
    throw 1;
  }
  catch(...)
  {
  }
  ASSERT_THAT( mutex.try_lock(), Eq(true) );
  mutex.unlock();
}
