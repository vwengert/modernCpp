#include "gmock/gmock.h"

class RetweetCollection
{
  public:
    bool isEmpty() const
    {
      return true;
    }
};

using namespace testing;

TEST( ARetweetCollection, IsEmptyWhenCreated )
{
  RetweetCollection retweets;
  ASSERT_TRUE( retweets.isEmpty() );
}