#ifndef HANDLERS_H
#define HANDLERS_H

#include "context.h"
#include "vector.h"

void handlers_init(struct vector *commands);
void handlers_free(struct vector *commands);
int handler_quit(struct vector *args, struct context *context);
int handler_quit(struct vector *args, struct context *context);
int map_handler_move(struct vector *args, struct context *context);
int map_handler_where(struct vector *args, struct context *context);
int map_handler_look(struct vector *args, struct context *context);
int inventory_handler_show(struct vector *args, struct context *context);
int inventory_handler_pickup(struct vector *args, struct context *context);
int inventory_handler_drop(struct vector *args, struct context *context);
int player_handler_attack(struct vector *args, struct context *context);
int player_handler_equip(struct vector *args, struct context *context);

#endif
