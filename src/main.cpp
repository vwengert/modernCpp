#include "moderncpp_version.h"
#include <iostream>
#include <modernLibrary.h>
#include <thread>

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
      if( m_thread.joinable() )
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
      doWork();
    }
    void operator()( const int value, const std::string& text ) const
    {
      doWork();
      std::cout << "Value: " << value << " Text: " << text << std::endl;
    }
};

auto main() -> int
{
  std::cout << "Version: " << PROJECT_CPP_VERSION << std::endl;
  BackgroundTask task;
  std::thread th1( task, 1, "Hello" );
  ThreadGuard guard( th1 );

  return 0;
}
