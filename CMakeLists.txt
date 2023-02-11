cmake_minimum_required(VERSION 3.15)

project(ToiletGame)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./src)

include_directories(./src)

add_executable(ToiletGame main.cc)

target_link_libraries(ToiletGame
PRIVATE
TG)