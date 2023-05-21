#include <cassert>
#include <future>
#include <initializer_list>
#include <memory>
#include <modernLibrary.h>

class Foo
{
    public:
        Foo( int* ptr ) : ptr_{ptr} {}
        auto set_ptr_val( int v ) const
        {
            *ptr_ = v;
        }
    private:
        int* ptr_ = nullptr;
};

class Buffer
{
    public:
        Buffer( const std::initializer_list<float>& values ) : size_{values.size()}
        {
            ptr_ = new float[values.size()];
            std::copy( values.begin(), values.end(), ptr_ );
        }
        // copy constructor and assignment operator
        Buffer( const Buffer& other ) : size_{other.size_}
        {
            ptr_ = new float[size_];
            std::copy( other.ptr_, other.ptr_ + size_, ptr_ );
        }
        auto& operator=( const Buffer& other )
        {
            delete[] ptr_;
            ptr_ = new float[other.size_];
            size_ = other.size_;
            std::copy( other.ptr_, other.ptr_ + size_, ptr_ );
            return *this;
        }
        // move constructor and assignment operator
        Buffer( Buffer&& other ) noexcept : size_{other.size_}, ptr_{other.ptr_}
        {
            other.ptr_ = nullptr;
            other.size_ = 0;
        }
        auto& operator=( Buffer&& other ) noexcept
        {
            ptr_ = other.ptr_;
            size_ = other.size_;
            other.ptr_ = nullptr;
            other.size_ = 0;
            return *this;
        }

        ~Buffer()
        {
            delete[] ptr_;
            ptr_ = nullptr;
        }

        auto begin() const
        {
            return ptr_;
        }
        auto end() const
        {
            return ptr_ + size_;
        }
    private:
        size_t size_{0};
        float* ptr_{nullptr};
};

class Button
{
    public:
        Button() {}
        auto set_title( const std::string& s )
        {
            title_ = s;
        }
        auto set_title( std::string&& s )
        {
            title_ = std::move( s );
        }
        std::string title_;
};

auto get_ok()
{
    return std::string( "OK" );
}

class Widget
{
    public:
        Widget( const int& x, const int& y ) : x_{x}, y_{y}
        {
            assert( is_valid() );
        }

        auto update( const int& x, const int& y )
        {
            assert( x != y && is_valid() );
            auto temp_x = x;
            auto temp_y = y;
            std::swap( x_, temp_x );
            std::swap( y_, temp_y );
            assert( is_valid() );
        }
    private:
        int x_{};
        int y_{};
        bool is_valid() const
        {
            return x_ != y_;
        }
};

auto main() -> int
{
    auto i = 0;
    auto foo = Foo{&i};
    foo.set_ptr_val( 42 );
    auto bar = std::move( foo );
    bar.set_ptr_val( 22 );

    auto button = Button{};

    auto str = std::string{"OK"};
    button.set_title( str );

    auto str2 = std::string{"OK"};
    button.set_title( std::move( str2 ) );

    button.set_title( get_ok() );

    auto str3 = get_ok();
    button.set_title( str3 );

    const auto str4 = get_ok();
    button.set_title( std::move( str4 ) );

    auto fut = std::async( doWork );
}
