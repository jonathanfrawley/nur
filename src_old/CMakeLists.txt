cmake_minimum_required (VERSION 2.6)
project (pmuj)

# The version number.
set (pmuj_VERSION_MAJOR 1)
set (pmuj_VERSION_MINOR 0)

#include_directories( ../lib/sdl/include/SDL )
#find_library(sdl_LIB
#	NAMES SDL
#	PATHS ../lib/sdl/lib
#	)

Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
	message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

file(GLOB pmuj_cpp *.cpp)
add_executable(pmuj ${pmuj_cpp})
target_link_libraries (pmuj ${SDL_LIBRARY}
	   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
	   )
