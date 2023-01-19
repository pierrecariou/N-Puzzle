cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -lstdc++")

# set the project name
project(NPuzzle)

#add_subdirectory(SFML-2.5.1)

add_executable(NPuzzle
  ${CMAKE_SOURCE_DIR}/src/NPuzzleApp.cpp
  ${CMAKE_SOURCE_DIR}/src/NPuzzle.cpp
  ${CMAKE_SOURCE_DIR}/src/NPuzzleFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/AStarAlgorithm.cpp
  ${CMAKE_SOURCE_DIR}/src/ManhattanDistance.cpp
  ${CMAKE_SOURCE_DIR}/src/LinearConflict.cpp
  #${CMAKE_SOURCE_DIR}/src/Gui.cpp
)

#target_link_libraries(NPuzzle PUBLIC sfml-graphics)

target_include_directories(NPuzzle PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

#set_property(TARGET tgt PROPERTY CXX_STANDARD 11)
