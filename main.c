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

int handle_input(char* input, struct vector* commands, struct context* context);

int main(void)
{
    // Initialise commands
    struct vector commands;
    vector_init(&commands, sizeof(struct command*));
    map_commands_add(&commands);
    inventory_commands_add(&commands);

    // Initialise player
    struct person player;
    char name[50];
    printf("What is your name?\n> ");
    fgets(name, sizeof(name), stdin);
    remove_newline(name);
    person_init(&player, name);
    printf("Hello, %s!\n", player.name);

    // Initialise game context
    struct context context;
    context.player = &player;
    map_init(&context);

    // Main game loop
    char input[50];

    while (true) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        if (handle_input(input, &commands, &context) > 0) {
            break;
        }
    }

    // Clean up
    person_free(&player);
    vector_free(&commands);
    map_free(&context);

    return 0;
}

int handle_input(char* input, struct vector* commands, struct context* context)
{
    bool handled = false;

    // Exit handler
    if (strncmp(input, "exit", strlen("exit")) == 0) {
        return 1;
    }
    // Process command
    for (int i = 0; i < commands->size; i++) {
        struct command* cmd = (struct command*)vector_get(commands, i);

        if (strncmp(input, cmd->command, strlen(cmd->command)) == 0) {
            // Get arguments
            struct vector* args = explode(input, " ");
            context->args = args;

            // Invoke handler
            cmd->handler(context);
            handled = true;

            // Clean up
            free(args->data);
            free(args);

            break;
        }
    }
    if (!handled) {
        printf("I don't understand that!\n");
    }

    return 0;
}
