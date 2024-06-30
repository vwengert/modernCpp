#pragma once
#include <iostream>
#include <memory>

constexpr int kMAXVALUE = 100;

class TemperatureSensor
{
  public:
    TemperatureSensor() = default;
    TemperatureSensor( const TemperatureSensor& ) = default;
    TemperatureSensor( TemperatureSensor&& ) = default;
    TemperatureSensor& operator=( const TemperatureSensor& ) = default;
    TemperatureSensor& operator=( TemperatureSensor&& ) = default;
    virtual ~TemperatureSensor() = default;
    float actualTemperature()
    {
      setActualTemperature( readTemperature() );
      return m_actualTemperature;
    }
    virtual float readTemperature() = 0;

  protected:
    void setActualTemperature( float temperature )
    {
      m_actualTemperature = temperature;
    }

  private:
    float m_actualTemperature{};
};

class JalousieActor
{
  public:
    JalousieActor() = default;
    JalousieActor( const JalousieActor& ) = default;
    JalousieActor( JalousieActor&& ) = default;
    JalousieActor& operator=( const JalousieActor& ) = default;
    JalousieActor& operator=( JalousieActor&& ) = default;
    virtual ~JalousieActor() = default;
    float getActualPosition() const
    {
      return m_actualPosition;
    }
    void up( float value )
    {
      m_actualPosition = readActualPosition();
      m_actualPosition -= value;

      if( m_actualPosition < 0 )
      {
        m_actualPosition = 0;
      }
    }
    void down( float value )
    {
      m_actualPosition = readActualPosition();
      m_actualPosition += value;

      if( m_actualPosition > kMAXVALUE )
      {
        m_actualPosition = kMAXVALUE;
      }
    }
    virtual float readActualPosition() = 0;
    virtual float setActualPosition( float value )
    {
      m_actualPosition = value;
      return m_actualPosition;
    }

  private:
    float m_actualPosition{};
};

class HomebusTemperatureSensor : public TemperatureSensor
{
  public:
    float readTemperature() override
    {
      return 0.0;
    }
};

class HomebusJalousieActor : public JalousieActor
{
  public:
    float readActualPosition() override
    {
      return 0.0;
    }
};

class ProbusTemperatureSensor : public TemperatureSensor
{
  public:
    float readTemperature() override
    {
      return 0.0;
    }
};

class ProbusJalousieActor : public JalousieActor
{
  public:
    float readActualPosition() override
    {
      return 0.0;
    }
};

class HomeAutomationFabric
{
  public:
    HomeAutomationFabric() = default;
    HomeAutomationFabric( const HomeAutomationFabric& ) = default;
    HomeAutomationFabric( HomeAutomationFabric&& ) = default;
    HomeAutomationFabric& operator=( const HomeAutomationFabric& ) = default;
    HomeAutomationFabric& operator=( HomeAutomationFabric&& ) = default;
    virtual ~HomeAutomationFabric() = default;
    virtual std::unique_ptr< TemperatureSensor > createTemperatureSensor() = 0;
    virtual std::unique_ptr< JalousieActor > createJalousieActor() = 0;
};

class HomebusFabric : public HomeAutomationFabric
{
  public:
    std::unique_ptr< TemperatureSensor > createTemperatureSensor() override
    {
      return std::make_unique< HomebusTemperatureSensor >();
    }
    std::unique_ptr< JalousieActor > createJalousieActor() override
    {
      return std::make_unique< HomebusJalousieActor >();
    }
};

class ProbusFabric : public HomeAutomationFabric
{
  public:
    std::unique_ptr< TemperatureSensor > createTemperatureSensor() override
    {
      return std::make_unique< ProbusTemperatureSensor >();
    }
    std::unique_ptr< JalousieActor > createJalousieActor() override
    {
      return std::make_unique< ProbusJalousieActor >();
    }
};

class HomeController
{
  public:
    explicit HomeController( std::unique_ptr< HomeAutomationFabric > fabric )
      : m_fabric{ std::move( fabric ) }
    {
      createProducts();
    }

    float getActualTemperature() const
    {
      m_tempSensor->readTemperature();
      return m_tempSensor->actualTemperature();
    }

    void up( float value ) const
    {
      m_jalousieActor->up( value );
    }

    void down( float value ) const
    {
      m_jalousieActor->down( value );
    }

  protected:
    void createProducts()
    {
      m_tempSensor = m_fabric->createTemperatureSensor();
      m_jalousieActor = m_fabric->createJalousieActor();
    }

  private:
    std::unique_ptr< HomeAutomationFabric > m_fabric;
    std::unique_ptr< TemperatureSensor > m_tempSensor;
    std::unique_ptr< JalousieActor > m_jalousieActor;
};

inline void abstractFactoryDoWork()
{
  auto controller = std::make_unique< HomeController >( std::make_unique< ProbusFabric >() );

  std::cout << "Aktuelle Temperatur: " << controller->getActualTemperature() << '\n';
}
