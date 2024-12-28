#include "gmock/gmock.h"

using namespace testing;

class GeoServer
{
  std::vector< std::string > m_users;
  std::unordered_map< std::string, std::pair< double, double > > m_locations;

  public:
    bool isTracking( const std::string& user ) const
    {
      const auto it = std::ranges::find( m_users, user );
      return it != m_users.end();
    }

    void track( const std::string& user )
    {
      m_users.push_back( user );
    }

    size_t numberOfUsers() const
    {
      return m_users.size();
    }

    void stopTracking( const std::string& user )
    {
      if(const auto it = std::ranges::find( m_users, user ); it != m_users.end())
      {
        m_locations.erase( user );
        m_users.erase( it );
      }
    }

    void updateLocation( const std::string& user, double latitude, double longitude )
    {
      m_locations[ user ] = std::make_pair( latitude, longitude );
    }

    std::pair< double, double > locationOf( const std::string& user ) const
    {
      return m_locations.at( user );
    }
};

constexpr double kLocation_Tolerance{ 0.005 };

class TestGeoServer : public Test
{
  public:
    GeoServer server;
    const std::string aUser{ "auser" };
    const std::string anotherUser{ "anotheruser" };
    const double latitude{ 48.8566 };
    const double longitude{ 2.3522 };

    void SetUp() override
    {
      server.track( aUser );
      server.updateLocation( aUser, latitude, longitude );
    }
};

TEST_F( TestGeoServer, TracksAUser )
{
  ASSERT_THAT( server.numberOfUsers(), Eq(1) );
}

TEST_F( TestGeoServer, TracksTwoUsers )
{
  server.track( anotherUser );

  ASSERT_THAT( server.numberOfUsers(), Eq(2) );
}

TEST_F( TestGeoServer, IsTrackingIsFalseWhenUserIsNotAdded )
{
  ASSERT_FALSE( server.isTracking(anotherUser) );
}

TEST_F( TestGeoServer, IsTrackingIsTrueWhenUserIsBeingTracked )
{
  ASSERT_TRUE( server.isTracking(aUser) );
}

TEST_F( TestGeoServer, IsTrackingIsFalseWhenUserIsRemovedFromBeingTracked )
{
  server.stopTracking( aUser );

  ASSERT_FALSE( server.isTracking(aUser) );
}

TEST_F( TestGeoServer, RemoveUserOnNotTrackedUserDoesNotChangeUserCount )
{
  EXPECT_FALSE( server.isTracking( anotherUser ) );
  server.stopTracking( anotherUser );

  ASSERT_THAT( server.numberOfUsers(), Eq(1) );
}

TEST_F( TestGeoServer, UpdatesLocationOfUser )
{
  const auto [ locLat, locLong ] = server.locationOf( aUser );

  ASSERT_THAT( locLat, DoubleNear( latitude, kLocation_Tolerance ) );
  ASSERT_THAT( locLong, DoubleNear( longitude, kLocation_Tolerance ) );
}

TEST_F( TestGeoServer, ThrowsWhenLocationOfUserIsRequestedAndUserIsNotTracked )
{
  ASSERT_THROW( server.locationOf( anotherUser ), std::out_of_range );
}

TEST_F( TestGeoServer, ThrowsWhenNoTrackingDataIsFoundForUser )
{
  server.track( anotherUser );

  ASSERT_THROW( server.locationOf( anotherUser ), std::out_of_range );
}

TEST_F( TestGeoServer, ThrowsWhenTrackingFromUserIsStopped )
{
  server.stopTracking( aUser );

  ASSERT_THROW( server.locationOf( aUser ), std::out_of_range );
}