cmake_minimum_required(VERSION 3.2)
project(sls-engine)


set(SLSENGINE sls-engine)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


set(DEPS)

if (EMSCRIPTEN)
  set(GLAD extern/glad-es/)
else ()
  set(GLAD extern/glad)
endif ()


set(SRC src/main.c
    src/slsapp.c src/slsapp.h
    src/slsrenderer.c src/slsrenderer.h
    src/shaderutils.c src/shaderutils.h
    src/slsmacros.h
    src/common.h
    src/results.h
    src/slsmath.c src/slsmath.h
    ${GLAD}/src/glad.c
    ${GLAD}/include/glad/glad.h
    ${GLAD}/include/KHR/khrplatform.h
    extern/vendor/include/linmath.h
    extern/vendor/include/nk_private/nuklear.h
    extern/vendor/include/nk_private/nuklear_sdl_gl3.h
    extern/vendor/include/nk_private/nuklear_sdl_gles2.h
    src/sls-nuklear.c src/sls-nuklear.h)

#check if libm is required
include(CheckFunctionExists)
CHECK_FUNCTION_EXISTS(pow LIBM_EXISTS)
if (NOT LIBM_EXISTS)
  unset(LIBM_EXISTS)
  list(APPEND DEPS m)

endif ()

if (NOT EMSCRIPTEN)
  find_package(SDL2 REQUIRED)
  find_package(OpenGL REQUIRED)

  list(APPEND DEPS
       OpenGL::GL
       SDL2::SDL2 SDL2::SDL2main)
  list(APPEND SRC
       src/desktop/desktop-app.c)
else ()
  list(APPEND SRC
       src/emscripten/em-app.c)
endif ()


set(TEST_SRC
    ${SRC}
    extern/vendor/include/catch.hpp
    tests/tests-main.cpp
    tests/math-tests.cpp)


list(REMOVE_ITEM TEST_SRC src/main.c)

add_executable(${SLSENGINE} ${SRC})
add_executable(tests ${SRC} ${TEST_SRC})


target_link_libraries(${SLSENGINE} ${DEPS})
target_link_libraries(tests ${DEPS})

target_compile_definitions(tests PUBLIC SLS_TEST_RUNNER)
set_target_properties(${SLSENGINE} tests
                      PROPERTIES
                      C_STANDARD 11
                      CXX_STANDARD 14
                      )

set(INCLUDE_DIRS
    extern/vendor/include
    ${GLAD}/include/
    src)
target_include_directories(tests
                           PRIVATE
                           ${INCLUDE_DIRS}
                           )
target_include_directories(${SLSENGINE}
                           PRIVATE
                           ${INCLUDE_DIRS}
                           )
if (EMSCRIPTEN)
  set_property(
    TARGET ${SLSENGINE} tests
    APPEND_STRING
    PROPERTY COMPILE_OPTIONS
    -s USE_SDL=2
  )

  set_property(
    TARGET ${SLSENGINE} tests
    PROPERTY
    SUFFIX ".html")
  set_property(
    TARGET ${SLSENGINE} tests
    APPEND_STRING
    PROPERTY
    LINK_FLAGS "-s USE_SDL=2 -s USE_WEBGL2=1 -s FULL_ES3=1 --preload-file assets --use-preload-plugins")
  set_property(
    TARGET ${SLSENGINE} tests
    APPEND_STRING
    PROPERTY

    LINK_FLAGS_DEBUG "-s USE_SDL=2 --emrun")
elseif (WIN32)
  set_property(TARGET ${SLSENGINE} tests
               APPEND_STRING
               PROPERTY COMPILE_DEFINITIONS
               _CRT_SECURE_NO_WARNINGS
               )
endif ()
