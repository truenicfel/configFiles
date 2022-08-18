cmake_minimum_required(VERSION 3.23)
project(configFiles LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(extern)

add_executable(configFiles main.cpp)
