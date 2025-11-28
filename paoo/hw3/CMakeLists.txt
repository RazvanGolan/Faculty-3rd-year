cmake_minimum_required(VERSION 3.10)
project(homework3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

add_executable(homework3 ${SOURCES})
