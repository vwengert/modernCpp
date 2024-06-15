#include "bridge.h"

class ElectricEngine : public Engine
{
  public:
    explicit ElectricEngine( std::ostream& stream )
      : Engine{ stream }
    {
      getStream() << "Using stream";
    }

    void start() override
    {
      getStream() << "Engine start\n";
    }

    void stop() override
    {
      getStream() << "Engine stop\n";
    }
};

ElectricCar::ElectricCar( std::ostream& stream )
  : Car{ std::make_unique< ElectricEngine >( stream ), stream }
{
}

void ElectricCar::drive()
{
  getEngine()->start();
  getStream() << "Driving\n";
  getEngine()->stop();
}

std::ostream& Car::getStream()
{
  return m_stream;
}
