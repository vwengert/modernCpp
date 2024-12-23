#include "gmock/gmock.h"

class Tweet
{
};

class RetweetCollection
{
  public:
    void add( const Tweet& tweet )
    {
      mSize = 1;
    }

    void remove( const Tweet& tweet )
    {
      mSize = 0;
    }

    bool isEmpty() const
    {
      return 0 == size();
    }

    size_t size() const
    {
      return mSize;
    }

  private:
    size_t mSize{ 0 };
};

using namespace testing;

class ARetweetCollection : public Test
{
  public:
    RetweetCollection retweets;
};

MATCHER_P( HasSize, expected, "" )
{
  return arg.size() == expected && arg.isEmpty() == ( 0 == expected );
}

TEST_F( ARetweetCollection, HasSizeZeroAndIsEmptyWhenCreated )
{
  ASSERT_THAT( retweets, HasSize(0U) );
}

TEST_F( ARetweetCollection, SizeIsOneAfterTweetAddedAndIsNoLongerEmpty )
{
  retweets.add( Tweet() );
  ASSERT_THAT( retweets, HasSize(1U) );
}

TEST_F( ARetweetCollection, DecreaseSizeAfterRemovingTweet )
{
  retweets.add( Tweet() );
  retweets.remove( Tweet() );
  ASSERT_THAT( retweets, HasSize(0U) );
}