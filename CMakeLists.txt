cmake_minimum_required(VERSION 2.8.4)
project(slsengine)

set (CLANG_CFLAGS "--std=gnu11 -fblocks")

set (USE_CLANG "TRUE")

if (USE_CLANG)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${CLANG_CFLAGS})
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

find_library(SDL2 SDL2)
find_library(SDL2_IMAGE SDL2_image)
find_library(SDL2_TTF SDL2_ttf)
find_library(SDL2_MIXER SDL2_mixer)
find_library(BLOCKS BlocksRuntime)
find_library(DISPATCH dispatch)

set (DIRS ${PROJECT_SOURCE_DIR}/src ${GLIB_INCLUDE_DIRS})

include_directories(${DIRS})
set (LIBS
    ${GLIB_LIBRARIES}
    ${APR_LIBRARIES}

    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${SDL2}
    ${SDL2_IMAGE}
    ${SDL2_TTF}
    ${SDL2_MIXER}
    ${BLOCKS}
    ${DISPATCH})

add_subdirectory(src/slsengine)
add_subdirectory(src/tests)
add_subdirectory(src/demo)


