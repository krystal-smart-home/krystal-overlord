cmake_minimum_required(VERSION 3.10)
project(krystal-overlord)

set(CMAKE_CXX_STANDARD 20)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GCC_COVERAGE_COMPILE_FLAGS "--coverage -O0")
set(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

find_package(Threads)
enable_testing()

if (COV_BUILD)
	message("-- Triggering build with coverage support")
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
	string(REPLACE "-O3" "" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
else()
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2")
endif()

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(test)

