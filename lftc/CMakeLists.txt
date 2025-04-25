cmake_minimum_required(VERSION 3.30)
project(lftc C)

set(CMAKE_C_STANDARD 11)

include_directories(AtomC/files)

add_executable(main
        AtomC/main.c
        AtomC/files/lexer.c
        AtomC/files/lexer.h
        AtomC/files/utils.c
        AtomC/files/utils.h
        AtomC/files/ad.c
        AtomC/files/ad.h
        AtomC/files/parser.c
        AtomC/files/parser.h
)