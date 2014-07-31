/*
 * world.c
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

#ifndef WORLD_C_
#define WORLD_C_

#define MAX_COMPONENTS 50

#include <glib.h>
#include "../linalg/sls-transform2d.h"
#include "../types.h"

typedef enum {
	COMPONENT_NONE = 0,
	COMPONENT_TRANSFORM = 1 << 0
} slsComponent;

typedef struct _slsEntityTable slsEntityTable;

/*********************************************************************
 *
 * entity table type
 *
 **********************************************************************/

struct _slsEntityTable {
	GArray *component_mask; // type slsComponent

	/**
	 * list component arrays here
	 */

	GArray *transform; //type struct slsTransform2D
};

slsEntityTable *slsEntityTable_create();
void slsEntityTable_free(slsEntityTable *world);

/**
 * appends to each component and the component-map arrays one index
 * returns etity ID index
 */
SLuint slsEntityTable_addEntity(slsEntityTable *world);
void slsEntityTable_removeEntity(slsEntityTable *world, SLuint entity_id);


/**
 * ensures each component list in world is of equal length.
 */
SLbool slsEntityTable_validate(slsEntityTable *world);


#endif /* WORLD_C_ */
