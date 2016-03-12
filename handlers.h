#ifndef HANDLERS_H
#define HANDLERS_H

#include "context.h"
#include "vector.h"

void handlers_init(struct vector *commands);
void map_handler_move(struct context *context);
void map_handler_where(struct context *context);
void map_handler_look(struct context *context);
void inventory_handler_show(struct context *context);
void inventory_handler_pickup(struct context *context);
void inventory_handler_drop(struct context *context);
void player_handler_attack(struct context *context);
void player_handler_equip(struct context *context);

#endif
