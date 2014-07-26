#ifndef __SLS_SCENE_H__
#define __SLS_SCENE_H__

#include <glib.h>
#include <SDL2/SDL.h>
#include "window/window.h"

struct _slsSceneProto {
    runCallback run;
    eventCallback event;
    updateCallback update;
    updateCallback fixed_update;

    resizeCallback resize;
    drawCallback draw;
};

#endif
