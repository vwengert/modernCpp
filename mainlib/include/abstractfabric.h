#pragma once
#include <iostream>
#include <memory>

class TemperatureSensor
{
  public:
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
    float m_actualTemperature;
};

class JalousieActor
{
  public:
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

      if( m_actualPosition > 100 )
      {
        m_actualPosition = 100;
      }
    }
    virtual float readActualPosition() = 0;
    virtual float setActualPosition( float value )
    {
      m_actualPosition = value;
      return m_actualPosition;
    }

  private:
    float m_actualPosition;
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
    virtual ~HomeAutomationFabric() = default;
    virtual std::unique_ptr< TemperatureSensor > createTemperatureSensor() = 0;
    virtual std::unique_ptr< JalousieActor > createJalousieActor() = 0;
};

class HomebusFabric : public HomeAutomationFabric
{
  public:
    ~HomebusFabric() override = default;
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
    ~ProbusFabric() override = default;
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
    explicit HomeController( HomeAutomationFabric* fabric )
      : m_fabric{ fabric }
    {
      createProducts();
    }

    ~HomeController()
    {
      delete m_fabric;
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
    HomeAutomationFabric* m_fabric;

    std::unique_ptr< TemperatureSensor > m_tempSensor;
    std::unique_ptr< JalousieActor > m_jalousieActor;
};

inline void abstractFactoryDoWork()
{
  auto controller = std::make_unique< HomeController >( new ProbusFabric() );

  std::cout << "Aktuelle Temperatur: " << controller->getActualTemperature() << '\n';
}
