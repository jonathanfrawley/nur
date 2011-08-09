cmake_minimum_required (VERSION 2.6)
project (pmuj)

# The version number.
set (pmuj_VERSION_MAJOR 1)
set (pmuj_VERSION_MINOR 0)

include_directories( ../lib/sdl/include/SDL )
find_library(sdl_LIB
	NAMES SDL
	PATHS ../lib/sdl/lib
	)

file(GLOB pmuj_c *.c)
add_executable(pmuj ${pmuj_c})
target_link_libraries (pmuj ${sdl_LIB})
