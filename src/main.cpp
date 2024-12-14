#include "basicLibrary.h"
#include "modernLibrary.h"
#include "moderncpp_version.h"
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex; // NOLINT(*-avoid-non-const-global-variables)

class ThreadGuard
{
  std::thread& m_thread;

  public:
    explicit ThreadGuard( std::thread& thread )
      : m_thread( thread )
    {
    }

    ~ThreadGuard()
    {
      if(m_thread.joinable())
      {
        m_thread.join();
      }
    }

    ThreadGuard( ThreadGuard const& ) = delete;

    ThreadGuard& operator=( ThreadGuard const& ) = delete;

    ThreadGuard( ThreadGuard&& ) = delete;

    ThreadGuard& operator=( ThreadGuard&& ) = delete;
};

class BackgroundTask
{
  public:
    void operator()() const
    {
#ifdef WIN32
      _sleep( 1 );
#else
      sleep( 1 );
#endif
      std::lock_guard< std::mutex > guard( mutex );
      doWork();
    }

    void operator()( const int value, const std::string& text ) const
    {
#ifdef WIN32
      _sleep( 1 );
#else
      sleep( 1 );
#endif
      std::lock_guard< std::mutex > guard( mutex );
      doWork();
      std::cout << "Value: " << value << " Text: " << text << std::endl;
    }
};

auto main() -> int
{
  doWork();
  doBasicWork();
  std::cout << "Version: " << PROJECT_CPP_VERSION << std::endl;
  return 0;
}
