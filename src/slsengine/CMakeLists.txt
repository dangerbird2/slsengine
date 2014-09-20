cmake_minimum_required(VERSION 2.8.4)
set(slsengine_SOURCES
    setup.c
    linalg/sls-mat4.c
    linalg/vectypes.c
    graphics/shaderutils.c
    graphics/sls-content.c
    graphics/sls-mesh.c
    graphics/sls-shader.c
    graphics/sls-sprite.c
    window/sls-clock.c
    window/sls-window.c
    window/sls-glwindow.c
    window/sls-gamewindow.c
    window/sls-renderwindow.c
    window/sls-statestack.c
    )

include_directories(${DIRS} )
link_directories(${GLIB_LINK_DIRS})


add_library(slsengine ${slsengine_SOURCES})
target_link_libraries(slsengine ${LIBS})

