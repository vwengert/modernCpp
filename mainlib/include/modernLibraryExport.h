#pragma once

#ifdef _WIN32
#ifdef MODERN_LIBRARY_EXPORTS
#define MODERN_LIBRARY_API __declspec( dllexport )
#else
#define MODERN_LIBRARY_API __declspec( dllimport )
#endif
#else
#define MODERN_LIBRARY_API __attribute__( ( visibility( "default" ) ) )
#endif
