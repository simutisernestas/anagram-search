cmake_minimum_required(VERSION 3.16.3)
project(anagram)

set(CMAKE_CXX_STANDARD 20)

add_executable(anagram md5.h md5.cpp main.cpp)