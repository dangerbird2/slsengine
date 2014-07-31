/*
 * sls-world.c
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Steven Shea
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *  Created on: Jul 25, 2014
 *      Author: steven
 */

#include "../types.h"
#include "../linalg/vectypes.h"
#include "sls-entity-table.h"
#include "../linalg/sls-transform2d.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

slsEntityTable *slsEntityTable_create()
{
    slsEntityTable *world = malloc(sizeof(slsEntityTable));
    g_return_val_if_fail(world != NULL, NULL);

    world->component_mask = g_array_new(FALSE, FALSE, sizeof(SLenum));

    // allocate component arrays
    world->transform = g_array_new(TRUE, FALSE, sizeof(struct slsTransform2D));

    return world;
}
void slsEntityTable_free(slsEntityTable *world)
{
    g_return_if_fail(world !=NULL);
    g_array_unref(world->component_mask);
    g_array_unref(world->transform);

    free(world);
}

SLuint slsEntityTable_addEntity(slsEntityTable *world)
{
    SLuint id = 0;
    if (!slsEntityTable_validate(world)){
        g_return_val_if_reached(id);
    }
    // append component mask
    SLenum mask = COMPONENT_NONE;
    g_array_append_val(world->component_mask, mask);

    // append transform struct
    struct slsTransform2D transform = sls_default_transform();
    g_array_append_val(world->transform, transform);

    id = world->component_mask->len -1;

    return id;
}

void slsEntityTable_removeEntity(slsEntityTable *world, SLuint entity_id)
{
    g_array_remove_index(world->component_mask, entity_id);
    g_array_remove_index(world->transform, entity_id);

    slsEntityTable_validate(world);
}

SLbool slsEntityTable_validate(slsEntityTable *world)
{
    if (!(world->component_mask->len == world->transform->len)) {
        g_return_val_if_reached(false);
    }
    return true;
}
