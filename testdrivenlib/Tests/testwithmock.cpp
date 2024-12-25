#include <gmock/gmock.h>

class Http
{
  public:
    virtual ~Http() = default;

    virtual void initialize() = 0;

    virtual std::string get( const std::string& url ) const = 0;
};

class HttpStub : public Http
{
  public:
    MOCK_METHOD0( initialize, void() );
    MOCK_CONST_METHOD1( get, std::string( const std::string& url ) );
};

class Service
{
  public:
    Service( Http& http )
      : m_http( http )
    {
    }

    std::string accessWithKey( const std::string& key ) const
    {
      m_http.initialize();
      const std::string url = "https://api.ipstack.com/check?access_key=" + key;
      return m_http.get( url );
    }

  private:
    Http& m_http;
};

using namespace testing;

class TestService : public Test
{
  public:
    HttpStub httpStub;
    Service service{ httpStub };
};

TEST_F( TestService, MakesHttpRequestToObtainAddress )
{
  EXPECT_CALL( httpStub, initialize() );
  const std::string urlStart = "https://api.ipstack.com/";
  const auto expectedUrl = urlStart + "check?access_key=123456789";
  EXPECT_CALL( httpStub, get( expectedUrl ) );

  auto result = service.accessWithKey( "123456789" );

  Mock::VerifyAndClearExpectations( &httpStub );
}

TEST_F( TestService, RetrieveValidResponseForCorrectKey )
{
  EXPECT_CALL( httpStub, initialize() );
  EXPECT_CALL( httpStub, get(_) ).WillOnce( Return( "access granted" ) );

  const auto result = service.accessWithKey( "123456789" );

  ASSERT_THAT( result, Eq( "access granted" ) );
}
