#include <forward_list>
#include <memory>
#include <modernLibrary.h>
#include <effictive.h>
#include <fileHandling.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>
#include <thread>
#include <future>
#include <exception>

struct Foo {
    auto val() const
    {
        return m_;
    }
    auto& cref() const
    {
        return m_;
    }
    auto& mref()
    {
        return m_;
    }
    int m_{};
};

std::ostream& operator<<( std::ostream& os, const std::vector<int>& data )
{
    for( auto& e : data ) {
        os << e << ' ';
    }

    return os;
}

static const char* const FILENAME = "nums.dat";

int saveVector( const std::vector<int>& nums )
{
    const auto file = openFileInMode( FILENAME, "wb" );

    std::cerr << std::endl;

    if( const auto ok = fwrite( nums.data(), sizeof( int ), nums.size(),
                                file.get() ); ok != nums.size() ) {
        std::cerr << "Fehler beim Schreiben" << std::endl;
        return -1;
    }

    return 0;
}

auto loadVector() -> std::vector<int>
{
    const auto file = openFileInMode( FILENAME, "rb" );
    std::vector<int> gelesen{};
    const size_t sz = 4;
    gelesen.resize( sz );

    if( auto ok = fread( gelesen.data(), sizeof( int ), sz, file.get() ); ok != sz ) {
        std::cerr << "Fehler beim Lesen" << std::endl;
        return gelesen;
    }

    std::list<int> n;
    return gelesen;
}

void vectors()
{
    try {
        const std::vector<int> nums{10, 11, 22, 34};

        if( auto ok = saveVector( nums ); ok != 0 ) {
            return;
        }

        const std::vector<int> gelesen = loadVector();

        if( gelesen.size() < 4 ) {
            return;
        }

        std::cout << nums << std::endl;
        std::cout << gelesen << std::endl;
    } catch( std::invalid_argument ) {
        return;
    }

    if( remove( FILENAME ) == -1 ) {
        std::cerr << "Fehler beim Löschen der Datei" << std::endl;
    }

    std::vector<int> v1 = {1, 2, 4, 4, 3};
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> result;
    std::sort( v1.begin(), v1.end() );
    std::sort( v2.begin(), v2.end() );
    std::set_difference( v2.begin(), v2.end(), v1.begin(), v1.end(),
                         std::back_inserter( result ) );
    std::cout << result << std::endl;
    result.clear();
    std::set_intersection( v1.begin(), v1.end(), v2.begin(), v2.end(),
                           std::back_inserter( result ) );
    std::cout << result << std::endl;
}

bool isPalindrome( const std::string_view&& word )
{
    std::for_each( word.begin(), word.end() - 1,
    []( const auto & ch ) {
        std::cout << ch << " - ";
    } );
    std::cout << *word.crbegin() << "\n";
    return std::equal( word.begin(), word.begin() + word.size() / 2, word.rbegin(),
    []( char first, char second ) {
        return std::toupper( first ) == std::toupper( second );
    } );
}

void printPalindromes( const std::string& word )
{
    isPalindrome( word ) ? std::cout << "ist ein Palindrom.\n"
                                     : std::cout << "ist kein Palindrom.\n";
}

void palindromes()
{
    std::cout << std::boolalpha;
    printPalindromes( "Otto" );
    printPalindromes( "Volker" );
    printPalindromes( "Reliefpfeiler" );
}

void generator()
{
    std::vector<int> sq( 10 );
    std::generate( sq.begin(), sq.end(), Squares{} );
    std::for_each( sq.begin(), sq.end(), []( auto n ) {
        std::cout << n << " ";
    } );
    std::cout << '\n';
    std::string a = "NCC-";
    std::vector<int> b{1, 7, 0, 1};
    std::vector<std::string> c( 4 );
    auto f = []( char d, int i ) {
        return d + std::to_string( i );
    };
    std::transform( a.begin(), a.end(), b.begin(), c.begin(), f );
    std::for_each( c.begin(), c.end(), []( auto s ) {
        auto n = int( 3 );
        std::cout << s << " " << n;
    } );
    std::cout << '\n';
}

