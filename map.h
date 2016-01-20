#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "context.h"

void map_init(struct context* context);
void map_free(struct context* context);
void map_commands_add(struct vector* commands);
void map_handler_move(struct context* context);
void map_handler_where(struct context* context);
void map_handler_look(struct context* context);

#endif
