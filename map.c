#include <stdio.h>
#include "command.h"
#include "map.h"
#include "context.h"
#include "position.h"

void add_map_commands(vector_t* commands) {
	command_add(commands, "move", &map_move_handler);
	command_add(commands, "where", &map_where_handler);
}

void map_move_handler(context_t* context) {
	// Can only move forward for now!
	context->player->position.y += 1;
}

void map_where_handler(context_t* context) {
	printf("You are at %d, %d\n", context->player->position.x, context->player->position.y);
}