#include "modernLibrary.h"
#include "fileHandling.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

std::ostream &operator<<( std::ostream &os, const std::vector<int> &data )
{
    for( auto &e : data )
    {
        os << e << ' ';
    }
    return os;
}

static const char *const FILENAME = "nums.dat";

int saveVector( const std::vector<int> &nums )
{
    const auto file = openFileInMode( FILENAME, "wb" );
    if( const auto ok = fwrite( nums.data(), sizeof( int ), nums.size(),
                                file.get() ); ok != nums.size() )
    {
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
    if( auto ok = fread( gelesen.data(), sizeof( int ), sz, file.get() ); ok != sz )
    {
        std::cerr << "Fehler beim Lesen" << std::endl;
        return gelesen;
    }
    return gelesen;
}

void vectors()
{
    try
    {
        const std::vector<int> nums{10, 11, 22, 34};
        if( auto ok = saveVector( nums ); ok != 0 )
        {
            return;
        }
        const std::vector<int> gelesen = loadVector();
        if( gelesen.size() < 4 )
        {
            return;
        }
        std::cout << nums << std::endl;
        std::cout << gelesen << std::endl;
    }
    catch( std::invalid_argument )
    {
        return;
    }
    if( remove( FILENAME ) == -1 )
    {
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

bool isPalindrome( const std::string_view &&word )
{
    std::for_each( word.begin(), word.end() - 1,
                   []( const auto & ch )
    {
        std::cout << ch << " - ";
    } );
    std::cout << *word.crbegin() << "\n";
    return std::equal( word.begin(), word.begin() + word.size() / 2, word.rbegin(),
                       []( char first, char second )
    {
        return std::toupper( first ) == std::toupper( second );
    } );
}

void printPalindromes( const std::string &word )
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
    std::for_each( sq.begin(), sq.end(), []( auto n )
    {
        std::cout << n << " ";
    } );
    std::cout << '\n';
    std::string a = "NCC-";
    std::vector<int> b{1, 7, 0, 1};
    std::vector<std::string> c( 4 );
    auto f = []( char d, int i )
    {
        return d + std::to_string( i );
    };
    std::transform( a.begin(), a.end(), b.begin(), c.begin(), f );
    std::for_each( c.begin(), c.end(), []( auto s )
    {
        std::cout << s << " ";
    } );
    std::cout << '\n';
}

void permutate()
{
    int i = 1;
    std::string text = "build";
    do
    {
        std::cout << i << ':' << text << " - ";
        i++;
    }
    while( std::next_permutation( text.begin(), text.end() ) );
}

void streamVector()
{
    std::vector<char> pfad{};
    for( char ch = 'a'; ch <= 'z'; ch++ )
    {
        pfad.push_back( ch );
    }
    std::copy( pfad.begin(), pfad.end(), std::ostream_iterator<char>( std::cout,
               "-" ) );
}

template<typename T, size_t S, std::size_t... Idx>
constexpr std::array < T, S + 1 >
help_append( std::array<T, S> &&data, T &&elem, std::index_sequence<Idx...> )
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
    std::for_each( pics.begin(), pics.end(), []( auto p )
    {
        std::cout << p.name() << '\n';
    } );
    std::cout << '\n';
    Picture neu {"Uhren"};
    auto mehr = append( std::move( pics ), std::move( neu ) );
    std::for_each( mehr.begin(), mehr.end(), []( auto p )
    {
        std::cout << p.name() << '\n';
    } );
}

auto doWork() -> int
{
    vectors();
    palindromes();
    generator();
    permutate();
    streamVector();
    resizeArray();
    return 0;
}
