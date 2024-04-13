#pragma once

#include <mutex>

class MutexGuard
{
  public:
    explicit MutexGuard( std::mutex& m )
      : m_( m )
    {
      if( !m_.try_lock() )
      {
        throw 1;
      }
    }
    ~MutexGuard()
    {
      m_.unlock();
    }

  private:
    std::mutex& m_;
};