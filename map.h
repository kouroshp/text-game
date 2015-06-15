#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "context.h"

void add_map_commands(vector_t* commands);
void map_move_handler(context_t* context);
void map_where_handler(context_t* context);

#endif