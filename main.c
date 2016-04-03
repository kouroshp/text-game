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
#include "handlers.h"

static int handle_input(char *input, struct vector *commands, struct context *context);

int main(void)
{
    // Initialise commands
    struct vector commands;
    vector_init(&commands, sizeof(struct command *));
    handlers_init(&commands);

    // Initialise game context
    struct context context;
    map_init(&context);
    char name[50];
    printf("What is your name?\n> ");
    fgets(name, sizeof(name), stdin);
    remove_newline(name);
    person_init(&context.player, name);
    printf("Hello, %s!\n", context.player.name);

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
    person_free(&context.player);
    map_free(&context);
    vector_free(&commands);

    return 0;
}

static int handle_input(char *input, struct vector *commands, struct context *context)
{
    // Exit handler
    if (strncmp(input, "exit", strlen("exit")) == 0 ||
        strncmp(input, "quit", strlen("quit")) == 0) {
        return 1;
    }

    // Process command
    for (int i = 0; i < commands->size; i++) {
        struct command *cmd = (struct command *)vector_get(commands, i);

        if (strncmp(input, cmd->command, strlen(cmd->command)) == 0) {
            // Get arguments
            struct vector *args = explode(input, " ");
            context->args = args;

            // Invoke handler
            cmd->handler(context);

            // Clean up
            free(args->data);
            free(args);

            return 0;
        }
    }

    printf("I don't understand that!\n");
    return 0;
}
