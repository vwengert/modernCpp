#pragma once

#ifdef _WIN32
#ifdef TESTDRIVEN_LIBRARY_EXPORTS
#define TESTDRIVEN_LIBRARY_API __declspec( dllexport )
#else
#define TESTDRIVEN_LIBRARY_API __declspec( dllimport )
#endif
#else
#define TESTDRIVEN_LIBRARY_API __attribute__( ( visibility( "default" ) ) )
#endif
