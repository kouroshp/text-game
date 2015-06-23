#include <stdio.h>
#include <string.h>
#include "command.h"
#include "map.h"
#include "context.h"
#include "position.h"

void add_map_commands(vector_t* commands) {
	command_add(commands, "move", &map_move_handler);
	command_add(commands, "where", &map_where_handler);
}

void map_move_handler(context_t* context) {
	if(strncmp(context->args, "forward", strlen("forward")) == 0) {
		context->player->position.y += 1;
	}
	else if(strncmp(context->args, "backward", strlen("backward")) == 0) {
		context->player->position.y -= 1;
	}
	else if(strncmp(context->args, "left", strlen("left")) == 0) {
		context->player->position.x -= 1;
	}
	else if(strncmp(context->args, "right", strlen("right")) == 0) {
		context->player->position.x += 1;
	}
}

void map_where_handler(context_t* context) {
	printf("You are at %d, %d\n", context->player->position.x, context->player->position.y);
}