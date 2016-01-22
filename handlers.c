#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "handlers.h"
#include "command.h"
#include "context.h"
#include "inventory.h"
#include "map.h"

void inventory_commands_add(struct vector* commands)
{
    command_add(commands, "inventory", &inventory_handler_show);
    command_add(commands, "pickup", &inventory_handler_pickup);
    command_add(commands, "drop", &inventory_handler_drop);
}

void inventory_handler_show(struct context* context)
{
    inventory_contents_print(&context->player.inventory);
}

void inventory_handler_pickup(struct context* context)
{
    if (context->args->size == 1) {
        printf("Pick up what?\n");
        return;
    }

    struct item* item = malloc(sizeof(struct item));
    item->name = malloc(sizeof(context->args->data[1]));
    memcpy(item->name, context->args->data[1], sizeof(context->args->data[1]));
    item->weight = 1;

    if (!inventory_add(&context->player.inventory, item)) {
        printf("Your inventory is full!");
        item_free(item);
        free(item);
    }
}

void inventory_handler_drop(struct context* context)
{
    if (context->args->size == 1) {
        printf("Drop what?\n");
        return;
    }

    if (!inventory_remove(&context->player.inventory, atoi(context->args->data[1]))) {
        printf("You don't have that in your inventory...\n");
    }
}

void map_commands_add(struct vector* commands)
{
    command_add(commands, "move", &map_handler_move);
    command_add(commands, "where", &map_handler_where);
    command_add(commands, "look", &map_handler_look);
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
        context->player.position.y += 1;
    }
    else if (strncmp(direction, "backward", strlen("backward")) == 0) {
        context->player.position.y -= 1;
    }
    else if (strncmp(direction, "left", strlen("left")) == 0) {
        context->player.position.x -= 1;
    }
    else if (strncmp(direction, "right", strlen("right")) == 0) {
        context->player.position.x += 1;
    }
}

void map_handler_where(struct context* context)
{
    struct location* location = context->map[context->player.position.x][context->player.position.y];

    if (location != NULL) {
        printf("You are at %s\n", location->description);
    }
    else {
        printf("You are nowhere...\n");
    }
}

void map_handler_look(struct context* context)
{
    struct location* location = context->map[context->player.position.x][context->player.position.y];

    if (location != NULL) {
        if (location->inventory.size > 0) {
            printf("You see something in the darkness...\n");
            inventory_contents_print(&location->inventory);
        }
        if (location->people.size == 0) {
            printf("There is no one here...\n");
        }
    }
}
