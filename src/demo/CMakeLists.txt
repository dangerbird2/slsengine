cmake_minimum_required(VERSION 2.8.4)

set (demo_SOURCES
    main.c)

add_executable(demo ${demo_SOURCES})
target_link_libraries(demo slsengine ${LIBS})