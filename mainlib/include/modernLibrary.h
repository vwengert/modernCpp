#include <string>
#include <vector>

auto doWork() -> int;
auto isPalindrome( const std::string_view&& word ) -> bool;

struct Squares {
    mutable int n = 0;
    int operator()() const
    {
        ++n;
        return n * n;
    }
};

class Picture
{
        std::vector<char> data_;
        std::string name_;
    public:
        explicit Picture( const std::string& name ) : data_( 1000, 0 ), name_{name} {}
        auto name() const
        {
            return name_;
        }
};
