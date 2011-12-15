cmake_minimum_required(VERSION 2.8)

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/cuda")

### Set include dirs
if(WIN32)
    INCLUDE_DIRECTORIES(./ ../lib/external/include)
    LINK_DIRECTORIES(../lib/external/lib/win32)
else()
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    INCLUDE_DIRECTORIES(./)
endif()

### Set common libs
if(WIN32)
#    SET(commonLibs mingw32 opengl32 SDLmain SDL glu32 SDL_image alut)
    #SET(commonLibs mingw32 opengl32 SDLmain SDL glu32 SDL_image libchipmunk.a alut)
    #SET(commonLibs mingw32 opengl32 glu32 libSDLmain.a libSDL.dll.a SDL_image.lib libchipmunk.a alut.lib)
    #Removed alut
    SET(commonLibs mingw32 SDLmain SDL SDL_image m glu32 opengl32 libchipmunk.a SDL_mixer)
else()
    SET(commonLibs GL GLU SDL)
endif()

#SET(CMAKE_C_FLAGS -std=c99 -mwindows)
SET(CMAKE_C_FLAGS "-std=c99 -mwindows")

### Set c files
FILE(GLOB_RECURSE pmuj_c "./*.c")

add_executable (pmuj ${pmuj_c})
target_link_libraries(pmuj ${commonLibs})
