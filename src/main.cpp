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
};

auto main() -> int
{
  BackgroundTask task;
  std::thread th1( task );
  ThreadGuard guard( th1 );

  return 0;
}
