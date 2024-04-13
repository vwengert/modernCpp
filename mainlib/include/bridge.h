#pragma once

#include <memory>

class Engine
{
  public:
    Engine( std::ostream& stream )
      : stream_( stream )
    {
    }
    virtual ~Engine() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    std::ostream& getStream()
    {
      return stream_;
    }

  private:
    std::ostream& stream_;
};

class Car
{
  protected:
    explicit Car( std::unique_ptr< Engine > engine, std::ostream& stream )
      : engine_( std::move( engine ) )
      , stream_( stream )
    {
    }

  public:
    virtual ~Car() = default;
    virtual void drive() = 0;

  protected:
    Engine* getEngine()
    {
      return engine_.get();
    }
    Engine const* getEngine() const
    {
      return engine_.get();
    }
    std::ostream& getStream();

  private:
    std::unique_ptr< Engine > engine_;
    std::ostream& stream_;
};

class ElectricCar : public Car
{
  public:
    ElectricCar( std::ostream& stream );
    void drive() override;
};
