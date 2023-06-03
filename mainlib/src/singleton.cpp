#include "singleton.h"


Singleton* Singleton::s_instance = new Singleton();

Singleton* Singleton::instance()
{
    return s_instance;
}

std::string Singleton::configuration()
{
    return "Configuration";
}

Singleton::Singleton()
{
}
