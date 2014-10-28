cmake_minimum_required(VERSION 2.8.4)

set (demo_SOURCES
    main.c)

add_executable(demo ${demo_SOURCES})
target_link_libraries(demo slsengine ${LIBS})

add_custom_command(
	TARGET demo POST_BUILD
	COMMAND demo
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	VERBATIM)