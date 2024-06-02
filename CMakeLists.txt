cmake_minimum_required(VERSION 3.16)
project(untitled4 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled4 main.c str_utils.h lexer.h token.h parser.h ast.h interpreter.h)