#include "gmock/gmock.h"

class Tweet
{
  public:
    Tweet( const std::string& msg, const std::string& user )
    {
      mMsg = msg;
      mUser = user;
    }

    bool operator==( const Tweet& ) const { return true; }

  private:
    std::string mMsg;
    std::string mUser;
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
    std::shared_ptr< Tweet > tweet{ nullptr };

    void SetUp() override
    {
      tweet = std::make_shared< Tweet >( "msg", "user" );
      collection.add( *tweet );
    }
};

TEST_F( ARetweetCollectionWithOneTweet, SizeIsOneAfterTweetAddedAndIsNoLongerEmpty )
{
  ASSERT_THAT( collection, HasSize(1U) );
}

TEST_F( ARetweetCollectionWithOneTweet, DecreaseSizeAfterRemovingTweet )
{
  collection.remove( Tweet( "msg", "user" ) );
  ASSERT_THAT( collection, HasSize(0U) );
}
