#pragma once

#include <mutex>

class MutexGuard
{
  public:
    explicit MutexGuard( std::mutex& mutex )
      : m_mutex( mutex )
    {
      if( !m_mutex.try_lock() )
      {
        throw 1;
      }
    }
    ~MutexGuard()
    {
      m_mutex.unlock();
    }
    MutexGuard() = delete;
    MutexGuard( const MutexGuard& ) = delete;
    MutexGuard( MutexGuard&& ) = default;
    MutexGuard& operator=( const MutexGuard& ) = delete;
    MutexGuard& operator=( MutexGuard&& ) = delete;

  private:
    std::mutex& m_mutex; // NOLINT(*avoid-const-or-ref-data-members)
};
