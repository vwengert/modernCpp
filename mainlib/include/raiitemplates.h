#pragma once

template< typename T >
class scoped_ptr
{
  public:
    explicit scoped_ptr( T* p )
      : p_( p )
    {
    }
    ~scoped_ptr()
    {
      delete p_;
    }
    T* operator->()
    {
      return p_;
    }
    const T* operator->() const
    {
      return p_;
    }
    T& operator*()
    {
      return *p_;
    }
    const T& operator*() const
    {
      return *p_;
    }

  private:
    T* p_;
};

template< typename T >
class raii
{
  public:
    explicit raii( T* p )
      : p_( p )
    {
    }
    ~raii()
    {
      delete p_;
    }

  private:
    T* p_;
};

struct object_counter
{
    static inline int count;
    static inline int all_count;
    object_counter()
    {
      ++count;
      ++all_count;
    }
    ~object_counter()
    {
      --count;
    }
};
