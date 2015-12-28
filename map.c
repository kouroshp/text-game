#include <stdio.h>
#include <string.h>
#include "command.h"
#include "map.h"
#include "context.h"
#include "position.h"
#include "location.h"

void map_init(struct context* context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            context->map[x][y] = NULL;
        }
    }

    struct location* house = malloc(sizeof(struct location));
    house->description = "a dark ominous dwelling, old and forgotten.";
    context->map[1][1] = house;
}

void map_free(struct context* context)
{
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if (context->map[x][y] != NULL) {
                free(context->map[x][y]);
            }
        }
    }
}

void map_commands_add(struct vector* commands)
{
    command_add(commands, "move", &map_handler_move);
    command_add(commands, "where", &map_handler_where);
}

void map_handler_move(struct context* context)
{
    char* direction;

    // Direction should be second argument
    if (context->args->size > 1) {
        direction = context->args->data[1];
    }
    else {
        direction = "forward";
    }

    if (strncmp(direction, "forward", strlen("forward")) == 0) {
        context->player->position.y += 1;
    }
    else if (strncmp(direction, "backward", strlen("backward")) == 0) {
        context->player->position.y -= 1;
    }
    else if (strncmp(direction, "left", strlen("left")) == 0) {
        context->player->position.x -= 1;
    }
    else if (strncmp(direction, "right", strlen("right")) == 0) {
        context->player->position.x += 1;
    }
}

void map_handler_where(struct context* context)
{
    struct location* location = context->map[context->player->position.x][context->player->position.y];

    if (location != NULL) {
        printf("You are at %s\n", location->description);
    }
    else {
        printf("You are nowhere...\n");
    }
}
