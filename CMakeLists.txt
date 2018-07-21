cmake_minimum_required(VERSION 3.2)
project(sls-engine)


set(SLSENGINE sls-engine)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)




set(DEPS)

if(NOT EMSCRIPTEN)
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)

    list(APPEND DEPS
        OpenGL::GL
        SDL2::SDL2 SDL2::SDL2main GLEW::GLEW)

else()
endif()


set(SRC src/main.c
    src/slsapp.c src/slsapp.h
    src/slsrenderer.c src/slsrenderer.h
    src/shaderutils.c src/shaderutils.h
    src/slsmacros.h
    src/common.h
    src/results.h
    )

add_executable(${SLSENGINE} ${SRC})
target_link_libraries(${SLSENGINE} ${DEPS})
set_target_properties(${SLSENGINE}
    PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 14
    )
if(EMSCRIPTEN)
    set_property(
        TARGET ${SLSENGINE}
        APPEND_STRING
        PROPERTY COMPILE_OPTIONS
        -s USE_SDL=2
        )

    set_property(TARGET ${SLSENGINE}
      PROPERTY
      SUFFIX ".html")
    set_property(
        TARGET ${SLSENGINE}
        APPEND_STRING
        PROPERTY
        LINK_FLAGS "-s USE_SDL=2 -s USE_WEBGL2=1")
    set_property(
        TARGET ${SLSENGINE}
        APPEND_STRING
        PROPERTY

        LINK_FLAGS_DEBUG "-s USE_SDL=2 --emrun")
endif()
