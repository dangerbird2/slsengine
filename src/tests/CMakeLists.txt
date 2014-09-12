cmake_minimum_required(VERSION 2.8.4)

set (tests_SOURCES
    main.c
    math-tests.c
    mesh-test.c
    component-test.c
    content-test.c
    statestack-test.c)


add_executable(tests ${tests_SOURCES})
target_link_libraries(tests slsengine ${LIBS})
