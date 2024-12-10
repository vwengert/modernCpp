#pragma once

#ifdef _WIN32
#ifdef BASIC_LIBRARY_EXPORTS
#define BASIC_LIBRARY_API __declspec( dllexport )
#else
#define BASIC_LIBRARY_API __declspec( dllimport )
#endif
#else
#define BASIC_LIBRARY_API __attribute__( ( visibility( "default" ) ) )
#endif