void permutate()
{
    int i = 1;
    std::string text = "build";

    do {
        std::cout << i << ':' << text << " - ";
        i++;
    } while( std::next_permutation( text.begin(), text.end() ) );
}

void streamVector()
{
    std::vector<char> pfad{};

    for( char ch = 'a'; ch <= 'z'; ch++ ) {
        pfad.push_back( ch );
    }

    std::copy( pfad.begin(), pfad.end(), std::ostream_iterator<char>( std::cout,
                                                                      "-" ) );
}

template<typename T, size_t S, std::size_t... Idx>
constexpr std::array < T, S + 1 >
help_append( std::array<T, S>&& data, T&& elem, std::index_sequence<Idx...> )
{
    return {std::get<Idx>( std::forward<std::array<T, S>>( data ) )..., std::forward<T>( elem ) };
}

template<typename T, size_t S>
constexpr auto
append( std::array<T, S> data, T elem )
{
    return help_append( std::move( data ), std::move( elem ),
                        std::make_index_sequence<S> {} );
}

void resizeArray()
{
    std::cout << '\n';
    std::array<Picture, 3> pics{Picture{"Mona"}, Picture{"Schrei"}, Picture{"Vincent"}};
    std::for_each( pics.begin(), pics.end(), []( auto p ) {
        std::cout << p.name() << '\n';
    } );
    std::cout << '\n';
    Picture neu {"Uhren"};
    auto mehr = append( std::move( pics ), std::move( neu ) );
    std::for_each( mehr.begin(), mehr.end(), []( auto p ) {
        std::cout << p.name() << '\n';
    } );
}

int ackermann( int m, int n )
{
    if( m == 0 ) {
        return n + 1;
    }

    if( n == 0 ) {
        return ackermann( m - 1, 1 );
    }

    return ackermann( m - 1, ackermann( m, n - 1 ) );
}

void langeBerechnung( std::promise<int> intPromise )
{
    try {
        int result = ackermann( 3, 12 );
        intPromise.set_value( result );
    } catch( std::exception& e ) {
        intPromise.set_exception( std::make_exception_ptr( e ) );
    } catch( ... ) {
        intPromise.set_exception( std::current_exception() );
    }
}

void usePromise()
{
    std::promise<int> intPromise;
    std::future<int> intFuture = intPromise.get_future();
    std::thread th{ langeBerechnung,
                    std::move( intPromise ) };
    th.detach();
    int result = intFuture.get();
    std::cout << result << std::endl;
}

void threads()
{
    std::thread thread1{ [] {
            vectors();
            palindromes();
        } };
    std::thread thread2{ [] {
            generator();
            permutate();
        } };
    std::thread thread3{ [] {
            streamVector();
            resizeArray();
        } };
    thread1.join();
    thread2.join();
    thread3.join();

    usePromise();
}

class iCol
{
    public:
        virtual void output() = 0;
};

template<class T>
class collector : public iCol
{
    public:
        collector( std::unique_ptr<T> t ) : t( std::move( t ) ) {};
        std::unique_ptr<T> t;

        void output() override
        {
            std::cout << "class: " << typeid( *t ).name() << "\nvalue: " << *t << "\n";
        }

};

auto num_hamlet( const std::forward_list<std::string>& books )
{
    return std::count( books.begin(), books.end(), "Hamlet" );
}


auto doWork() -> int
{

#ifdef _
    threads();
#endif
    auto count = num_hamlet( {"Hamlet", "or not to be", "Hamlet"} );
    std::cout << count << " numbers of Hamlet found \n";

    Foo foo{5};

    auto z = foo.mref() = 7;
    auto x = foo.val();
    auto y = foo.cref();

    std::cout << x << " " << y << " " << z << "\n";

    runEffective();
    std::vector<std::unique_ptr<iCol>> data;
    data.emplace_back( std::make_unique<collector<int>>(
                           std::make_unique<int>( 1 ) ) );
    data.emplace_back( std::make_unique<collector<std::string>>(
                           std::make_unique<std::string>( "hello world" ) ) );

    for( const auto& d : data ) {
        d->output();
    }

    return 0;
}
