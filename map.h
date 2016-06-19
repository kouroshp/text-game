#ifndef MAP_H
#define MAP_H

#include <jansson.h>
#include "vector.h"
#include "context.h"

void map_init(struct context *context, json_t *data);
void map_free(struct context *context);

#endif
