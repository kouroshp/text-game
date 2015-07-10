#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "item.h"
#include "inventory.h"
#include "map.h"
#include "person.h"
#include "command.h"
#include "vector.h"
#include "context.h"
#include "utilities.h"

void handle_input(char* input, struct vector* commands, struct context* context);

int main(void) {
	// Initialise commands
	struct vector commands;
	vector_init(&commands, sizeof(struct command*));
	add_map_commands(&commands);
	
	// Initialise player
	struct person player;
	char name[50];
	printf("What is your name?\n> ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = 0; // Remove trailing newline
	person_init(&player, name);
	printf("Hello, %s!\n", player.name);

	// Initialise game context
	struct context context;
	context.player = &player;

	// Main game loop
	char input[50];

	while (true) {
		printf("> ");
		fgets(input, sizeof(input), stdin);

		handle_input(input, &commands, &context);
	}

	return 0;
}

void handle_input(char* input, struct vector* commands, struct context* context) {
	bool handled = false;

	// Exit handler
	if(strncmp(input, "exit", strlen("exit")) == 0) {
		exit(0);
	}
	// Process command
	for (int i = 0; i < commands->size; i++) {
		struct command* cmd = (struct command*)vector_get(commands, i);

		if(strncmp(input, cmd->command, strlen(cmd->command)) == 0) {
			struct vector* args = explode(input, " ");
			context->args = args;

			cmd->handler(context); // Invoke handler
			handled = true;
			break;
		}
	}
	if (!handled) {
		printf("I don't understand that!\n");
	}
}