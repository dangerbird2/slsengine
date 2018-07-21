cmake_minimum_required(VERSION 3.2)
project(sls-engine)


set(SLSENGINE sls-engine)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

set(DEPS
    OpenGL::GL
    GLEW::GLEW
    SDL2::SDL2
    SDL2::SDL2main
    )

set(SRC src/main.c
    src/slsapp.c src/slsapp.h
    src/slsrenderer.c src/slsrenderer.h
    src/shaderutils.c src/shaderutils.h
    src/slsmacros.h
    src/common.h
    )

add_executable(${SLSENGINE} ${SRC})
target_link_libraries(${SLSENGINE} ${DEPS})
set_target_properties(${SLSENGINE}
    PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 14
    )
