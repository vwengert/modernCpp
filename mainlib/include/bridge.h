#pragma once

#include <memory>

class Engine
{
  public:
    virtual ~Engine() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

class Car
{
  protected:
    explicit Car( std::unique_ptr< Engine > engine )
      : engine_( std::move( engine ) )
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

  private:
    std::unique_ptr< Engine > engine_;
};

class ElectricCar : public Car
{
  public:
    ElectricCar();
    void drive() override;
};
