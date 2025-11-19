cmake_minimum_required(VERSION 3.10)
project(homework2)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

add_executable(homework2 ${SOURCES})
