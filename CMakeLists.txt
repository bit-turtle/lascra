cmake_minimum_required( VERSION 3.22..3.29 )

project( lascra LANGUAGES CXX )

# fetch dependencies
include( FetchContent )

# argh
FetchContent_Declare( argh
	GIT_REPOSITORY https://github.com/adishavit/argh.git
	GIT_TAG master
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable( argh )

# bparser
set( BPARSER_TESTS CACHE BOOL OFF)
FetchContent_Declare( bparser
	GIT_REPOSITORY https://github.com/bit-turtle/bparser.git
	GIT_TAG main
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable( bparser )

# ziplib
FetchContent_Declare( ZipLib
	GIT_REPOSITORY https://github.com/bit-turtle/ZipLib
	GIT_TAG master
	EXCLUDE_FROM_ALL
	SYSTEM
)
FetchContent_MakeAvailable( ZipLib )

# build lascra
add_subdirectory( src )
