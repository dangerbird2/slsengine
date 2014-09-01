/*
 * sls-component-transform.h
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

#ifndef SLS_TRANSFORM_2D_H_
#define SLS_TRANSFORM_2D_H_

#include "../types.h"
#include "vectypes.h"

struct slsTransform2D {
	vec2d position;
	vec2d scale;

	/*
	 * rotation is in RADIANS!!!!
	 */
	float rotation;
};

static inline struct slsTransform2D sls_default_transform()
{
	return (struct slsTransform2D) {
		.position = (vec2d) {0.0, 0.0},
		.scale = (vec2d) {1.0, 1.0},
		.rotation = 0.0
	};
}

#endif /* SLS_TRANSFORM_2D_H_ */
