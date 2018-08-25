/**
 * @file ${FILE}
 * @brief 
 * @license ${LICENSE}
 * Copyright (c) 8/12/18, Steven
 * 
 **/
#ifndef SLS_ENGINE_SLSWORLD_H
#define SLS_ENGINE_SLSWORLD_H

#include <slsmath.h>
#include "components.h"

enum slsComponentMask {
  SLS_NO_COMPONENT = 0,
  SLS_COMPONENT_EXISTS = 1u << 0u,
  SLS_COMPONENT_TRANSFORM = 1u << 1u,
  SLS_COMPONENT_RENDERSPRITE = 1u << 2u,
  SLS_COMPONENT_PLAYERCONTROLLED = 1u << 3u,
  SLS_COMPONENT_MOVEMENT= 1u << 3u,

  SLS_SYSTEM_RENDERSPRITE =
  SLS_COMPONENT_EXISTS | SLS_COMPONENT_TRANSFORM | SLS_COMPONENT_RENDERSPRITE
};



typedef enum slsComponentMask slsComponentMask;

typedef struct slsEntityWorld {
  size_t length;
  slsComponentMask *masks;
  slsMat4 *transforms;
  slsPlayerInput *inputs;
  slsMotion *motions;

} slsEntityWorld;

slsEntityWorld *sls_create_world(slsEntityWorld *world, size_t length);
slsEntityWorld *sls_destroy_world(slsEntityWorld *self);

/**
 *
 * @param self
 * @return if zero or positive, the index of the entity in the world.
 * Otherwise, returns negative
 */
int64_t sls_world_find_free_entity(slsEntityWorld *self);
int64_t sls_world_create_sprite(slsEntityWorld *self, slsMat4 const *transform);



#endif //SLS_ENGINE_SLSWORLD_H
