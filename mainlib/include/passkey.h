#pragma once
#include <string>

class Secret
{
    class ConstructorKey
    {
        friend class SecretFactory;

      private:
        ConstructorKey(){};
        ConstructorKey( ConstructorKey const& ) = default;
    };

  public:
    explicit Secret( std::string str, ConstructorKey )
      : data( std::move( str ) )
    {
    }

  private:
    void addData( std::string const& moreData );

    std::string data;
};

class SecretFactory
{
  public:
    Secret getSecret( std::string str )
    {
      return Secret{ std::move( str ), {} };
    }
};
