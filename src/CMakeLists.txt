find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

find_package(jsoncpp REQUIRED)

set (LIBS ${CMAKE_THREAD_LIBS_INIT} spdlog xvent ${JSONCPP_LIBRARIES} pistache_static)

file (GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(REMOVE_ITEM SRC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${SRC})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${jsoncpp_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_lib PUBLIC ${LIBS})

add_executable(${PROJECT_NAME} ./main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib ${LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 20)

