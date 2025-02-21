cmake_minimum_required(VERSION 3.10)
project(Redis-Clone)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Werror -pedantic-errors -Wall")
set(SOURCE main.cpp)
add_executable(TestBinary ${SOURCE})

