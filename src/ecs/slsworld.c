/**
 * @file ${FILE}
 * @brief 
 * @license ${LICENSE}
 * Copyright (c) 8/12/18, Steven
 * 
 **/
#include "slsworld.h"


slsEntityWorld *sls_create_world(slsEntityWorld *self, size_t length)
{
  self->length = length;
  self->masks = calloc(length, sizeof(*self->masks));
  self->transforms = calloc(length, sizeof(*self->transforms));
  self->inputs = calloc(length, sizeof(*self->inputs));
  self->motions = calloc(length, sizeof(*self->motions));
  return self;
}

slsEntityWorld *sls_destroy_world(slsEntityWorld *self)
{
  self->length = 0;
  if (self->masks) { free(self->masks); }
  if (self->transforms) { free(self->transforms); }
  return self;
}


int64_t sls_world_find_free_entity(slsEntityWorld *self)
{
  for (int i = 0; i < self->length; ++i) {
    if ((self->masks[i] & SLS_COMPONENT_EXISTS) == 0) {
      return i;
    }
  }
  return -1;
}

int64_t sls_world_create_sprite(slsEntityWorld *self, slsMat4 const *transform)
{
  int64_t index = sls_world_find_free_entity(self);
  if (index < 0) return index;
  self->masks[index] = SLS_COMPONENT_EXISTS | SLS_COMPONENT_RENDERSPRITE | SLS_COMPONENT_TRANSFORM;
  self->transforms[index] = *transform;

  return index;
}
