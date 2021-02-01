set(GTEST_LINK gtest gtest_main gmock gmock_main)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fconcepts")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fconcepts")

include(GoogleTest)

function(f_add_test bin files)
	add_executable(${bin} ${files})
	target_link_libraries(${bin} PUBLIC ${PROJECT_NAME}_lib ${GTEST_LINK})
	target_include_directories(${bin} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
	set_property(TARGET ${bin} PROPERTY CXX_STANDARD 20)
	gtest_add_tests(TARGET ${bin})
endfunction()

file (GLOB_RECURSE SL_TEST_CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp)
file (GLOB_RECURSE SL_TEST_SUPERVISOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/supervisor/*.cpp)

f_add_test(core_tests "${SL_TEST_CORE_SRC}")
f_add_test(supervisor_tests "${SL_TEST_SUPERVISOR_SRC}")

