#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "context.h"

void add_map_commands(struct vector* commands);
void map_move_handler(struct context* context);
void map_where_handler(struct context* context);

#endif