#include <fileHandling.h>
#include <array>
#include <string>
#include <iostream>

#ifdef __win
    using std::FILE
#endif

using Destroyer = std::function<void( FILE* )>;
void closeFile( FILE* file )
{
    std::fclose( file );
}

std::unique_ptr<FILE, std::function<void( FILE* )>> openFileInMode(
                                                     const char* name, const char* mode )
{
    FILE* file;

    if( const auto err = fopen_s( &file, name, mode ); err != 0 ) {
        std::string error =
            "Cannot open file with error ";
        std::cerr << "Cannot open file with error";
        throw std::invalid_argument( error );
    }

    auto ptr = std::unique_ptr<FILE, Destroyer>( file, &closeFile );

    return ptr;
}
