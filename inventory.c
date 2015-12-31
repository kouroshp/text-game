#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "item.h"
#include "inventory.h"
#include "vector.h"
#include "command.h"
#include "context.h"

void inventory_init(struct inventory* inventory)
{
    inventory->size = 0;
    inventory->capacity = 10;

    inventory->contents = malloc(sizeof(struct list));
    list_init(inventory->contents);
}

bool inventory_add(struct inventory* inventory, struct item* item)
{
    if (inventory->size + item->weight <= inventory->capacity) {
        list_add(inventory->contents, item);
        inventory->size += item->weight;
        return true;
    }
    return false;
}

bool inventory_remove(struct inventory* inventory, int index)
{
    // Probably not very efficient
    struct item* item = inventory_get(inventory, index);

    if (item == NULL) {
        return false;
    }

    inventory->size -= item->weight;
    list_remove(inventory->contents, index);

    return true;
}

struct item* inventory_get(struct inventory* inventory, int index)
{
    struct node* node = list_get(inventory->contents, index);

    if (node != NULL) {
        return (struct item*)node->data;
    }

    return NULL;
}

void inventory_item_print(void* data) {
    printf("%s\n", ((struct item*)data)->name);
}

void inventory_contents_print(struct inventory* inventory)
{
    if (inventory->size == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    list_each(inventory->contents, &inventory_item_print);
}

void inventory_commands_add(struct vector* commands)
{
    command_add(commands, "inventory", &inventory_handler_show);
    command_add(commands, "pickup", &inventory_handler_pickup);
    command_add(commands, "drop", &inventory_handler_drop);
}

void inventory_handler_show(struct context* context)
{
    inventory_contents_print(context->player->inventory);
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

    if (!inventory_add(context->player->inventory, item)) {
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

    if (!inventory_remove(context->player->inventory, atoi(context->args->data[1]))) {
        printf("You don't have that in your inventory...\n");
    }
}

void inventory_free(struct inventory* inventory)
{
    list_each(inventory->contents, &inventory_item_free);
    list_free(inventory->contents);
    free(inventory->contents);
}

void inventory_item_free(void* item)
{
    item_free((struct item*)item);
}
