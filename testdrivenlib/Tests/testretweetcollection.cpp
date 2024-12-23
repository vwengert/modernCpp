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

class ARetweetCollection : public Test
{
  public:
    RetweetCollection collection;

    void SetUp() override
    {
      const Tweet tweet;
      collection.add( tweet );
    }
};

MATCHER_P( HasSize, expected, "" )
{
  return arg.size() == expected && arg.isEmpty() == ( 0 == expected );
}

TEST_F( ARetweetCollection, HasSizeZeroAndIsEmptyWhenCreated )
{
  RetweetCollection retweets;
  ASSERT_THAT( retweets, HasSize(0U) );
}

TEST_F( ARetweetCollection, SizeIsOneAfterTweetAddedAndIsNoLongerEmpty )
{
  ASSERT_THAT( collection, HasSize(1U) );
}

TEST_F( ARetweetCollection, DecreaseSizeAfterRemovingTweet )
{
  collection.remove( Tweet() );
  ASSERT_THAT( collection, HasSize(0U) );
}
