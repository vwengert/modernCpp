#include "bridge.h"
#include <iostream>

class ElectricEngine : public Engine
{
  public:
    void start()
    {
      std::cout << "Engine start\n";
    }

    void stop()
    {
      std::cout << "Engine stop\n";
    }
};

ElectricCar::ElectricCar()
  : Car{ std::make_unique< ElectricEngine >() }
{
}

void ElectricCar::drive()
{
  getEngine()->start();
  std::cout << "Driving\n";
  getEngine()->stop();
}
