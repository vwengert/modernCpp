#include "singleton.h"

std::shared_ptr< Singleton > Singleton::m_instance;

std::shared_ptr< Singleton > Singleton::instance()
{
  return m_instance;
}

std::string Singleton::configuration()
{
  return "Configuration";
}
