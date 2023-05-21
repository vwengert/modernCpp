#include "effictive.h"
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

class Widget
{
    public:
        Widget() = default;
        Widget( Widget&& rhs ) = default;
        Widget( Widget& rhs ) = default;
        Widget& operator=( Widget&& rhs ) = default;
        Widget& operator=( const Widget& rhs ) = default;
        ~Widget() = default;

        bool isValidated() const
        {
            return true;
        }
        bool isProcessed() const
        {
            return true;
        }
        bool isArchived() const
        {
            return true;
        }
};

auto computeSomeValue1()
{
    return 1;
}

auto computeSomeValue2()
{
    return 1;
}

auto computeDivisor( int, int )
{
    return 1;
}

using FilterContainer =
    std::vector<std::function<bool( int )>>;

FilterContainer filters;


void addDivisorFilter()
{
    static auto calc1 = computeSomeValue1();
    static auto calc2 = computeSomeValue2();

    static auto divisor = computeDivisor( calc1, calc2 );

    filters.emplace_back(
    [ = ]( int value ) {
        return value % divisor == 0;
    } );

    ++divisor;
}

class IsValAndArch
{
    public:
        using DataType = std::unique_ptr<Widget>;

        explicit IsValAndArch( DataType&& ptr ) : pw( std::move( ptr ) ) {}

        bool operator()() const
        {
            return pw->isValidated() && pw->isArchived();
        }

    private:
        DataType pw;
};

std::vector<double> data {5.5, 3.5, 7.5};

void runEffective()
{
    addDivisorFilter();

    auto pw = std::make_unique<Widget>();
    auto func = [pw = std::move( pw )] {
        return pw->isValidated() && pw->isArchived();
    };

    auto func11 = IsValAndArch( std::make_unique<Widget>() );


    for( auto d : data ) {
        std::cout << d << " ";
    }

    auto funcDouble = std::bind( []( const std::vector<double>& data ) {
        for( auto d : data ) {
            std::cout << d << " ";
        }

        std::cout << '\n';
    }, std::move( data ) );


    std::cout << '\n';
    funcDouble();

    std::cout << "Size of vector: " << data.size();

    std::cout << '\n';
}
