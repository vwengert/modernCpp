#pragma once
#include "modernLibraryExport.h"
#include <memory>
#include <string>

class MODERN_LIBRARY_API Singleton final
{
  public:
    static std::shared_ptr< Singleton > instance();

    static std::string configuration();

  private:
    Singleton() = default;

    static std::shared_ptr< Singleton > m_instance;
};
