#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <jansson.h>
#include "linenoise.h"
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
    // Load game data
    json_error_t error;
    json_t *data = json_load_file("data.json", 0, &error);

    if (!data) {
        fprintf(stderr, "Error loading data: %s\n", error.text);
        return 1;
    }

    // Initialise game context
    struct context context;
    map_init(&context, data);

    // Initialise commands
    struct vector commands;
    vector_init(&commands, sizeof(struct command *));
    handlers_init(&commands);

    // Start game
    linenoiseClearScreen();
    char *name;
    printf("What is your name?\n");
    name = linenoise("> ");
    person_init(&context.player, name);
    printf("Hello, %s!\n", context.player.name);

    // Main game loop
    char *input;

    while ((input = linenoise("> ")) != NULL) {
        linenoiseHistoryAdd(input);
        if (handle_input(input, &commands, &context) > 0) {
            free(input);
            break;
        }
        free(input);
    }

    // Clean up
    person_free(&context.player);
    free(name);
    map_free(&context);
    handlers_free(&commands);
    vector_free(&commands);
    json_decref(data);

    return 0;
}

static int handle_input(char *input, struct vector *commands, struct context *context)
{
    // Process command
    for (int i = 0; i < commands->size; i++) {
        struct command *cmd = vector_get(commands, i);

        if (strncasecmp(input, cmd->command, strlen(cmd->command)) == 0) {
            // Get arguments
            struct vector *args = strsplit(input, " ");

            // Invoke handler
            int result = cmd->handler(args, context);

            // Clean up
            free(args->data);
            free(args);

            return result;
        }
    }

    printf("I don't understand that!\n");
    return 0;
}
