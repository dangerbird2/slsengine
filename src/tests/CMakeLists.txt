cmake_minimum_required(VERSION 2.8.4)

enable_testing()
set (tests_SOURCES
    main.c
    math-tests.c
    mesh-test.c
    component-test.c
    content-test.c
    statestack-test.c)

include_directories(${DIRS})
add_executable(tests ${tests_SOURCES})
target_link_libraries(tests slsengine ${LIBS})

add_custom_command(
	TARGET tests POST_BUILD
	COMMAND tests
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	VERBATIM)