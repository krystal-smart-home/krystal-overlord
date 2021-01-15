cmake_minimum_required(VERSION 3.10)
project(krystal-overlord)

set(CMAKE_CXX_STANDARD 20)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(Threads)

enable_testing()

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(test)
