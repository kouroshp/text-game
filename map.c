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
	char* direction;

	// Direction should be second argument
	if(context->args->size > 1) {
		direction = context->args->data[1];
	}
	else {
		direction = "forward";
	}

	if(strncmp(direction, "forward", strlen("forward")) == 0) {
		context->player->position.y += 1;
	}
	else if(strncmp(direction, "backward", strlen("backward")) == 0) {
		context->player->position.y -= 1;
	}
	else if(strncmp(direction, "left", strlen("left")) == 0) {
		context->player->position.x -= 1;
	}
	else if(strncmp(direction, "right", strlen("right")) == 0) {
		context->player->position.x += 1;
	}
}

void map_where_handler(context_t* context) {
	printf("You are at %d, %d\n", context->player->position.x, context->player->position.y);
}