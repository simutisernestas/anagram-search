cmake_minimum_required(VERSION 3.17)
project(anagram)


find_package(OpenSSL)
#target_include_directories(anagram openssl)

include_directories(${OPENSSL_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)

add_executable(anagram md5.h md5.cpp main.cpp)

target_link_libraries(anagram ${OPENSSL_LIBRARIES})