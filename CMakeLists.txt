cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)

# Add the -pthread flag to CMAKE_CXX_FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags using the correct syntax
set(CMAKE_CXX_FLAGS "-Wall")

project(SnakeGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
# Add image loading
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

# Copy the 'resources' folder
file(COPY ${CMAKE_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_BINARY_DIR})

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/logfile.cpp)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} pthread)