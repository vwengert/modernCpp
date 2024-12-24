#include "gmock/gmock.h"

class Tweet
{
};

class RetweetCollection
{
  public:
    void add( const Tweet& tweet )
    {
      mSize++;
    }

    void remove( const Tweet& tweet )
    {
      if(mSize == 0)
      {
        return;
      }
      mSize--;
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

MATCHER_P( HasSize, expected, "" )
{
  return arg.size() == expected && arg.isEmpty() == ( 0 == expected );
}

TEST( ARetweetCollection, HasSizeZeroAndIsEmptyWhenCreated )
{
  const RetweetCollection retweets;
  ASSERT_THAT( retweets, HasSize(0U) );
}

class ARetweetCollectionWithOneTweet : public Test
{
  public:
    RetweetCollection collection;

    void SetUp() override
    {
      Tweet tweet;
      collection.add( tweet );
    }
};

TEST_F( ARetweetCollectionWithOneTweet, SizeIsOneAfterTweetAddedAndIsNoLongerEmpty )
{
  ASSERT_THAT( collection, HasSize(1U) );
}

TEST_F( ARetweetCollectionWithOneTweet, DecreaseSizeAfterRemovingTweet )
{
  collection.remove( Tweet() );
  ASSERT_THAT( collection, HasSize(0U) );
}
