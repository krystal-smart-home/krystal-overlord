set(GTEST_LINK gtest gtest_main gmock gmock_main)

include(GoogleTest)

function(_add_test module)
	file (GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/${module}/*.cpp)
	add_executable(${module}_tests ${src})
	target_link_libraries(${module}_tests PUBLIC ${PROJECT_NAME}_lib ${GTEST_LINK})
	target_include_directories(${module}_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
	set_property(TARGET ${module}_tests PROPERTY CXX_STANDARD 20)
	gtest_add_tests(TARGET ${module}_tests)
endfunction()

_add_test(core)