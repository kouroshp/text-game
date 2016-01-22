#ifndef HANDLERS_H
#define HANDLERS_H

#include "context.h"
#include "vector.h"

void map_commands_add(struct vector* commands);
void map_handler_move(struct context* context);
void map_handler_where(struct context* context);
void map_handler_look(struct context* context);
void inventory_commands_add(struct vector* commands);
void inventory_handler_show(struct context* context);
void inventory_handler_pickup(struct context* context);
void inventory_handler_drop(struct context* context);

#endif
