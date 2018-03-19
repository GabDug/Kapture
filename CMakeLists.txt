cmake_minimum_required(VERSION 3.9)
project(Kaptur C)

# includes cmake/FindSDL2.cmake
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


#find_package(SDL REQUIRED)

# include_directories(${SDL2_INCLUDE_DIR})
# include_directories(${SDL_INCLUDE_DIR})


#set(SDL_PATH "C:\\SDL")

#[[set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SDL2_LIBRARY ${PROJECT_SOURCE_DIR}/lib)
]]
include_directories(${PROJECT_SOURCE_DIR}/SDL/include)
link_directories(${PROJECT_SOURCE_DIR}/SDL/lib)

set(CMAKE_C_STANDARD 99)


# #target_link_libraries(Kaptur ${SDL2_LIBRARY})

# target_link_libraries(Kaptur )
add_executable(main sources/main.c sources/game.c sources/display.c sources/tools.c sources/headers/constant.h sources/headers/game.h sources/headers/tools.h sources/headers/display.h sources/files.c sources/headers/files.h)
#target_link_libraries(mainsdl ${SDL_LIBRARY})
#target_link_libraries(mainsdl SDLmain SDL)