#include "singleton.h"

std::shared_ptr<Singleton> Singleton::s_instance;

std::shared_ptr<Singleton> Singleton::instance() { return s_instance; }

std::string Singleton::configuration()
{
    return "Configuration";
}
