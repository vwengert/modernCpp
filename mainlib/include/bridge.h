#pragma once

#include "modernLibraryExport.h"
#include <memory>

class Engine
{
  public:
    Engine() = delete;
    explicit Engine( std::ostream& stream )
      : m_stream( stream )
    {
    }
    virtual ~Engine() = default;
    Engine( const Engine& ) = default;
    Engine& operator=( const Engine& ) = delete;
    Engine( Engine&& ) = default;
    Engine& operator=( Engine&& ) = delete;
    virtual void start() = 0;
    virtual void stop() = 0;
    std::ostream& getStream() const
    {
      return m_stream;
    }

  private:
    std::ostream& m_stream; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class Car
{
  protected:
    explicit Car( std::unique_ptr< Engine > engine, std::ostream& stream )
      : m_engine( std::move( engine ) )
      , m_stream( stream )
    {
    }

  public:
    Car() = delete;
    virtual ~Car() = default;
    Car( const Car& ) = delete;
    Car& operator=( const Car& ) = delete;
    Car( Car&& ) = default;
    Car& operator=( Car&& ) = delete;
    virtual void drive() = 0;

  protected:
    Engine* getEngine()
    {
      return m_engine.get();
    }
    Engine const* getEngine() const
    {
      return m_engine.get();
    }
    std::ostream& getStream();

  private:
    std::unique_ptr< Engine > m_engine;
    std::ostream& m_stream; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

class MODERN_LIBRARY_API ElectricCar : public Car
{
  public:
    explicit ElectricCar( std::ostream& stream );
    void drive() override;
};
