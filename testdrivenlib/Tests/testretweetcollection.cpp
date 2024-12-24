#include "gmock/gmock.h"

class Tweet
{
  public:
    Tweet( const std::string& msg, const std::string& user )
      : m_msg( msg )
        , m_user( user )
    {
    }

    Tweet( const Tweet& other )
      : m_msg( other.m_msg )
        , m_user( other.m_user )
    {
    }

    bool operator==( const Tweet& tweet ) const
    {
      return m_msg == tweet.m_msg && m_user == tweet.m_user;
    }

  private:
    std::string m_msg;
    std::string m_user;
};

class RetweetCollection
{
  public:
    void add( const Tweet& tweet )
    {
      if(const auto it = std::ranges::find( m_tweets, tweet ); it == m_tweets.end())
      {
        m_tweets.emplace_back( tweet );
      }
    }

    void remove( const Tweet& tweet )
    {
      if(!isEmpty())
      {
        m_tweets.pop_back();
      }
    }

    bool isEmpty() const
    {
      return m_tweets.empty();
    }

    size_t size() const
    {
      return m_tweets.size();
    }

  private:
    std::vector< Tweet > m_tweets;
};

using namespace testing; // NOLINT(*-build-using-namespace)

MATCHER_P( HasSize, expected, "" ) // NOLINT(*-avoid-const-or-ref-data-members)
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
  ASSERT_THAT( collection, HasSize( static_cast< size_t >( 1 )) );
}

TEST_F( ARetweetCollectionWithOneTweet, DecreaseSizeAfterRemovingTweet )
{
  collection.remove( Tweet( "msg", "user" ) );

  ASSERT_THAT( collection, HasSize(static_cast<size_t>(0)) );
}

TEST_F( ARetweetCollectionWithOneTweet, IgnoresDuplicateTweetAdded )
{
  const Tweet newTweet( "msg", "@user" );
  collection.add( newTweet );
  EXPECT_THAT( collection, HasSize(static_cast<size_t>(2)) );
  const Tweet duplicate( newTweet );

  collection.add( duplicate );

  ASSERT_THAT( collection, HasSize(static_cast<size_t>(2)) );
}
