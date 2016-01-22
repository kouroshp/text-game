#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "item.h"
#include "inventory.h"

void inventory_init(struct inventory* inventory)
{
    inventory->size = 0;
    inventory->capacity = 10;
    list_init(&inventory->contents);
}

bool inventory_add(struct inventory* inventory, struct item* item)
{
    if (inventory->size + item->weight <= inventory->capacity) {
        list_add(&inventory->contents, item);
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
    list_remove(&inventory->contents, index);

    return true;
}

struct item* inventory_get(struct inventory* inventory, int index)
{
    struct node* node = list_get(&inventory->contents, index);

    if (node != NULL) {
        return (struct item*)node->data;
    }

    return NULL;
}

void inventory_item_print(int index, void* data) {
    printf("[%d] %s\n", index, ((struct item*)data)->name);
}

void inventory_contents_print(struct inventory* inventory)
{
    if (inventory->size == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    list_each_with_index(&inventory->contents, &inventory_item_print);
}


void inventory_free(struct inventory* inventory)
{
    list_free(&inventory->contents);
}
