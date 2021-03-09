find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

find_package(jsoncpp REQUIRED)
find_package(Boost 1.71.0 REQUIRED COMPONENTS system coroutine)

if (!Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif()

set (LIBS ${CMAKE_THREAD_LIBS_INIT} spdlog ${JSONCPP_LIBRARIES} ${Boost_SYSTEM_LIBRARY} ${Boost_COROUTINE_LIBRARY})

file (GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${SRC})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${jsoncpp_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_lib PUBLIC ${LIBS})
set_property(TARGET ${PROJECT_NAME}_lib PROPERTY CXX_STANDARD 20)

add_executable(${PROJECT_NAME} ./main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib ${LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)